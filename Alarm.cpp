#include "Alarm.h"



Alarm::Alarm(SOCKET client,string Id)
{
}


Alarm::~Alarm()
{
}
int Alarm::Messanger(SOCKET client, string Id) {//client�� id�� �̿��� alarm������ ������� ����
	char path[255];
	int cnt = 0;
	do {
		string pathstr;
		if (cnt == 0)
			pathstr = "c:/server/" + Id + "/*.txt";
		else if (cnt == 1)
			pathstr = "c:/server/" + Id + "/chat" + Id + "alarm/*.txt";
		else if (cnt ==2)
			pathstr = "c:/server/" + Id + "/friends" + Id + "/*.txt";
		else if (cnt ==3)
			pathstr = "c:/server/" + Id + "/friends" + Id + "invite/*.txt";
		else if (cnt ==4)
			pathstr = "c:/server/" + Id + "/friends" + Id + "alarm/*.txt";
		strcpy(path, pathstr.c_str());
		string Filepath;
		WIN32_FIND_DATA FindData;
		HANDLE hFind;
		hFind = FindFirstFile((LPCSTR)path, &FindData);
		if (hFind == INVALID_HANDLE_VALUE)//file�� �ƹ��͵� ������
		{
			cout << "No file in directory!" << endl;//
			send(client, "endfile", MAX_BUFFER_SIZE, 0);
		}
		else {
			do
			{
				cout << FindData.cFileName << endl;
				//Send(client, "File");
				send(client, FindData.cFileName, MAX_BUFFER_SIZE, 0);
				if (cnt == 0)
					Filepath = "c:/server/" + Id + "/" + FindData.cFileName;
				else if (cnt == 1)
					Filepath = "c:/server/" + Id + "/chat" + Id + "alarm/" + FindData.cFileName;
				else if (cnt == 2)
					Filepath = "c:/server/" + Id + "/friends" + Id + "/" + FindData.cFileName;
				else if (cnt == 3)
					Filepath = "c:/server/" + Id + "/friends" + Id + "invite/" + FindData.cFileName;
				else if (cnt == 4)
					Filepath = "c:/server/" + Id + "/friends" + Id + "alarm/" + FindData.cFileName;
				FILE *fp = fopen(Filepath.c_str(), "rb");
				if (fp == NULL)
					cout << "file error" << endl;
				fseek(fp, 0, SEEK_END);
				int totalbytes = ftell(fp);
				send(client, to_string(totalbytes).c_str(), MAX_BUFFER_SIZE, 0);
				char buf[MAX_BUFFER_SIZE];
				ZeroMemory(buf, MAX_BUFFER_SIZE);
				int numread;
				int numtotal = 0;
				rewind(fp);//���� �����͸� ���� ������ �̵�
				while (1) {
					numread = fread(buf, 1, MAX_BUFFER_SIZE, fp);
					if (numread > 0) {
						if (MAX_BUFFER_SIZE >= totalbytes) {
							send(client, buf, MAX_BUFFER_SIZE, 0);
							totalbytes = 0;
						}
						else if (MAX_BUFFER_SIZE < totalbytes) {
							send(client, buf, MAX_BUFFER_SIZE, 0);
							totalbytes -= MAX_BUFFER_SIZE;
						}
					}
					else if (numread == 0 && 0 == totalbytes) {
						cout << " �������ۿϷ�!" << endl;
						break;
					}
					else {
						cout << " ���� ����� ����" << endl;
						break;
					}
				}
				fclose(fp);
				// ��������//client ���ο� alarm ���� ����
				//�Ŀ� client �� �� ������ �������� alarm�� ������
				// ���ϻ���
				if (cnt == 4)
					remove(Filepath.c_str());
			} while (FindNextFile(hFind, &FindData));//handler�� ���� file �˻�
			cout << "endfile" << endl;
			send(client, "endfile", MAX_BUFFER_SIZE, 0);
		}
		FindClose(hFind);
		cnt++;
	} while (cnt <= 4);
	return 0;

	//find id file on server
	//read id file
}
