#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
class Schedule {
private:
	int TimeLine[24][60] = { 0, };
	map<string, string> Map_Schedule;
	string date;
public:
	Schedule();
	~Schedule();
	int AddSchedule(string sh,string sm, string fh, string fm, string Schedule);
	int DeleteSchedule(string time);
	map<string, string> ReturnSchedule();
	int* ReturnTimeLine(); 
	int CheckOverlap(char* time); 
	int CheckCurOverlap(char* time, int Starthour, int Startminute);

};