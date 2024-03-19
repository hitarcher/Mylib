// LinkedList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LinkedList.h"
#define _AFXDLL
#include <iostream>
using namespace std;
#include <afxcoll.h>


Car::Car(int num)
	:num(num)
{
}

Car::~Car()
{}


Link::Link()
{
	head = new Node();
	head->next = head;

}
Link::~Link()
{
	Node*p = head->next;
	Node*q = p;
	while (q != head)
	{
		p = p->next;
		delete q;
		q = p;
	}
	delete head;
}

bool Link::InsertNewVal(int newVal)
{
	Node * newnode = new Node();
	newnode->val = newVal;
	Node*p = head->next;
	while (p->next != head)
	{
		p = p->next;
	}
	p->next = newnode;
	newnode->next = head;
	return true;

}

bool Link::deleteElemenet(int oldval)
{
	Node *q = head;
	Node *p = head->next;

	while (p != head)
	{
		if (p->val == oldval)
		{
			q->next = p->next;
			delete p;
			return true;
		}
		q = p;
		p = p->next;
	}
}

bool Link::findByvalu(int val)
{
	Node *p = head->next;
	while (p != head)
	{
		if (p->val == val)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}

bool Link::modifyElement(int oldValue, int newval)
{
	Node*p = head->next;
	while (p != head)
	{
		if (p->val == oldValue)
		{
			p->val = newval;
			return true;
		}
		p = p->next;
	}
	return false;
}


//	//来自 afxcoll.h 的一种链表，ptr是用于存放指针，CList 是通用型
CPtrList g_clientList;		// 链表用于存储用户

void  TestLinkedList()
{
	Car *car1 = new Car(1);//num 为 1
	Car *car2 = new Car(2);
	g_clientList.AddTail(car1); //增
	g_clientList.AddTail(car2); //增
	int m_UserCount = g_clientList.GetCount();//获得数量

											  //删
	POSITION nPos = g_clientList.GetHeadPosition();
	POSITION nTmpPos = nPos;
	while (nPos)
	{
		Car* pcar = (Car*)g_clientList.GetNext(nPos);//循环
		if (1 == pcar->num)
		{
			g_clientList.RemoveAt(nTmpPos);
			m_UserCount = g_clientList.GetCount();
		}
		nTmpPos = nPos;
	}


}

