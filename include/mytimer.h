#pragma once

#ifndef __MY_TIMER__H__
#define __MY_TIMER__H__

#include <string>
#include <mutex>
using namespace std;

#include "json.hpp"
using json = nlohmann::json;

/************************************************************************/
/*                               ��ʱ��                                 */
/************************************************************************/

// ֧�ֶ�ʱִ��һ�λ���ѯִ��
// ע�⣺���߳�ʹ�ã���ε���setTimeout������������������ң�
class easyTimer
{
public:
	easyTimer()
	{
		this->mutex_thread_work.lock();
	};
	~easyTimer()
	{
		this->mutex_thread_work.unlock();
		this->mutex_thread_exit.try_lock_for(std::chrono::seconds(10));
	};

private:
	// ���sleep��������;�˳�
	std::timed_mutex mutex_thread_work;
	// �ȴ��̰߳�ȫ�˳�
	std::timed_mutex mutex_thread_exit;

public:
	template<typename Function>
	void setTimeout(Function function, int delay)
	{
		this->mutex_thread_exit.try_lock();
		std::thread t([=]() {
			// ���sleep
			this->mutex_thread_work.try_lock();
			bool blocked = this->mutex_thread_work.try_lock_for(std::chrono::milliseconds(delay));
			if (blocked == true) {
				return this->mutex_thread_exit.unlock();
			}
			function();
			this->mutex_thread_exit.unlock();
		});
		t.detach();
	}

	template<typename Function>
	void setInterval(Function function, int interval)
	{
		this->mutex_thread_exit.try_lock();
		std::thread t([=]() {
			while (true)
			{
				// ���sleep
				this->mutex_thread_work.try_lock();
				bool blocked = this->mutex_thread_work.try_lock_for(std::chrono::milliseconds(interval));
				if (blocked == true) {
					return this->mutex_thread_exit.unlock();
				}
				function();
			}
		});
		t.detach();
	}

	template<typename Function>
	void setInterval2(Function function, json param, int interval)
	{
		this->mutex_thread_exit.try_lock();
		std::thread t([=](json th_param) {
			while (true)
			{
				// ���sleep
				this->mutex_thread_work.try_lock();
				bool blocked = this->mutex_thread_work.try_lock_for(std::chrono::milliseconds(interval));
				if (blocked == true) {
					return this->mutex_thread_exit.unlock();
				}
				function(th_param);
			}
		}, param);
		t.detach();
	}
};

// ֧���Զ��嶨ʱ��
// ע�⣺���̣߳�ֻ����һ����ɲ���ִ����һ����ǿ�йرջᵼ���̲߳���ȫ
class myTimer {
public:
	myTimer()
	{
		// ��ʼ��
		mutex_waiting.lock();
	};
	~myTimer()
	{
		// �ͷ����߳�
		m_exit = true;
		mutex_waiting.unlock();

		// �ͷ��������߳�
		threadpoll_clear();

		// �ȴ��߳��˳�
		while (!threadpoll_isexited())
		{
			Sleep(2);
		}
	};

private:
	// ���߳��˳�
	bool m_exit = false;
	// ���̵߳ȴ��ź�
	std::timed_mutex mutex_waiting;
	// ��ǰִ�е�timer id
	int m_idevent = NULL;

private:
	/************************************************************************/
	/*                                �̳߳ع���                            */
	/************************************************************************/
	// �������ù���timer poll
	//   [%id][active:bool]	
	//   [%id][param:json]
	//   [%id][mutexs:array:uint64_t] ����һ��timer idevent����߳�
	//   [poll:array:%id]
	json m_timerpoll;
	// ��json��������ֹ��ͻ
	std::timed_mutex mutex_poll;

	// ��ӵ��̳߳�
	void threadpoll_join(int idevent, void *pmutex, json param)
	{
		mutex_poll.lock();
		// [%id]
		m_timerpoll[to_string(idevent).c_str()]["active"] = true;
		m_timerpoll[to_string(idevent).c_str()]["param"] = param;
		m_timerpoll[to_string(idevent).c_str()]["mutexs"].push_back((uint64_t)pmutex);

		// [poll]
		bool already = false;
		for (json::iterator it = m_timerpoll["poll"].begin();
			it != m_timerpoll["poll"].end(); it++)
		{
			if ((*it).get<std::int32_t>() == idevent) {
				already = true;
				break;
			}
		}
		if (already == false) m_timerpoll["poll"].push_back(idevent);
		mutex_poll.unlock();
	}

	// ƥ��pmutex���������߳��˳���������
	void threadpoll_exit(int idevent, void *pmutex)
	{
		mutex_poll.lock();
		try
		{
#ifdef DEBUG
			int size0 = m_timerpoll[to_string(idevent).c_str()]["mutexs"].size();
#endif 
			// [%id]
			//   [%id][mutexs:array:uint64_t]
			for (json::iterator it = m_timerpoll[to_string(idevent).c_str()]["mutexs"].begin();
				it != m_timerpoll[to_string(idevent).c_str()]["mutexs"].end(); it++) {
				// �ҵ���ɾ��
				if ((*it).get<std::uint64_t>() == (uint64_t)pmutex) {
					m_timerpoll[to_string(idevent).c_str()]["mutexs"].erase(it);
					break;
				}
			}
#ifdef DEBUG
			std::string tmp = m_timerpoll.dump();
			int size = m_timerpoll[to_string(idevent).c_str()]["mutexs"].size();
#endif 
			// [poll]
			// do nothing
		}
		catch (const std::exception&)
		{
			// do nothing
		}
		mutex_poll.unlock();
	}

	// ƥ��idevent��һ�飩�߳��Ƴ���������
	void threadpoll_remove(int idevent)
	{
		mutex_poll.lock();
		try
		{
			// [%id]
			//   [%id][active:bool]	
			m_timerpoll[to_string(idevent).c_str()]["active"] = false;

			//   [%id][mutexs:array:uint64_t]
			for (json::iterator it = m_timerpoll[to_string(idevent).c_str()]["mutexs"].begin();
				it != m_timerpoll[to_string(idevent).c_str()]["mutexs"].end(); it++) {
				// �Ƴ�
				std::timed_mutex *pmutex_elapse =
					(std::timed_mutex *)(void*)((*it).get<std::uint64_t>());
				pmutex_elapse->unlock();
			}

			// [poll]
			// do nothing
		}
		catch (const std::exception&)
		{
			// do nothing
		}
		mutex_poll.unlock();
	}

	// ƥ��idevent��ȡparam
	json threadpoll_param(int idevent)
	{
		json param;
		mutex_poll.lock();
		try
		{
			param = m_timerpoll[to_string(idevent).c_str()]["param"];
		}
		catch (const std::exception&)
		{
			// do nothing
		}
		mutex_poll.unlock();
		return param;
	}

	// ƥ��idevent�鿴timer�ļ���״̬��kill����false
	bool threadpoll_active(int idevent)
	{
		bool active = false;
		mutex_poll.lock();
		try
		{
			active = m_timerpoll[to_string(idevent).c_str()]["active"];
		}
		catch (const std::exception&)
		{
			// do nothing
		}
		mutex_poll.unlock();
		return active;
	}

	// ��������̳߳�
	void threadpoll_clear()
	{
		mutex_poll.lock();
		//   [poll:array:%id]
		for (json::iterator itid = m_timerpoll["poll"].begin();
			itid != m_timerpoll["poll"].end(); itid++) {
			//   [%id][mutexs:array:uint64_t] 
			json jidmutexs = m_timerpoll[to_string((*itid).get<std::int32_t>()).c_str()];
			for (json::iterator itmutex = jidmutexs["mutexs"].begin();
				itmutex != jidmutexs["mutexs"].end(); itmutex++) {
				// �Ƴ�
				std::timed_mutex *pmutex_elapse =
					(std::timed_mutex *)(void*)((*itmutex).get<std::uint64_t>());
				pmutex_elapse->unlock();
			}
			m_timerpoll[to_string((*itid).get<std::int32_t>()).c_str()]["active"] = false;
		}
		mutex_poll.unlock();
	}

	// �Ƿ�ȫ���ͷ�
	bool threadpoll_isexited()
	{
		bool exit = true;
		mutex_poll.lock();
		try
		{
#ifdef DEBUG
			std::string tmp = m_timerpoll.dump();
#endif 
			//   [poll:array:%id]
			for (json::iterator itid = m_timerpoll["poll"].begin();
				itid != m_timerpoll["poll"].end(); itid++) {
				//   [%id][mutexs:array:uint64_t] 
				exit &= !(m_timerpoll[to_string((*itid).get<std::int32_t>()).c_str()]["mutexs"].size());
			}
		}
		catch (const std::exception&)
		{
			// do nothing
		}
		mutex_poll.unlock();
		return exit;
	}

public:
	// �Զ���timer����
	template<typename Function>
	void onTimer(Function function)
	{
		std::thread t([=]() {
			std::timed_mutex mutex_main; mutex_main.lock();
			threadpoll_join(-1, &mutex_main, "");
			while (!m_exit)
			{
				// �ȴ�timer����
				mutex_waiting.lock();

				// ���߳��˳������߳��˳�
				if (m_exit) break;

				// ִ��.....
				function(this->m_idevent, threadpoll_param(this->m_idevent));
			}
			threadpoll_exit(-1, &mutex_main);
		});
		t.detach();
	}

	// ��ʱִ�У�ִֻ��һ��
	void setTimer(int idevent, int elapse, json param)
	{
		// ��ʱ
		std::thread t([=]() {
			// ʹ��mutex����sleep
			std::timed_mutex mutex_elapse; mutex_elapse.lock();

			// ��ӵ��̳߳�
			threadpoll_join(idevent, &mutex_elapse, param);

			// ��ʼ��ʱ......
			bool blocked = mutex_elapse.try_lock_for(std::chrono::milliseconds(elapse));

			// �жϣ����߳��˳�������ִ�ж�ʱ����
			if (blocked == true) return threadpoll_exit(idevent, &mutex_elapse);

			// �жϣ���ʱ����kill
			if (threadpoll_active(idevent) == false)
				return threadpoll_exit(idevent, &mutex_elapse);

			// ִ��......
			//   ע������ʱontimer����ִ�У���ô�˴���Ϣ������
			this->m_idevent = idevent;
			mutex_waiting.unlock();

			// ��Ǵ��߳��Ѿ��˳�
			threadpoll_exit(idevent, &mutex_elapse);
		});
		t.detach();
	}

	// ��ʱִ�У���ѯ
	void setInterval(int idevent, int elapse, json param)
	{
		killTimer(idevent);

		std::thread t([=]() {
			// ʹ��mutex����sleep
			std::timed_mutex mutex_elapse; mutex_elapse.lock();

			// ��ӵ��̳߳�
			threadpoll_join(idevent, &mutex_elapse, param);

			// ��ʱ
			while (true)
			{
				// set timer
				setTimer(idevent, elapse, param);

				// ��ʼ��ʱ......
				//   +10��Ϊ�˷�ֹ��һ����ûִ�����ִ������һ��
				bool blocked = mutex_elapse.try_lock_for(std::chrono::milliseconds(elapse + 10));

				// �жϣ����߳��˳�������ִ�ж�ʱ����
				if (blocked == true) return threadpoll_exit(idevent, &mutex_elapse);

				// �жϣ���ʱ����kill
				if (threadpoll_active(idevent) == false)
					return threadpoll_exit(idevent, &mutex_elapse);
			}
		});
		t.detach();
	}

	// ��ǰִ��֮ǰɱ����ʱ��
	void killTimer(int idevent)
	{
		// �Ƴ����е��߳�
		threadpoll_remove(idevent);
	}

	// ���������Ϣ
	void clear()
	{
		threadpoll_clear();
	}
};

#endif