#include "stdafx.h"

#include "Single.h"


Single* Single::interface = NULL;

Single::Single()
{
	//if(interface == Null)
	//{
	//	interface =new Single();
	//} ���캯���ﲻ�ܳ�ʼ�� static����
}
Single* Single::getinerface()
{
	if (interface == NULL)
	{
		interface = new Single();
	}
	return interface;
}