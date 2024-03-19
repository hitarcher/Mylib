#include "stdafx.h"
#include "container.h"
#include <vector>
#include <map>
void testContainer()
{
	map<string, vector<string>>families;
	vector<string>firstname;
	firstname.push_back("john");
	firstname.push_back("jack");
	firstname.push_back("red");
	families["lion"] = firstname;
	families["bird"] = firstname;
	for (auto p : families)
	{
		for (auto v:p.second)
		{
			cout << p.first.c_str() << v.c_str() << endl;
		}

	}
}