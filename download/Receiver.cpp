#include "Receiver.h"



Receiver::Receiver(SOCKET client, string Id)
{
}


Receiver::~Receiver()
{
}

int Receiver::Chat(SOCKET server, string Id) {
	char msg[MAX_BUFFER_SIZE];
	ZeroMemory(msg, MAX_BUFFER_SIZE);
	string filepath = Get(server, Id, msg);//get filename.txt
	//����
	while (strcmp(msg, "endfile") != 0) {
		cout << filepath << endl;//fd.name ���
		filepath = "c:/client/" + Id + "/" + filepath;
		Get(server, Id, msg);//total byte size
		int totalbytes = atoi(msg);
		FILE *fp = fopen(filepath.c_str(), "wb");
		int left = totalbytes;
		while (1) {
			if (left <= MAX_BUFFER_SIZE) {//����ũ�Ⱑ MAX_BUFFER_SIZE ���� ������
				Get(server, Id, msg);
				fwrite(msg, 1, left, fp);
				left = 0;
			}
			else if (left > MAX_BUFFER_SIZE) {
				Get(server, Id, msg);
				fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
				left -= MAX_BUFFER_SIZE;
			}
			if (left == 0) {
				break;
			}
		}
		fclose(fp);
		if (left == 0) {
			printf("filename %s ������ ���������� �޾ҽ��ϴ�.\r\n", msg);
		}
		else {
			printf("������ ����� ���� ���߽��ϴ�.\r\n");
		}
		filepath = Get(server, Id, msg);//get filename.txt
	}
	if (strcmp(msg, "endfile") == 0) {
		cout << "ä�� ��� �ҷ����� �Ϸ�" << endl;
	}
	return 0;
}
int Receiver::Chatin(SOCKET server, string Id) {
	char msg[MAX_BUFFER_SIZE];
	ZeroMemory(msg, MAX_BUFFER_SIZE);
	string filepath = Get(server,Id, msg);//get filename.txt
	while (strcmp(msg, "endfile") != 0) {
		cout << filepath << endl;//fd.name ���
		filepath = "c:/client/" + Id + "/ChatAlarm/" + filepath;
		Get(server, Id , msg);//total byte size
		int totalbytes = atoi(msg);
		FILE *fp = fopen(filepath.c_str(), "wb");
		int left = totalbytes;
		while (1) {
			if (left <= MAX_BUFFER_SIZE) {//����ũ�Ⱑ MAX_BUFFER_SIZE ���� ������
				Get(server,Id, msg);
				fwrite(msg, 1, left, fp);
				left = 0;
			}
			else if (left > MAX_BUFFER_SIZE) {
				Get(server, Id,msg);
				fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
				left -= MAX_BUFFER_SIZE;
			}
			if (left == 0) {
				break;
			}
		}
		fclose(fp);
		if (left == 0) {
			printf("filename %s ������ ���������� �޾ҽ��ϴ�.\r\n", msg);
		}
		else {
			printf("������ ����� ���� ���߽��ϴ�.\r\n");
		}
		filepath = Get(server,Id, msg);//get filename.txt
	}
	if (strcmp(msg, "endfile") == 0) {
		cout << "ä�� �˶� ��� �ҷ����� �Ϸ�" << endl;
	}
	return 0;
}
int Receiver::NewInvite(SOCKET server, string Id) {
	char msg[MAX_BUFFER_SIZE];
	ZeroMemory(msg, MAX_BUFFER_SIZE);
	string filepath = Get(server,Id, msg);//get filename.txt
	while (strcmp(msg, "endfile") != 0) {
		cout << filepath << endl;//fd.name ���
		filepath = "c:/client/" + Id + "/InviteAlarm/" + filepath;
		Get(server, Id, msg);//total byte size
		int totalbytes = atoi(msg);
		FILE *fp = fopen(filepath.c_str(), "wb");
		int left = totalbytes;
		while (1) {
			if (left <= MAX_BUFFER_SIZE) {//����ũ�Ⱑ MAX_BUFFER_SIZE ���� ������
				Get(server, Id,msg);
				fwrite(msg, 1, left, fp);
				left = 0;
			}
			else if (left > MAX_BUFFER_SIZE) {
				Get(server,Id, msg);
				fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
				left -= MAX_BUFFER_SIZE;
			}
			if (left == 0) {
				break;
			}
		}
		fclose(fp);
		if (left == 0) {
			printf("filename %s ������ ���������� �޾ҽ��ϴ�.\r\n", msg);
		}
		else {
			printf("������ ����� ���� ���߽��ϴ�.");
		}
		filepath = Get(server,Id, msg);//get filename.txt
	}
	if (strcmp(msg, "endfile") == 0) {
		cout << "friend �˶� ��� �ҷ����� �Ϸ�" << endl;
	}
	return 0;
}
int Receiver::NewFriends(SOCKET server, string Id) {
	char msg[MAX_BUFFER_SIZE];
	ZeroMemory(msg, MAX_BUFFER_SIZE);
	string filepath = Get(server,Id, msg);//get filename.txt
	while (strcmp(msg, "endfile") != 0) {
		cout << filepath << endl;//fd.name ���
		filepath = "c:/client/" + Id + "/FriendsIndex/" + filepath;
		Get(server, Id, msg);//total byte size
		int totalbytes = atoi(msg);
		FILE *fp = fopen(filepath.c_str(), "wb");
		int left = totalbytes;
		while (1) {
			if (left <= MAX_BUFFER_SIZE) {//����ũ�Ⱑ MAX_BUFFER_SIZE ���� ������
				Get(server, Id,msg);
				fwrite(msg, 1, left, fp);
				left = 0;
			}
			else if (left > MAX_BUFFER_SIZE) {
				Get(server, Id,msg);
				fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
				left -= MAX_BUFFER_SIZE;
			}
			if (left == 0) {
				break;
			}
		}
		fclose(fp);
		if (left == 0) {
			printf("filename %s ������ ���������� �޾ҽ��ϴ�.\r\n", msg);
		}
		else {
			printf("������ ����� ���� ���߽��ϴ�.");
		}
		filepath = Get(server,Id, msg);//get filename.txt
	}
	if (strcmp(msg, "endfile") == 0) {
		cout << "���ο� friend ��� �ҷ����� �Ϸ�" << endl;
	}
	return 0;
}
int Receiver::FriendsIndex(SOCKET server, string Id) {
	char msg[MAX_BUFFER_SIZE];
	ZeroMemory(msg, MAX_BUFFER_SIZE);
	string filepath = Get(server,Id, msg);//get filename.txt
	while (strcmp(msg, "endfile") != 0) {
		cout << filepath << endl;//fd.name ���
		filepath = "c:/client/" + Id + "/FriendsIndex/" + filepath;
		Get(server, Id, msg);//total byte size
		int totalbytes = atoi(msg);
		FILE *fp = fopen(filepath.c_str(), "wb");
		int left = totalbytes;
		while (1) {
			if (left <= MAX_BUFFER_SIZE) {//����ũ�Ⱑ MAX_BUFFER_SIZE ���� ������
				Get(server,Id, msg);
				fwrite(msg, 1, left, fp);
				left = 0;
			}
			else if (left > MAX_BUFFER_SIZE) {
				Get(server,Id, msg);
				fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
				left -= MAX_BUFFER_SIZE;
			}
			if (left == 0) {
				break;
			}
		}
		fclose(fp);
		if (left == 0) {
			printf("filename %s ������ ���������� �޾ҽ��ϴ�.\r\n", msg);
		}
		else {
			printf("������ ����� ���� ���߽��ϴ�.");
		}
		filepath = Get(server,Id, msg);//get filename.txt
	}
	if (strcmp(msg, "endfile") == 0) {
		cout << "friend ��� �ҷ����� �Ϸ�" << endl;
	}
	return 0;
}
int Receiver::Newmsg(SOCKET server, string Id, string file, string message) {
	string filepath = "c:/client/" + Id + "/ChatAlarm/" + file + ".txt";
	ofstream Write(filepath, ios::app);
	if (Write.is_open()) {
		cout << "writing file" << endl;
		Write << message << endl;
	}
	Write.close();
	return 0;
}
string Receiver::Get(SOCKET server, string Id, char* buf) {
	int Bytein = recv(server, buf, MAX_BUFFER_SIZE, 0);
	string code = buf;
	code = code.substr(0, 3);
	if (strcmp(code.c_str(), "001") == 0) {
		Chat(server, Id); return buf;
	}
	else if (strcmp(code.c_str(), "002") == 0) {
		Chatin(server, Id); return buf;
	}
	else if (strcmp(code.c_str(), "003") == 0) {
		FriendsIndex(server, Id); return buf;
	}
	else if (strcmp(code.c_str(), "004")==0) {
		NewInvite(server, Id); return buf;
	}
	else if (strcmp(code.c_str(), "005") == 0) {
		NewFriends(server, Id); return buf;
	}
	else if (strcmp(code.c_str(), "006") == 0) {//message ���� //���� ���� client�� �ش� ä��â�� ������
		strtok(buf, " ");
		char* ptr = strtok(NULL, " ");
		string file = (strcpy, ptr);
		ptr = strtok(NULL, " ");
		string sender = (strcpy, ptr);
		char Str[MAX_BUFFER_SIZE];
		string tokmsg;
		strcpy(Str, "");
		while (ptr != NULL) {
			strcat(Str,ptr);
			tokmsg = strcat(Str, " ");
			ptr = strtok(NULL, " ");
		}
		Newmsg(server, Id, file, tokmsg); return buf;
	}
	else if (strcmp(code.c_str(), "007") == 0) {//Invite ����
		strtok(buf, " ");
		char* Invite_id = strtok(NULL, " ");
		string filepath = "c:/client/" + Id + "/InviteAlarm/" + Invite_id + ".txt";
		ofstream Write(filepath, ios::app);
		if (Write.is_open()) {
			cout << "writingfile:" + filepath << endl;
			Write << Invite_id <<endl;
		}
		Write.close();
	}
	else if (strcmp(code.c_str(), "008") == 0) {//��ģ���� �˶�
		strtok(buf, " ");
		char* new_friend = strtok(NULL, " ");
		string filepath = "c:/client/" + Id + "/FriendsIndex/" + new_friend + ".txt";//friends Alarm���� ��������.
		ofstream Write(filepath, ios::app);
		if (Write.is_open()) {
			cout << "writingfile:" + filepath << endl;
			Write << new_friend << endl;
		}
		Write.close();
	}
	else if (Bytein <= 0) {
		exit(0);
		return "error";
	}
	else {
		return buf;
	}
}