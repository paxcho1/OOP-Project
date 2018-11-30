#include "TimeTable.h"


class DailySchedule {
private:
	int TimeLine[24][60] = { 0, };
	map<string, string> Map_Schedule;
public:
	DailySchedule()
	{

	};
	~DailySchedule()
	{

	}
	int AddSchedule(string Time, string Schedule) {
		int Shour, Sminute, Fhour, Fminute, Check;
		vector<string>V_Time;
		vector<string> V_Stime;
		vector<string> V_Ftime;
		vector<string>::iterator tIter = V_Time.begin();
		vector<string>::iterator StIter = V_Stime.begin();
		vector<string>::iterator FtIter = V_Ftime.begin();
		//spilt input time into StartTime and FinishTime
		tool::splitString(V_time, Time, '~');
		
		tool::splitString(V_Stime, *(tIter), ':');
		tool::splitString(V_Ftime, *(++tIter), ':');

		Shour = stoi(*(StIter));
		Sminute = stoi(*(++StIter));
		Fhour = stoi(*(FtIter));
		Fminute = stoi(*(++FtIter));

		for (int i = Shour; i < Fhour; i++) {
			for (int j = Sminute; j < Fminute; j++) {
				Check += TimeLine[i][j];
			}
		}
		if (Check != 0) {
			cout << "overlap schedule";;
			return -1;
		}
		else {
			for (int i = Shour; i < Fhour; i++) {
				for (int j = Sminute; j < Fminute; j++) {
					TimeLine[i][j] = 1;
				}
			}
			Map_Schedule[Schedule] = Time;
			cout << "added schedule";
		}
		
		return 0;
	}
	int DeleteSchedule(string Schedule) {
		int Shour, Sminute, Fhour, Fminute, Check;
		vector<string>V_Time;
		vector<string> V_Stime;
		vector<string> V_Ftime;
		vector<string>::iterator tIter = V_Time.begin();
		vector<string>::iterator StIter = V_Stime.begin();
		vector<string>::iterator FtIter = V_Ftime.begin();
		
		
		
		if (map<string, string>::iterator ScheduleIter = Map_Schedule.find(Schedule) == Map_Schedule.end()) {
			cout << "there is no such Schedule"
				return -1;
		}
		else {
			
			tool::splitString(V_time, ScheduleIter->second, '~');

			tool::splitString(V_Stime, *(tIter), ':');
			tool::splitString(V_Ftime, *(++tIter), ':');

			Shour = stoi(*(StIter));
			Sminute = stoi(*(++StIter));
			Fhour = stoi(*(FtIter));
			Fminute = stoi(*(++FtIter));
			Map_Schedule.erase(Schedule);

			for (int i = Shour; i < Fhour; i++) {
				for (int j = Sminute; j < Fminute; j++) {
					TimeLine[i][j] = 0;
				}
			}
		}
		return 0;
	}
	string FindSchedule() {

	}
	map<string,string> ReturnSchedule() {
		return Map_Schedule;
	}
	int* ReturnTimeLine() {
		return TimeLine;
	}

};
int TimeTable::table(SOCKET client, string id) {
	vector<DailySchedule> WeeklySchedule;
	DailySchedule Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday;
	
	return 0;
}
