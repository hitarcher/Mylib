#pragma once

#ifndef LINK_H_
#define LIN_H_

class Car
{
public:
	Car(int num);
	~Car();

	int num;
};

class Link
{
private:
	struct Node
	{
		int val;
		struct Node* next;
	};
	Node *head;//链表头节点
public:
	Link();
	~Link();
	bool InsertNewVal(int newValue);
	bool deleteElemenet(int oldValue);
	bool findByvalu(int val);
	bool modifyElement(int oldval, int newval);
	void display();

};

void  TestLinkedList();

#endif
