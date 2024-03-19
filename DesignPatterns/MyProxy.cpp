#include "stdafx.h"
#include "MyProxy.h"

void Cheater::takeTest()
{
	cout << "Cheater take test" << endl;
}



Proxy::Proxy(Student &stu)
	:pch(stu)
{

}
void Proxy::takeTest()
{
	pch.takeTest();
}