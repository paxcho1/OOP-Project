#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
class DailySchedule {
private:
	int TimeLine[24][60] = { 0, };
	map<string, string> Map_Schedule;
	string date;
public:
	DailySchedule()
	{

	};
	~DailySchedule()
	{

	}
	int AddSchedule(char* Schedule);
	int DeleteSchedule(char* Schedule);
	string FindSchedule() {

	}
	map<string, string> ReturnSchedule();
	int* ReturnTimeLine();

};