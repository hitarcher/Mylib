#pragma once
#include <iostream>
using namespace std;
/*************************************************************************************************/

class D;
class C
{
	friend class D;
public:
	inline void display() { cout << "iamC" << endl; }
};

class D
{
public:
	C c;
};

/*************************************************************************************************/
//ȫ�ֺ�������Ԫ
class Building
{
	//���߱����� goodGayȫ�ֺ��� �� Building��ĺ����ѣ����Է������е�˽������
	friend void goodGay(Building * building);

public:
	Building()
	{
		this->m_SittingRoom = "����";
		this->m_BedRoom = "����";
	}
public:
	string m_SittingRoom; //����
private:
	string m_BedRoom; //����
};


void Friendmain();

/*************************************************************************************************/
//������Ԫ
/*
class Building;
class goodGay
{
public:
	goodGay();
	void visit();
private:
	Building *building;
};


class Building
{
	//���߱����� goodGay����Building��ĺ����ѣ����Է��ʵ�Building����˽������
	friend class goodGay;
public:
	Building(); //Ĭ�Ϲ��캯��
public:
	string m_SittingRoom; //����
private:
	string m_BedRoom;//����
};

//Ҳ���������ⶨ����Щ��Ա����
Building::Building()
{
	this->m_SittingRoom = "����";
	this->m_BedRoom = "����";
}

goodGay::goodGay()
{
	building = new Building; //�����ֱ�ӹ�����һ��Building����
}

void goodGay::visit()
{
	cout << "�û������ڷ���" << building->m_SittingRoom << endl;
	cout << "�û������ڷ���" << building->m_BedRoom << endl;
}

void test01()
{
	goodGay gg;
	gg.visit();

}

int main() {
	test01();
	return 0;
}
*/

/*************************************************************************************************/
//��Ա��������Ԫ
/*
class Building;
class goodGay
{
public:
	goodGay();
	void visit(); //ֻ��visit������ΪBuilding�ĺ����ѣ����Է�����Building��˽������
	void visit2();
private:
	Building *building;
};

class Building
{
	//���߱�����  goodGay���е�visit��Ա���� ��Building�����ѣ����Է���˽������
	friend void goodGay::visit();

public:
	Building();
public:
	string m_SittingRoom; //����
private:
	string m_BedRoom;//����
};

Building::Building()
{
	this->m_SittingRoom = "����";
	this->m_BedRoom = "����";
}

goodGay::goodGay()
{
	building = new Building;
}

void goodGay::visit()
{
	cout << "�û������ڷ���" << building->m_SittingRoom << endl;
	cout << "�û������ڷ���" << building->m_BedRoom << endl;
}

void goodGay::visit2()
{
	cout << "�û������ڷ���" << building->m_SittingRoom << endl;
	//cout << "�û������ڷ���" << building->m_BedRoom << endl;  //����Ԫ��Ա�������ܷ���
}

void test01()
{
	goodGay  gg;
	gg.visit();
	gg.visit2();
}

int main() {
	test01();
	return 0;
}

*/