#include "TimeTable.h"
TimeTable::TimeTable(SOCKET client, string id) :tool(client) {

}
TimeTable::~TimeTable() {

}

int TimeTable::table(SOCKET client, string id) {
	while (1) {
		char buf[MAX_BUFFER_SIZE];
		ZeroMemory(buf, MAX_BUFFER_SIZE);
		int byteIn = recv(client, buf, MAX_BUFFER_SIZE, 0);
		string code = buf;
		code = code.substr(0, 3);
		//send class 랑 recv 클래스 만들기
		if (byteIn <= 0) {
			break;
		}
		else {
			if (strcmp(code.c_str(), "000") == 0) {//000 yymmdd 요일 //string recv client의 일일 시간표 확인 요청 해당 시간표를 보낸다
				map<string, string> Sche;
				map<string, string>::iterator iter;
				strtok(buf, " ");
				char* date = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				string file = "c:/server/" + id + "/schedule/daily/" + day + "/" + date + ".txt";
				tool::TxtToMap(file.c_str(),Sche);
				Schedule Daily;
				if (Sche.size() != 0) {
					for (iter = Sche.begin(); iter != Sche.end(); ++iter) {
						Daily.Addmap((*iter).first, (*iter).second);
					}
					for (iter = Daily.Map_Schedule.begin(); iter != Daily.Map_Schedule.end(); ++iter) {
						string msg;
						msg = "001 " + iter->first + " " + iter->second;
						Send(client, msg);
					}
				}Send(client, "000");
				Sche.clear();
				file = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
				tool::TxtToMap(file.c_str(), Sche);
				Schedule Weekly;
				if (Sche.size() != 0) {
					for (iter = Sche.begin(); iter != Sche.end(); ++iter)
						Weekly.Addmap((*iter).first, (*iter).second);
					for (iter = Weekly.Map_Schedule.begin(); iter == Weekly.Map_Schedule.end(); ++iter) {
						string msg;
						msg = "003 " + iter->first + " " + iter->second;
						Send(client, msg);
					}
				}Send(client, "002");
			}
			else if (strcmp(code.c_str(), "001") == 0) {//MessangerIn
				Alarm alarm(client, id);
				alarm.Messanger(client, id);
				Messanger messanger(client, id);
				messanger.in(client, id);
			}
			else if (strcmp(code.c_str(), "002") == 0) {//002 yymmdd 00,00,00,00 요일 일정 recv /client의 daily 일정 추가 요청 자신의 일정을 확인하고 추가 가능 불가 여부를 보낸다.
				map<string, string> schedule;
				map<string, string>::iterator iter;
				strtok(buf, " ");
				char* date = strtok(NULL, " ");
				char* timeline = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				char* Dest_Sche = strtok(NULL, " "); 
				char* duptime;
				string file = "c:/server/" + id + "/schedule/daily/" + day + "/" + date + ".txt";
				tool::TxtToMap(file.c_str(), schedule);
				Schedule Daily;
				int D = 0, W = 0;
				if (schedule.size() != 0) {
					for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
						Daily.Addmap(iter->first, iter->second);
						Daily.AddTimeLine(iter->first);
					}
					duptime = _strdup(timeline);
					//파일이 열렸으면, 있으면
					D = Daily.CheckOverlap(duptime);
					//중복검사
					schedule.clear();
				}
				file = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
				tool::TxtToMap(file.c_str(), schedule);
				Schedule Weekly;
				if (schedule.size() != 0) {
					for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
						Weekly.Addmap(iter->first, iter->second);
						Weekly.AddTimeLine(iter->first);
					}
					duptime = _strdup(timeline);
					//파일이 열렸으면, 있으면
					W = Weekly.CheckOverlap(duptime);
					duptime = _strdup(timeline);
				}
					//중복검사
				//중복검사
				//가능하면 004 + 일정추가 불가능하면 005
				if ((D+W)==0)//성공
				{
					file = "c:/server/" + id + "/schedule/daily/" + day + "/" + date + ".txt";
					string AddT = duptime;
					string AddS = Dest_Sche;
					Daily.Addmap(AddT, Dest_Sche);
					tool::MapToTxt(file.c_str(), Daily.Map_Schedule);
					Send(client, "004");
				}
				else
				{
					Send(client, "005");
				}
			}
			else if (strcmp(code.c_str(), "003") == 0) {//003 yymmdd 00000000 요일 일정 // 해당 날짜의 일정 삭제
				map<string, string> Sche;
				map<string, string>::iterator iter;
				strtok(buf, " ");
				char* date = strtok(NULL, " "); 
				char* time = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				string file = "c:/server/" + id + "/schedule/daily/" + day + "/" + date + ".txt";
				Schedule Daily;
				tool::TxtToMap(file.c_str(), Sche);
				if (Sche.size() != 0) {
					for (iter = Sche.begin(); iter != Sche.end(); ++iter) {
						Daily.Addmap((*iter).first, (*iter).second);
					}
					Daily.DeleteSchedule(time);
				}
				tool::MapToTxt(file.c_str(), Daily.Map_Schedule);
				//토큰분활
				//해당 일정 삭제
			}
			else if (strcmp(code.c_str(), "004") == 0) {//004 yymmdd 00000000 요일 일정 // 해당 요일의 일정 삭제
				map<string, string> Sche;
				map<string, string>::iterator iter; 
				strtok(buf, " ");
				strtok(NULL, " ");
				char* time = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				string file = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
				Schedule Weekly;
				tool::TxtToMap(file.c_str(), Sche);
				if (Sche.size() != 0) {
					for (iter = Sche.begin(); iter != Sche.end(); ++iter) {
						Weekly.Addmap((*iter).first, (*iter).second);
					}
					Weekly.DeleteSchedule(time);
				}
				tool::MapToTxt(file.c_str(), Weekly.Map_Schedule);
				// 해당 일정 삭제
			}
			else if (strcmp(code.c_str(), "005") == 0) {//005 yymmdd 00000000 요일 일정 시간표 추가 
				map<string, string> schedule;
				map<string, string>::iterator iter; 
				int error = 0;
				int result = 0;
				string msg;
				strtok(buf, " ");
				int Cur_Date = atoi(strtok(NULL, " "));
				char* Time = strtok(NULL, " ");
				char* Dup_Time = _strdup(Time);
				char* day = strtok(NULL, " ");
				char* Dest_Sche = strtok(NULL, " ");
				Schedule Weekly;
				string Filepath = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
				tool::TxtToMap(Filepath.c_str(), schedule);
				if (schedule.size() != 0){
					for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
						Weekly.Addmap((*iter).first, (*iter).second);
						Weekly.AddTimeLine((*iter).first);
					}
					result = Weekly.CheckOverlap(Dup_Time);
				}
				if (result == -1){
					msg = "009";
					Send(client, msg);
					error++;
				}
				else{
					string pathstr = "c:/server/" + id + "/schedule/daily/" + day + "/*.txt"; 
					string Filepath = "c:/server/" + id + "/schedule/weekly/" + day + ".txt";
				char path[255];
				strcpy(path, pathstr.c_str());
				WIN32_FIND_DATA FindData;
				HANDLE hFind;
				hFind = FindFirstFile((LPCSTR)path, &FindData);
				if (hFind == INVALID_HANDLE_VALUE)//file에 아무것도 없을때
				{
					cout << "No file in directory!" << endl;//
					send(client, "endfile", MAX_BUFFER_SIZE, 0);
				}
				else {
					do{
						cout << FindData.cFileName << endl;
						int File_Date = atoi(FindData.cFileName);
						if (Cur_Date > File_Date) {}
						else if (Cur_Date < File_Date) {
							//현재 날짜 이후 파일들
							Schedule Find_File;
							string File_Date = FindData.cFileName;
							File_Date = File_Date.substr(0, 6);
							string Filepath = "c:/server/" + id + "/schedule/daily/" + day + "/" + FindData.cFileName;
							tool::TxtToMap(Filepath.c_str(), schedule);
							if (schedule.size() != 0) {
								for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
									Find_File.Addmap((*iter).first, (*iter).second);
									Find_File.AddTimeLine((*iter).first);
								}

								Dup_Time = _strdup(Time);
								result = Find_File.CheckOverlap(Dup_Time);
							}
							if (result == -1) {
								msg = "008 " + File_Date;
								Send(client, msg);
								error++;
							}
						}
						else {
							//현재날짜로 파일 검색됨 심층분석
							time_t curr_time;
							struct tm *curr_tm;
							curr_time = time(NULL);
							curr_tm = localtime(&curr_time);
							Schedule Find_File;
							string File_Date = FindData.cFileName;
							File_Date = File_Date.substr(0, 6);
							string Filepath = "c:/server/" + id + "/schedule/daily/" + day + "/" + FindData.cFileName;
							tool::TxtToMap(Filepath.c_str(), schedule);
							if (schedule.size() != 0) {
								for (iter = schedule.begin(); iter != schedule.end(); ++iter) {
									Find_File.Addmap((*iter).first, (*iter).second);
									Find_File.AddTimeLine((*iter).first);
								}
								Dup_Time = _strdup(Time);
								result = Find_File.CheckCurOverlap(Dup_Time, curr_tm->tm_hour, curr_tm->tm_min);
							}
							if (result == -1) {
								msg = "008 " + File_Date;
								Send(client, msg);
								error++;
							}
						}
						schedule.clear();
					} while (FindNextFile(hFind, &FindData));
				}
					if (error == 0) {
						Send(client, "006");
						tool::TxtToMap(Filepath.c_str(), Weekly.Map_Schedule);
						Dup_Time = _strdup(Time);
						Weekly.Addmap(Dup_Time, Dest_Sche);
						tool::MapToTxt(Filepath.c_str(), Weekly.Map_Schedule);
						schedule.clear();
					}
					else{
						Send(client, "007");
					}
				}
				//while 해당 요일 앞으로 일정 폴더를 전부 검색 할 때까지{
				//중복검사후 중복이면 불가 날짜;
				//}
				//가능하면 000 + 일정추가 불가능하면 001 +  불가 날짜
			}
		}
	}
	return 0;
}