#include "stdafx.h"
#include "Friend.h"

void goodGay(Building * building)
{
	cout << "�û������ڷ��ʣ� "<< building->m_SittingRoom.c_str() << endl;
	cout << "�û������ڷ��ʣ� "<< building->m_BedRoom.c_str() << endl;
}

void test01()
{
	Building b;
	goodGay(&b);
}

void Friendmain() {
	test01();
	
}
