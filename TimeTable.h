#pragma once
#include "Tool.h"
#include <iostream>
#include <direct.h>
#include <WinSock2.h>
#include <string>

#define MAX_BUFFER_SIZE 4092
using namespace std;

class TimeTable : public tool {
public:
	TimeTable(SOCKET client, string id)
	{
	};
	~TimeTable()
	{

	}
	int table(SOCKET client, string id);

};
