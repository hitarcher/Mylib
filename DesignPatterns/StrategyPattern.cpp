#include"stdafx.h"
#include "StrategyPattern.h"

Traveler ::Traveler(Travel *way1)
	:ways(way1)
{}

void Traveler::taketravl()
{
	this->ways->travel();
}