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
int Receiver::NewFriend(SOCKET server, string Id) {
	char msg[MAX_BUFFER_SIZE];
	ZeroMemory(msg, MAX_BUFFER_SIZE);
	string filepath = Get(server,Id, msg);//get filename.txt
	while (strcmp(msg, "endfile") != 0) {
		cout << filepath << endl;//fd.name ���
		filepath = "c:/client/" + Id + "/FriendsAlarm/" + filepath;
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
string Receiver::Get(SOCKET server, string Id, char buf[]) {
	int Bytein = recv(server, buf, MAX_BUFFER_SIZE, 0);
	if (strcmp(buf, "Chat") == 0) {
		Chat(server, Id);
		Get(server, Id, buf);
	}
	else if (strcmp(buf, "Alarm") == 0) {
		Chatin(server, Id);
		Get(server, Id, buf);
	}
	else if (strcmp(buf, "Friends") == 0) {
		FriendsIndex(server, Id);
		Get(server, Id, buf);
	}
	else if (strcmp(buf, "NewInvite")==0) {
		NewInvite(server, Id);
		Get(server, Id, buf);
	}
	else if (strcmp(buf, "NewFriend") == 0) {
		NewFriend(server, Id);
		Get(server, Id, buf);
	}
	else if (Bytein <= 0) {
		exit(0);
		return "error";
	}
	else {
		return buf;
	}
}