#include "MessangerSchedule.h"
MessangerSchedule::MessangerSchedule(SOCKET client, string Id) :tool(client)
{
}
MessangerSchedule::~MessangerSchedule()
{
}
void MessangerSchedule::Schedule_invite(char* msg) {//007 filename yymmdd 00,00,00,00 ���� sche
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	map<string, string> schedule;
	map<string, string>::iterator siter;
	vector<string> name;
	name.push_back(Id);
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string file = (strcpy, ptr);//file = filename
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

	//�ߺ��˻�
//�ߺ��˻�
//�����ϸ� 004 + �����߰� �Ұ����ϸ� 005
	if (D + W  == 0)//����
	{
		//group �˻�
		file = "c:/server/" + Id + "/schedule/group/" + date + ".txt";
		tool::TxtToMap(file.c_str(), schedule);
		Schedule Group; int G = 0;
		if (schedule.size() != 0) {
			for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
				Group.Addmap(siter->first, siter->second);
				Group.AddTimeLine(siter->first);
			}
			duptime = _strdup(timeline);
			G = Group.CheckOverlap(duptime);
			schedule.clear();
		}
		if (G == 0) {
			// ***���� ***�� �������� �ʴ��߽��ϴ�.
			char filename[MAX_BUFFER_SIZE];
			strcpy(filename, file.c_str());
			string invite_msg = "\t" + Id + " ���� " + message + "�� �������� �ʴ��߽��ϴ�.";
			ptr = strtok(filename, ",");
			while (ptr != NULL) {
				string str = ptr;
				string pathstr = "c:/server/" + str + "/chat" + str + "alarm/" + file + ".txt";
				ofstream DWrite(pathstr, ios::app);
				if (DWrite.is_open()) {
					cout << "writing file" << endl;
					DWrite << invite_msg << endl;
				}DWrite.close();
				string File_Path = "c:/server/" + str + "/schedule/group/" + date + ".txt";
				tool::VectorToTxt(File_Path.c_str(), name);
				tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info); iter = socket_info.find(ptr);
				if (iter == socket_info.end()) {}
				else {
					SOCKET destsock = iter->second;
					cout << "��ǥ ���� ������" << endl;
					Send(destsock, "006 " + file + " " + invite_msg);
				}
				socket_info.clear();
			}
			Send(client, "003");
		}
		else {
			Send(client, "004");
		}
	}
	else
	{
		Send(client, "004");
	}

	
}
void MessangerSchedule::Accept_schedule(char* msg) {
	map<string, string> schedule;
	map<string, string>::iterator siter;
	vector<string> name;
	name.push_back(Id);
	char* ptr = strtok(msg, " ");
	ptr = strtok(NULL, " ");
	string file = (strcpy, ptr);//file = filename
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

	//�ߺ��˻�
	//�ߺ��˻�
	//�����ϸ� 004 + �����߰� �Ұ����ϸ� 005
	if (D + W == 0)//����
	{
		//group �˻�
		file = "c:/server/" + Id + "/schedule/group/" + date + ".txt";
		tool::TxtToMap(file.c_str(), schedule);
		Schedule Group; int G = 0;
		if (schedule.size() != 0) {
			for (siter = schedule.begin(); siter != schedule.end(); ++siter) {
				Group.Addmap(siter->first, siter->second);
				Group.AddTimeLine(siter->first);
			}
			duptime = _strdup(timeline);
			G = Group.CheckOverlap(duptime);
			schedule.clear();
		}
	}
		if (G == 0) {
		else {
			Send(client, "004");
		}
	}
	else
	{
		Send(client, "004");
	}


}