#include "stdafx.h"
#include "Friend.h"

void goodGay(Building * building)
{
	cout << "好基友正在访问： "<< building->m_SittingRoom.c_str() << endl;
	cout << "好基友正在访问： "<< building->m_BedRoom.c_str() << endl;
}

void test01()
{
	Building b;
	goodGay(&b);
}

void Friendmain() {
	test01();
	
}
