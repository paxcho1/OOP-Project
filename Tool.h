#pragma once
#include <WinSock2.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include "Alarm.h"
#define MAX_BUFFER_SIZE 4092
using namespace std;
class tool// recv와 send를 사용하기 쉽게 만들어줌
{
public:
	SOCKET client;
	char buf[MAX_BUFFER_SIZE];
	tool(SOCKET client);
	~tool();
	void splitString(vector<string> &v_str, const string &str, const char ch);
	int Recv(SOCKET client, char buf[]);
	void Send(SOCKET client, string msg);
	void VectorToTxt(const char* fileName, vector<string> &Vector);
	void TxtToVector(const char* fileName, vector<string> &Vector);
	void MapToTxt(const char* fileName, map<string, string> &Map);
	void TxtToMap(const char* fileName, map<string, string> &Map);
	void SocketToTxt(const char* fileName, map<string, SOCKET> &Map);
	void TxtToSocket(const char* fileName, map<string, SOCKET> &Id_Socket);
	string MessangerRecv(SOCKET client, string Id, char buf[]);
	void ClassToFile(DailySchedule &Ds, string Id);
	void FileToClass(DailySchedule &Ds, string Id);
};
