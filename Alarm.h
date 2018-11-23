#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <algorithm>
#include "Tool.h"
#include <stdlib.h>
#pragma comment(lib,"ws2_32")
using namespace std;
class Alarm:public tool
{
private:
	string Id;
	SOCKET client;
public:
	Alarm(SOCKET client,string Id);
	~Alarm();
	int in(SOCKET client,string Id);
};

