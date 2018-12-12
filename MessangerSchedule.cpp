#include "MessangerSchedule.h"
MessangerSchedule::MessangerSchedule(SOCKET client, string Id) :tool(client)
{
}
MessangerSchedule::~MessangerSchedule()
{
}
void MessangerSchedule::Schedule_invite(char* msg, SOCKET client, string Id) {//007 filename yy,mm,dd 00,00,00,00 ���� sche
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	map<string, string> schedule;
	map<string, string>::iterator siter;
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string Chat_file = (strcpy, ptr);//file = filename
	string date = strtok(NULL, " ");
	char* timeline = strtok(NULL, " ");
	string day = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	char Str[MAX_BUFFER_SIZE];
	string Sche;
	strcpy(Str, "");
	while (ptr != NULL) {
		strcat(Str, ptr);
		Sche = strcat(Str, " ");
		ptr = strtok(NULL, " ");
	}
	string message = Sche;
	string file = "c:/server/" + Id + "/schedule/daily/" + day + "/" + date + ".txt";
	tool::TxtToMap(file.c_str(), schedule);
	Schedule Daily; char* duptime;
	int D = 0, W = 0 ;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			Daily.Addmap(siter->first, siter->second);
			Daily.AddTimeLine(siter->first);
		}
		duptime = _strdup(timeline);
		//������ ��������, ������
		D = Daily.CheckOverlap(duptime);
		//�ߺ��˻�
		schedule.clear();
	}
	file = "c:/server/" + Id + "/schedule/weekly/" + day + ".txt";
	tool::TxtToMap(file.c_str(), schedule);
	Schedule Weekly;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			Weekly.Addmap(siter->first, siter->second);
			Weekly.AddTimeLine(siter->first);
		}
		duptime = _strdup(timeline);
		//������ ��������, ������
		W = Weekly.CheckOverlap(duptime);
		schedule.clear();
	}
	//group �˻�
	file = "c:/server/" + Id + "/schedule/group/" + date + ".txt";
	tool::TxtToGSche(file.c_str(), schedule);
	Schedule Group; int G = 0;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			char* dupbuf = _strdup(siter->second.c_str()); strtok(dupbuf, "|"); strtok(NULL, "|"); dupbuf = strtok(NULL, " "); 
			char* gid = strtok(dupbuf, ",");
			while (gid !=NULL) {
				if (gid == Id) {
					Group.Addmap(siter->first, siter->second);
					Group.AddTimeLine(siter->first);
				}
				gid = strtok(NULL, ",");
			}
		}
		duptime = _strdup(timeline);
		G = Group.CheckOverlap(duptime);
		schedule.clear();
	}

	//�ߺ��˻�
//�ߺ��˻�
//�����ϸ� 004 + �����߰� �Ұ����ϸ� 005
	if (D + W + G == 0)//����
	{
			// ***���� ***�� �������� �ʴ��߽��ϴ�.
			char filename[MAX_BUFFER_SIZE];
			strcpy( filename,Chat_file.c_str());
			set<char*> sid;
			set<char*>::iterator iditer;
			duptime = _strdup(timeline);
			string invite_msg = "____" + Id + " ���� " + message + "�� �������� �ʴ��߽��ϴ�.____\n" + "( " +date+ " | " + duptime + " )";
			ptr = strtok(filename,",");
			while (ptr != NULL) {
				sid.insert(ptr);
				ptr = strtok(NULL, ",");
			}
			for(iditer = sid.begin();iditer!=sid.end();iditer++){
				string str = (*iditer);
				string pathstr = "c:/server/" + str + "/chat" + str + "alarm/" + Chat_file + ".txt";
				ofstream DWrite(pathstr, ios::app);
				if (DWrite.is_open()) {
					cout << "writing file" << endl;
					DWrite << invite_msg << endl;
				}DWrite.close();

				string File_Path = "c:/server/" + str + "/schedule/group/" + date + ".txt";
				tool::TxtToGSche(file.c_str(), schedule);
				Schedule AddGroup;
				if (schedule.size() != 0) {
					for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
						AddGroup.Addmap(siter->first, siter->second);
					}
				}
				duptime = _strdup(timeline);
				AddGroup.Addmap(timeline, Chat_file + "|" + Sche + "|" + Id);//timeline|File|Sche|Id_list
				tool::GScheToTxt(File_Path.c_str(), AddGroup.Map_Schedule);
				schedule.clear();
				tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
				iter = socket_info.find(str);
				if (iter == socket_info.end()) {}
				else {
					SOCKET destsock = iter->second;
					cout << "��ǥ ���� ������" << endl;
					string cmsg = "006 " + Chat_file + " " + invite_msg;
					Sleep(30);
					Send(destsock,cmsg);
				}
				socket_info.clear();
			}
			Sleep(30);
			Send(client, "003");//���� �Ȱ�ħ ����
	}
	else
	{
		Sleep(30);
		Send(client, "004");//���� ��Ĩ ����
	}
}
void MessangerSchedule::Accept_schedule(char* msg, SOCKET client, string Id) {//008 filename yy,mm,dd 00,00,00,00 ���� sche
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	map<string, string> schedule;
	map<string, string>::iterator siter;
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string Chat_file = (strcpy, ptr);//file = filename
	string date = strtok(NULL, " ");
	char* timeline = strtok(NULL, " ");
	string day = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	char Str[MAX_BUFFER_SIZE];
	string Sche;
	strcpy(Str, "");
	while (ptr != NULL) {
		strcat(Str, ptr);
		Sche = strcat(Str, " ");
		ptr = strtok(NULL, " ");
	}
	string message = Sche;
	string file = "c:/server/" + Id + "/schedule/daily/" + day + "/" + date + ".txt";
	tool::TxtToMap(file.c_str(), schedule);
	Schedule Daily; char* duptime;
	int D = 0, W = 0;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			Daily.Addmap(siter->first, siter->second);
			Daily.AddTimeLine(siter->first);
		}
		duptime = _strdup(timeline);
		//������ ��������, ������
		D = Daily.CheckOverlap(duptime);
		//�ߺ��˻�
		schedule.clear();
	}
	file = "c:/server/" + Id + "/schedule/weekly/" + day + ".txt";
	tool::TxtToMap(file.c_str(), schedule);
	Schedule Weekly;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			Weekly.Addmap(siter->first, siter->second);
			Weekly.AddTimeLine(siter->first);
		}
		duptime = _strdup(timeline);
		//������ ��������, ������
		W = Weekly.CheckOverlap(duptime);
		schedule.clear();
	}
	//group �˻�
	file = "c:/server/" + Id + "/schedule/group/" + date + ".txt";
	tool::TxtToGSche(file.c_str(), schedule);
	Schedule Group; int G = 0;
	if (schedule.size() != 0) {
		for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
			char* dupbuf = _strdup(siter->second.c_str()); strtok(dupbuf, "|"); strtok(NULL, "|"); dupbuf = strtok(NULL, " ");
			char* gid = strtok(dupbuf, ",");
			while (gid != NULL) {
				if (gid == Id) {
					Group.Addmap(siter->first, siter->second);
					Group.AddTimeLine(siter->first);
				}
				gid = strtok(NULL, ",");
			}
		}
		duptime = _strdup(timeline);
		G = Group.CheckOverlap(duptime);
		schedule.clear();
	}

	//�ߺ��˻�
//�ߺ��˻�
//�����ϸ� 004 + �����߰� �Ұ����ϸ� 005
	if (D + W + G == 0)//����
	{
		// ***���� ***�� �������� �ʴ��߽��ϴ�.
		char filename[MAX_BUFFER_SIZE];
		set<char*> sid;
		set<char*>::iterator iditer;
		ptr = strtok(filename, ",");
		while (ptr != NULL) {
			sid.insert(ptr);
			ptr = strtok(NULL, ",");
		}
		for (iditer = sid.begin(); iditer != sid.end(); iditer++) {
			string str = (*iditer);
			string File_Path = "c:/server/" + str + "/schedule/group/" + date + ".txt";
			tool::TxtToGSche(file.c_str(), schedule);
			Schedule AddGroup; char* Party = NULL;
			if (schedule.size() != 0) {
				for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
					duptime = _strdup(timeline);
					char* dupbuf = _strdup(siter->second.c_str());
					char* cfile = strtok(dupbuf, "|"); 
					dupbuf = strtok(NULL, "|"); 
					if (strcmp(siter->first.c_str(), timeline)+strcmp(cfile,Chat_file.c_str())+strcmp(dupbuf,Str) == 0){
						Party = _strdup(siter->second.c_str());
						string list = "," + Id;
						strcat(Party, list.c_str());
						AddGroup.Addmap(siter->first, Party);
					}
					else {
						AddGroup.Addmap(siter->first, siter->second);
					}
				}
				schedule.clear();
			}
			tool::GScheToTxt(File_Path.c_str(), AddGroup.Map_Schedule);
			tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
			iter = socket_info.find(ptr);
			if (iter == socket_info.end()) {}
			else {
				SOCKET destsock = iter->second;
				cout << "��ǥ ���� ������" << endl;
				Send(destsock, "005 " + message + " " + Party);
			}
		}
		Send(client, "003");//���� �Ȱ�ħ ����
	}
	else
	{
		Send(client, "004");//���� ��ħ ����
	}
}
void MessangerSchedule::Cancel_schedule(char* msg, SOCKET client, string Id) { //�ڵ� file yymmdd 00,00,00,00 wod sche
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	map<string, string> schedule;
	map<string, string>::iterator siter;
	char* duptime;
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string Chat_file = (strcpy, ptr);//file = filename
	string date = strtok(NULL, " ");
	char* timeline = strtok(NULL, " ");
	string day = strtok(NULL, " ");
	ptr = strtok(NULL, " ");
	char Str[MAX_BUFFER_SIZE];
	string Sche;
	strcpy(Str, "");
	while (ptr != NULL) {
		strcat(Str, ptr);
		Sche = strcat(Str, " ");
		ptr = strtok(NULL, " ");
	}
	string message = Sche; 
	char filename[MAX_BUFFER_SIZE];
	strcpy(filename, Chat_file.c_str());
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	set<char*> sid;
	set<char*>::iterator iditer;
	duptime = _strdup(timeline); 
	string invite_msg = "____" + Id + " ���� " + message + "�� �������� �ʴ��߽��ϴ�.____\n" + "( " + date + " | " + duptime + " )";
	ptr = strtok(filename, ",");
	while (ptr != NULL) {
		sid.insert(ptr);
		ptr = strtok(NULL, ",");
	}
	for (iditer = sid.begin(); iditer != sid.end(); iditer++) {
		string str = (*iditer);
		char* Party = NULL;
		Schedule CancelGroup; 
		string File_Path = "c:/server/" + str + "/schedule/group/" + date + ".txt";
		tool::TxtToGSche(File_Path.c_str(), schedule);
		if (schedule.size() != 0) {
			vector<string> name;
			vector<string>::iterator niter;
			for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
				if (strcmp(siter->first.c_str(), timeline) == 0) {
					Party = _strdup(siter->second.c_str()); strtok(Party, "|"); strtok(NULL, "|"); strtok(NULL, "|");
					char* lptr = strtok(NULL, ",");
					while (lptr != NULL) {
						name.push_back(lptr);
						lptr = strtok(NULL, ",");
					}
					niter = find(name.begin(), name.end(), Id);
					name.erase(niter);
					ZeroMemory(Party, MAX_BUFFER_SIZE);
					string dup = (string)timeline + "|"  + Chat_file + "|" + Sche + "|";
					strcpy(Party, dup.c_str()); 
					niter = name.begin();
					strcat(Party, (*niter).c_str()); 
					++niter;
					for (niter; niter != name.end(); ++niter) {
						strcat(Party, ",");
						strcat(Party, (*niter).c_str());
					}
					// ,Id ���� �� vector ���� vector string�� ����
					CancelGroup.Addmap(siter->first, Party);
				}
				else {
					CancelGroup.Addmap(siter->first, siter->second);
				}
				tool::GScheToTxt(File_Path.c_str(), CancelGroup.Map_Schedule);
			}
			schedule.clear();
		}
	}
}