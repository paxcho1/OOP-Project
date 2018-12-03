#include "Receiver.h"



Receiver::Receiver(SOCKET client, string Id)
{
}


Receiver::~Receiver()
{
}

int Receiver::Messanger(SOCKET server, string Id) {
	int cnt = 0;
	do {
		char msg[MAX_BUFFER_SIZE];
		ZeroMemory(msg, MAX_BUFFER_SIZE);
		Recv(server, msg);
		string filepath = msg;//get filename.txt
		//���� asd,qwe
		while (strcmp(msg, "endfile") != 0) {
			cout << filepath << endl;//fd.name ���
			if(cnt ==0)
			filepath = "c:/client/" + Id + "/" + filepath;
			else if(cnt ==1)
			filepath = "c:/client/" + Id + "/ChatAlarm/" + filepath;
			else if(cnt ==2)
			filepath = "c:/client/" + Id + "/InviteAlarm/" + filepath;
			else if(cnt ==3)
			filepath = "c:/client/" + Id + "/FriendsIndex/" + filepath;
			else if (cnt == 4)
			filepath = "c:/client/" + Id + "/FriendsIndex/" + filepath;// ��ģ���� ǥ������
			Recv(server, msg);//total byte size
			int totalbytes = atoi(msg);
			FILE *fp = fopen(filepath.c_str(), "wb");
			int left = totalbytes;
			while (1) {
				if (left <= MAX_BUFFER_SIZE) {//����ũ�Ⱑ MAX_BUFFER_SIZE ���� ������
					Recv(server, msg);
					fwrite(msg, 1, left, fp);
					left = 0;
				}
				else if (left > MAX_BUFFER_SIZE) {
					Recv(server, msg);
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
			filepath = Recv(server, msg);//get filename.txt
		}
		if (strcmp(msg, "endfile") == 0) {
			cout << "ä�� ��� �ҷ����� �Ϸ�" << endl;
		}
		cnt++;
	} while (cnt <= 4);
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
	if (strcmp(code.c_str(), "000")==0) {
		Messanger(server, Id);
		return "receive complete";
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
		//�� ģ���� ��ģ���Դϴ�.
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
int Receiver::Recv(SOCKET client, char* buf) {

	ZeroMemory(buf, MAX_BUFFER_SIZE);
	int Bytein = recv(client, buf, MAX_BUFFER_SIZE, 0);//error handle
	if (Bytein <= 0) {
		return -1;
	}
	else {
		return 1;
	}
}