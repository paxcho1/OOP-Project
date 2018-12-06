#include "Schedule.h"
Schedule::Schedule()
{
}
Schedule::~Schedule()
{
}
int Schedule::AddSchedule(string sh,string sm, string fh, string fm,string Schedule) {
	int Starthour = atoi(sh.c_str());
	int Startminute = atoi(sm.c_str());
	int Finalhour = atoi(fh.c_str());
	int Finalminute = atoi(fm.c_str());
	string Dest_Sche = Schedule;
	int hour;
	int minute;
	for (hour = Starthour, minute = Startminute; (hour != Finalhour) || (minute <= Finalminute);) {
		if (minute != 60) {
			TimeLine[hour][minute] = 1;
				
			minute++;
		}
		else {
			hour++;
			minute = 0;
		}
	}
	string time = sh + sm + fh + fm;
	Map_Schedule[time] = Dest_Sche;
	//추가 timeline에 추가
	return 0;
}
int Schedule::DeleteSchedule(string time) {
	int Starthour = atoi(time.substr(0, 2).c_str());
	int Startminute = atoi(time.substr(2, 4).c_str());
	int Finalhour = atoi(time.substr(4, 6).c_str());
	int Finalminute = atoi(time.substr(6, 8).c_str());
	if (Map_Schedule.find(time) == Map_Schedule.end()) {
		cout << "there is no such Schedule";
		return -1;
	}
	else {
		int hour;
		int minute;
		for (hour = Starthour, minute = Startminute; (hour != Finalhour) && (minute <= Finalminute);) {
			if (minute != 60) {
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
int Schedule::CheckOverlap(char* time) {
	char* sh = strtok(time, ",");
	char* sm = strtok(NULL, ",");
	char* fh = strtok(NULL, ",");
	char* fm = strtok(NULL, ",");
	int hour; int minute;
	int Starthour = atoi(sh);
	int Startminute = atoi(sm);
	int Finalhour = atoi(fh);
	int Finalminute = atoi(fm);
	for ( hour = Starthour, minute = Startminute; (hour == Finalhour) && (minute > Finalminute);) {
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
int Schedule::CheckCurOverlap(char* time, int Starthour, int Startminute) {
	char* sh = strtok(time, ",");
	char* sm = strtok(NULL, ",");
	char* fh = strtok(NULL, ",");
	char* fm = strtok(NULL, ",");
	int Finalhour = atoi(fh);
	int Finalminute = atoi(fm);
	int hour; int minute;
	for (hour = Starthour, minute = Startminute; (hour == Finalhour) && (minute > Finalminute);) {
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