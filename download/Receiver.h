#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tool.h"
#define MAX_BUFFER_SIZE 4092
using namespace std;
class Receiver
{
private:
	SOCKET server;
	string Id;
	char buf[MAX_BUFFER_SIZE];
public:
	Receiver(SOCKET server, string Id);
	~Receiver();
	int Messanger(SOCKET server, string Id);
	int Newmsg(SOCKET server,string Id, string file, string message);
	string Get(SOCKET server, string Id, char* buf);
	int Recv(SOCKET client, char* buf);
};

