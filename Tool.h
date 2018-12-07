#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <direct.h>
#include <mutex>
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
#include "Schedule.h"
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
	int DailyScheduleToFile(Schedule &Ds, string Id, string date, string day);
	int WeeklyScheduleToFile(Schedule &Ds, string Id, string day);
	int FileToDailyScheduleClass(Schedule &Ds, string Id, string date,string day);
	int FileToWeeklyScheduleClass(Schedule &Ds, string Id, string day);
	int TokenizingString();
};
