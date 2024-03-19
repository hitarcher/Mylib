#include "stdafx.h"

#include "Single.h"


Single* Single::interface = NULL;

Single::Single()
{
	//if(interface == Null)
	//{
	//	interface =new Single();
	//} 构造函数里不能初始化 static变量
}
Single* Single::getinerface()
{
	if (interface == NULL)
	{
		interface = new Single();
	}
	return interface;
}