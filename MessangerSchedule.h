#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>
#include "Tool.h"
#include "Alarm.h"
#include "AddFriends.h"
#include "MakeChat.h"
#include "Schedule.h"
#include <stdlib.h>
#pragma comment(lib,"ws2_32")
using namespace std;
class MessangerSchedule :public tool
{
private:
	SOCKET client;
	string Id;
public:
	MessangerSchedule(SOCKET client, string Id);
	~MessangerSchedule();
	void Schedule_invite(char* msg);
	void Accept_schedule(char* msg);
};