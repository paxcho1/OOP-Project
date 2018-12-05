#include "Schedule.h"
Schedule::Schedule()
{
}
Schedule::~Schedule()
{
}
int Schedule::AddSchedule(char* Schedule) {
	string Date = Schedule;
	date = Date.substr(4, 10);
	char* ptr = strtok(Schedule, " ");
	ptr = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	string time = ptr;
	int Starthour = atoi(time.substr(0, 2).c_str());
	int Startminute = atoi(time.substr(2, 4).c_str());
	int Finalhour = atoi(time.substr(4, 6).c_str());
	int Finalminute = atoi(time.substr(6, 8).c_str());
	ptr = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	string Dest_Sche = ptr;
	
	for (int hour = Starthour, int minute = Startminute; (hour == Finalhour) && (minute > Finalminute);) {
		if (minute != 59) {
			TimeLine[hour][minute] = 1;
				
			minute++;
		}
		else {
			hour++;
			minute = 0;
		}
	}
	Map_Schedule[time] = Dest_Sche;
	//추가 timeline에 추가
	return 0;
}
int Schedule::DeleteSchedule(char* Schedule) {

	string Date = Schedule;
	date = Date.substr(4, 10);
	char* ptr = strtok(Schedule, " ");
	ptr = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	string time = ptr;
	int Starthour = atoi(time.substr(0, 2).c_str());
	int Startminute = atoi(time.substr(2, 4).c_str());
	int Finalhour = atoi(time.substr(4, 6).c_str());
	int Finalminute = atoi(time.substr(6, 8).c_str());
	ptr = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	string schedule = ptr;

	if (Map_Schedule.find(time) == Map_Schedule.end()) {
		cout << "there is no such Schedule";
		return -1;
	}
	else {
			
		for (int hour = Starthour, int minute = Startminute; (hour == Finalhour) && (minute > Finalminute);) {
			if (minute != 59) {
				TimeLine[hour][minute] = 0;

				minute++;
			}
			else {
				hour++;
				minute = 0;
			}
		}
		Map_Schedule.erase(time);
	}
	return 0;
}
map<string, string> Schedule::ReturnSchedule() {
		return Map_Schedule;
}
int* Schedule::ReturnTimeLine() {
	return &TimeLine[0][0];
}
int Schedule::CheckOverlap(string time) {
	int Starthour = atoi(time.substr(0, 2).c_str());
	int Startminute = atoi(time.substr(2, 4).c_str());
	int Finalhour = atoi(time.substr(4, 6).c_str());
	int Finalminute = atoi(time.substr(6, 8).c_str());
	for (int hour = Starthour, int minute = Startminute; (hour == Finalhour) && (minute > Finalminute);) {
		if (minute != 59) {
			if (TimeLine[hour][minute] == 1) {
				return -1; //overlap exist
			}
			minute++;
		}
		else {
			hour++;
			minute = 0;
		}
	}
	return 0; //no overlap
}
int Schedule::CheckCurOverlap(string time, int Starthour, int Startminute) {
	int Finalhour = atoi(time.substr(4, 6).c_str());
	int Finalminute = atoi(time.substr(6, 8).c_str());
	for (int hour = Starthour, int minute = Startminute; (hour == Finalhour) && (minute > Finalminute);) {
		if (minute != 59) {
			if (TimeLine[hour][minute] == 1) {
				return -1; //overlap exist
			}
			minute++;
		}
		else {
			hour++;
			minute = 0;
		}
	}
	return 0; //no overlap
}