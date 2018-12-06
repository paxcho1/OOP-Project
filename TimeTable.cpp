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
		//send class �� recv Ŭ���� �����
		if (byteIn <= 0) {
			break;
		}
		else {
			if (strcmp(code.c_str(), "000") == 0) {//000 yymmdd ���� //string recv client�� ���� �ð�ǥ Ȯ�� ��û �ش� �ð�ǥ�� ������
				map<string, string>::iterator iter;
				strtok(buf, " ");
				char* date = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				Schedule Daily;
				int result = FileToDailyScheduleClass(Daily, id, date,day);
				if (result == 0) {
					for (iter = Daily.ReturnSchedule().begin(); iter == Daily.ReturnSchedule().end(); iter++) {
						string msg;
						msg = "001 " + iter->first + " " + iter->second;
						Send(client, msg);
						Daily.~Schedule();
					}
				}Send(client, "000");
				Schedule Weekly;
				result = FileToWeeklyScheduleClass(Weekly,id,day);
				if (result == 0) {
					for (iter = Weekly.ReturnSchedule().begin(); iter == Weekly.ReturnSchedule().end(); iter++) {
						string msg;
						msg = "003 " + iter->first + " " + iter->second;
						Send(client, msg);
						Weekly.~Schedule();
					}
				}Send(client, "002");
			}
			else if (strcmp(code.c_str(), "001") == 0) {
				//MessangerIn
				Alarm alarm(client, id);
				alarm.Messanger(client, id);
				Messanger messanger(client, id);
				messanger.in(client, id);
			}
			else if (strcmp(code.c_str(), "002") == 0) {//002 yymmdd 00000000 ���� ���� recv /client�� ���� �߰� ��û �ڽ��� ������ Ȯ���ϰ� �߰� ���� �Ұ� ���θ� ������.
				map<string, string> schedule;
				map<string, string>::iterator iter;
				strtok(buf, " ");
				char* date = strtok(NULL, " ");
				char* timeline = strtok(NULL, " ");
				Schedule Daily;
				char* day = strtok(NULL, " ");
				char* Dest_Sche = strtok(NULL, " ");

				int D = 0, W = 0;
				if (FileToDailyScheduleClass(Daily, id, date, day) == -1) {
					cout << "no file or fail to open";
				}
				else {
					//������ ��������, ������
					D = Daily.CheckOverlap(timeline);
					//�ߺ��˻�
				}
				
				Schedule Weekly;

				if (FileToWeeklyScheduleClass(Weekly, id, day) == -1) {
					cout << "no file or fail to open";
				}
				else {
					//������ ��������, ������
					W = Weekly.CheckOverlap(timeline);
					//�ߺ��˻�
				}
				
				char* sh = strtok(timeline, ",");
				char* sm = strtok(NULL, ",");
				char* fh = strtok(NULL, ",");
				char* fm = strtok(NULL, ",");
				//�ߺ��˻�
				//�����ϸ� 004 + �����߰� �Ұ����ϸ� 005
				if ((D+W)==0)//����
				{
					Daily.AddSchedule(sh,sm,fh,fm,Dest_Sche);

					if (DailyScheduleToFile(Daily, id, date, day) == -1) {
						cout << "file didn't open";
						exit(1);
					}
					Send(client, "004");
				}
				else
				{
					Send(client, "005");
				}
			}
			else if (strcmp(code.c_str(), "003") == 0) {//003 yymmdd 00000000 ���� ���� // �ش� ��¥�� ���� ����

				strtok(buf, " ");
				char* date = strtok(NULL, " "); 
				strtok(buf, " ");
				char* day = strtok(NULL, " ");
				char* Dele_Dest = strtok(NULL, " ");
				Schedule Daily;
				if (FileToDailyScheduleClass(Daily, id, date, day) == -1) {
					cout << "file didn't open";
					exit(1);
				}
				Daily.DeleteSchedule(buf);
				//��ū��Ȱ
				//�ش� ���� ����
			}
			else if (strcmp(code.c_str(), "004") == 0) {//004 yymmdd 00000000 ���� ���� // �ش� ������ ���� ����
				strtok(buf, " ");
				strtok(NULL, " ");
				strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				Schedule Weekly;
				if (FileToWeeklyScheduleClass(Weekly, id, day) == -1) {
					cout << "file didn't open";
					exit(1);
				}
				Weekly.DeleteSchedule(buf);
				// �ش� ���� ����
			}
			else if (strcmp(code.c_str(), "005") == 0) {//005 yymmdd 00000000 ���� ���� �ð�ǥ �߰� 
				int error = 0;
				strtok(buf, " ");
				strtok(NULL, " ");
				char* Time = strtok(NULL, " ");
				char* day = strtok(NULL, " ");
				char* Dest_Sche = strtok(NULL, " ");
				int Cur_Date = atoi(Dest_Sche);
				string pathstr = "c:/server/" + id + "/schedule/daily/" + day + "/*.txt"; string Filepath;
				char path[255];
				strcpy(path, pathstr.c_str());
				WIN32_FIND_DATA FindData;
				HANDLE hFind;
				hFind = FindFirstFile((LPCSTR)path, &FindData);
				if (hFind == INVALID_HANDLE_VALUE)//file�� �ƹ��͵� ������
				{
					cout << "No file in directory!" << endl;//
					send(client, "endfile", MAX_BUFFER_SIZE, 0);
				}
				else {
					cout << FindData.cFileName << endl;
					int File_Date = atoi(FindData.cFileName);
					if (Cur_Date>File_Date) {}
					else if(Cur_Date<File_Date) {
						//���� ��¥ ���� ���ϵ�
						Schedule Find_File;
						string File_Date = FindData.cFileName;
						File_Date = File_Date.substr(0, 6);
						if (FileToDailyScheduleClass(Find_File, id, File_Date, day) == -1) {
							cout << "file didn't open";
							
						}
						int result = Find_File.CheckOverlap(Time);
						if (result == -1) {
							string msg = "008 " + File_Date;
							Send(client, msg);
							error++;
						}
					}
					else {
						//���糯¥�� ���� �˻��� �����м�
						time_t curr_time;
						struct tm *curr_tm;
						curr_time = time(NULL);
						curr_tm = localtime(&curr_time);
						Schedule Find_File;
						string File_Date = FindData.cFileName;
						File_Date = File_Date.substr(0, 6);
						if (FileToDailyScheduleClass(Find_File, id, File_Date, day) == -1) {
							cout << "file didn't open";
							
						}
						int result = Find_File.CheckCurOverlap(Time, curr_tm->tm_hour,curr_tm->tm_min);
						if (result == -1) {
							string msg = "008 " + File_Date;
							Send(client, msg);
							error++;
						}
					}
				}
				Send(client, "007");
				if (error == 0) {
					Schedule Weekly;
					if (FileToWeeklyScheduleClass(Weekly, id, day) == -1) {
						cout << "file didn't open";
						
					}
					char* sh = strtok(Time, ",");
					char* sm = strtok(NULL, ",");
					char* fh = strtok(NULL, ",");
					char* fm = strtok(NULL, ",");
					Weekly.AddSchedule(sh,sm,fh,fm,Dest_Sche);
					if (WeeklyScheduleToFile(Weekly, id, day) == -1) {
						cout << "file didn't open";
					}
					Send(client, "006");
				}
				//while �ش� ���� ������ ���� ������ ���� �˻� �� ������{
				//�ߺ��˻��� �ߺ��̸� �Ұ� ��¥;
				//}
				//�����ϸ� 000 + �����߰� �Ұ����ϸ� 001 +  �Ұ� ��¥
			}
		}
	}
	return 0;
}