// #ifndef _MY_LOG_HPP_
// #define _MY_LOG_HPP_
// #include <iostream>
// using namespace std;
// #include "spdlog/spdlog.h"
// #include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
// #include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging
// #include "spdlog/sinks/stdout_sinks.h"
// #include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no colors needed
// #include "spdlog/sinks/daily_file_sink.h"
// 
// 
// class MyLog
// {
// public:
// 	static MyLog& GetInstance();
// protected:
// 	MyLog();
// 	~MyLog();
// private:
// 	MyLog(const MyLog& rhs) {}
// 	MyLog& operator = (const MyLog& rhs) {}
// public:
// 	/*
// 	trace = SPDLOG_LEVEL_TRACE,
// 	debug = SPDLOG_LEVEL_DEBUG,
// 	info = SPDLOG_LEVEL_INFO,
// 	warn = SPDLOG_LEVEL_WARN,
// 	err = SPDLOG_LEVEL_ERROR,
// 	critical = SPDLOG_LEVEL_CRITICAL,
// 	off = SPDLOG_LEVEL_OFF,
// 	*/
// 	bool InitLogObject(int consolelevel = 0, const int filelevel = 0, int maxsize = 1000, int backIndex = 10, int isDay = 1);
// 	auto& GetConsoleObject();
// 	auto& GetFileObject();
// 
// public:
// 	int m_isDay;
// };
// MyLog::MyLog()
// {
// }
// MyLog::~MyLog()
// {
// 	std::cout << "析构了" << std::endl;
// }
// MyLog& MyLog::GetInstance()
// {
// 	static MyLog instance;
// 	return instance;
// }
// auto& MyLog::GetConsoleObject()
// {
// 	return spdlog::get("console");
// }
// auto& MyLog::GetFileObject()
// {
// 	if (m_isDay == 1)
// 	{
// 		return spdlog::get("daily_logger");
// 	}
// 	return spdlog::get("file_logger");
// }
// 
// bool MyLog::InitLogObject(int consolelevel, int filelevel, int maxsize, int backIndex, int isDay)
// {
// 	try
// 	{
// 		m_isDay = isDay;
// 		auto console = spdlog::stdout_logger_mt("console");
// 
// 		switch (consolelevel)
// 		{
// 		case 0:console->set_level(spdlog::level::trace); break;
// 		case 1:console->set_level(spdlog::level::debug); break;
// 		case 2:console->set_level(spdlog::level::info); break;
// 		case 3:console->set_level(spdlog::level::warn); break;
// 		case 4:console->set_level(spdlog::level::err); break;
// 		case 5:console->set_level(spdlog::level::critical); break;
// 		case 6:console->set_level(spdlog::level::off); break;
// 		default:
// 			console->set_level(spdlog::level::trace);
// 			break;
// 		}
// 		// 单位M 即：maxsize M
// 		auto file_logger = spdlog::rotating_logger_mt("file_logger", "logs/rotat.log", 1024 * 1024 * maxsize, backIndex);
// 		auto daily_logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.log", 23, 59);
// 		switch (filelevel)
// 		{
// 		case 0:
// 		{
// 			file_logger->set_level(spdlog::level::trace);
// 			daily_logger->set_level(spdlog::level::trace);
// 			break;
// 		}
// 		case 1:
// 		{
// 			file_logger->set_level(spdlog::level::debug);
// 			daily_logger->set_level(spdlog::level::debug);
// 			break;
// 		}
// 		case 2:
// 		{
// 			file_logger->set_level(spdlog::level::info);
// 			daily_logger->set_level(spdlog::level::info);
// 			break;
// 		}
// 		case 3:
// 		{
// 			file_logger->set_level(spdlog::level::warn);
// 			daily_logger->set_level(spdlog::level::warn);
// 			break;
// 		}
// 		case 4:
// 		{
// 			file_logger->set_level(spdlog::level::err);
// 			daily_logger->set_level(spdlog::level::err);
// 			break;
// 		}
// 		case 5:
// 		{
// 			file_logger->set_level(spdlog::level::critical);
// 			daily_logger->set_level(spdlog::level::critical);
// 			break;
// 		}
// 		case 6:
// 		{
// 			file_logger->set_level(spdlog::level::off);
// 			daily_logger->set_level(spdlog::level::off);
// 			break;
// 		}
// 		default:
// 		{
// 			file_logger->set_level(spdlog::level::trace);
// 			daily_logger->set_level(spdlog::level::trace);
// 			break;
// 		}
// 		}
// 
// 		return true;
// 
// 	}
// 	catch (const spdlog::spdlog_ex& ex)
// 	{
// 		std::cout << "Log initialization failed: " << ex.what() << std::endl;
// 	}
// 	return true;
// }
// #endif // !_MY_LOG_HPP_

#ifndef _LOGFILE_H
#define _LOGFILE_H

#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

class LogFile
{
protected:

	CRITICAL_SECTION _csLock;
	char * _szFileName;
	HANDLE _hFile;

	bool OpenFile()//打开文件， 指针到文件尾
	{
		if (IsOpen())
			return true;

		if (!_szFileName)
			return false;

		_hFile = CreateFile(
			_szFileName,
			GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (!IsOpen() && GetLastError() == 2)//打开不成功， 且因为文件不存在， 创建文件
			_hFile = CreateFile(
				_szFileName,
				GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);

		if (IsOpen())
			SetFilePointer(_hFile, 0, NULL, FILE_END);

		return IsOpen();
	}

	DWORD Write(LPCVOID lpBuffer, DWORD dwLength)
	{
		DWORD dwWriteLength = 0;

		if (IsOpen())
			WriteFile(_hFile, lpBuffer, dwLength, &dwWriteLength, NULL);

		return dwWriteLength;
	}

	virtual void WriteLog(LPCVOID lpBuffer, DWORD dwLength)//写日志, 可以扩展修改
	{
		time_t now;
		char temp[21];
		DWORD dwWriteLength;

		if (IsOpen())
		{
			time(&now);
			strftime(temp, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));

			WriteFile(_hFile, "/xd/xa#-----------------------------", 32, &dwWriteLength, NULL);
			WriteFile(_hFile, temp, 19, &dwWriteLength, NULL);
			WriteFile(_hFile, "-----------------------------#/xd/xa", 32, &dwWriteLength, NULL);
			WriteFile(_hFile, lpBuffer, dwLength, &dwWriteLength, NULL);
			WriteFile(_hFile, "/xd/xa", 2, &dwWriteLength, NULL);

			FlushFileBuffers(_hFile);

		}
	}

	void Lock() { ::EnterCriticalSection(&_csLock); }
	void Unlock() { ::LeaveCriticalSection(&_csLock); }

public:

	LogFile(const char *szFileName = "Log.log")//设定日志文件名
	{
		_szFileName = NULL;
		_hFile = INVALID_HANDLE_VALUE;
		::InitializeCriticalSection(&_csLock);

		SetFileName(szFileName);
	}

	virtual ~LogFile()
	{
		::DeleteCriticalSection(&_csLock);
		Close();

		if (_szFileName)
			delete[]_szFileName;
	}

	const char * GetFileName()
	{
		return _szFileName;
	}

	void SetFileName(const char *szName)//修改文件名， 同时关闭上一个日志文件
	{
		assert(szName);

		if (_szFileName)
			delete[]_szFileName;

		Close();

		_szFileName = new char[strlen(szName) + 1];
		assert(_szFileName);
		strcpy(_szFileName, szName);
	}

	bool IsOpen()
	{
		return _hFile != INVALID_HANDLE_VALUE;
	}

	void Close()
	{
		if (IsOpen())
		{
			CloseHandle(_hFile);
			_hFile = INVALID_HANDLE_VALUE;
		}
	}

	void Log(LPCVOID lpBuffer, DWORD dwLength)//追加日志内容
	{
		assert(lpBuffer);
		__try
		{
			Lock();

			if (!OpenFile())
				return;

			WriteLog(lpBuffer, dwLength);
		}
		__finally
		{
			Unlock();
		}
	}

	void Log(const char *szText)
	{
		Log(szText, strlen(szText));
	}

private://屏蔽函数

	LogFile(const LogFile&);
	LogFile&operator = (const LogFile&);
};

class LogFileEx : public LogFile
{
protected:

	char *_szPath;
	char _szLastDate[9];
	int _iType;

	void SetPath(const char *szPath)
	{
		assert(szPath);

		WIN32_FIND_DATA wfd;
		char temp[MAX_PATH + 1] = { 0 };

		if (FindFirstFile(szPath, &wfd) == INVALID_HANDLE_VALUE && CreateDirectory(szPath, NULL) == 0)
		{
			strcat(strcpy(temp, szPath), " Create Fail. Exit Now! Error ID :");
			ltoa(GetLastError(), temp + strlen(temp), 10);
			MessageBox(NULL, temp, "Class LogFileEx", MB_OK);
			exit(1);
		}
		else
		{
			GetFullPathName(szPath, MAX_PATH, temp, NULL);
			_szPath = new char[strlen(temp) + 1];
			assert(_szPath);
			strcpy(_szPath, temp);
		}
	}

public:

	enum LOG_TYPE { YEAR = 0, MONTH = 1, DAY = 2 };

	LogFileEx(const char *szPath = ".", LOG_TYPE iType = MONTH)
	{
		_szPath = NULL;
		SetPath(szPath);
		_iType = iType;
		memset(_szLastDate, 0, 9);
	}

	~LogFileEx()
	{
		if (_szPath)
			delete[]_szPath;
	}

	const char * GetPath()
	{
		return _szPath;
	}

	void Log(LPCVOID lpBuffer, DWORD dwLength)
	{
		assert(lpBuffer);

		char temp[10];
		static const char format[3][10] = { "%Y", "%Y-%m", "%Y%m%d" };

		__try
		{
			Lock();

			time_t now = time(NULL);

			strftime(temp, 9, format[_iType], localtime(&now));

			if (strcmp(_szLastDate, temp) != 0)//更换文件名
			{
				strcat(strcpy(_szFileName, _szPath), "//");
				strcat(strcat(_szFileName, temp), ".log");
				strcpy(_szLastDate, temp);
				Close();
			}

			if (!OpenFile())
				return;

			WriteLog(lpBuffer, dwLength);
		}
		__finally
		{
			Unlock();
		}
	}

	void Log(const char *szText)
	{
		Log(szText, strlen(szText));
	}

private://屏蔽函数

	LogFileEx(const LogFileEx&);
	LogFileEx&operator = (const LogFileEx&);

};

#endif