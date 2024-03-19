#include "stdafx.h"
#include "watcher.h"
Trainer::Trainer()
	:num(0)
{
	memset(an, 0, sizeof(Animal*));
}

void Trainer::addAn(Animal *a1)
{
	an[num] = a1;
	num++;
}
void Trainer::deleteAN(Animal *a1)
{
	bool flag = false;
	for (int i=0;i<num;i++)
	{
		if (an[i] == a1)
		{
			an[i] = 0;
			an[i] = an[num - 1];
			num--;
			flag = true;
		}
	}
}
void Trainer::allAct()
{
	for (int i=0 ;i<num;i++)
	{
		an[i]->act();
	}
}

