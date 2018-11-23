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
class AddFriends:public tool
{
private:
	string Id;
	SOCKET client;
public:
	AddFriends(SOCKET client, string Id);
	~AddFriends();
	int Send_invite(SOCKET client, string Id);
};

