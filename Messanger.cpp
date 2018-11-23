#include "Messanger.h"
Messanger::Messanger(SOCKET client,string Id):tool(client)
{
}
Messanger::~Messanger()
{
}
int Messanger::in(SOCKET client,string Id) {
	char path[255];
	char file[MAX_BUFFER_SIZE];
	char msg[MAX_BUFFER_SIZE];
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	cout << "�޽��� ���� id:" + Id << endl;
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	socket_info.insert(pair<string, SOCKET>(Id, client));
	tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
	socket_info.clear();
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	while (1) {
		int Bytein = Recv(client, msg);//�޼��� �Է¹��� ���⼭ �޽����� ���ᵵ �Է¹޴´�.
		if (strcmp(msg, "MessangerClose") == 0) {// �޽��� ����
			iter = socket_info.find(Id);
			socket_info.erase(iter);
			tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
			return 0;
		}
		else if (strcmp(msg, "Alarm") == 0) {
			Send(client, "Alarm");
			Alarm alam(client, Id);
			alam.in(client, Id);
			//�˶��� �ƴ϶� msg�� ���������� ��� �ݺ�
		}
		else if (strcmp(msg, "SendInvite") == 0) {
			cout << "Sending invite message" << endl;
			char recv_id[MAX_BUFFER_SIZE];
			Recv(client, recv_id);
			AddFriends Add(client, Id , recv_id);
			Add.Send_invite(client, Id, recv_id);
		}
		else if (strcmp(msg, "AcceptInvite") == 0) {
			cout << "Accepting invite message" << endl;
			char recv_id[MAX_BUFFER_SIZE];
			Recv(client, recv_id);
			AddFriends Add(client, Id, recv_id);
			Add.Accept_invite(client, Id, recv_id);
		}
		else if (Bytein <= 0) {
			iter = socket_info.find(Id);
			socket_info.erase(iter);
			tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
			return -1;
		}
		else {//�޼����� �Է¹޾Ҵ� //filename msg ���·� ����
			
			char* ptr = strtok(msg, " ");
			string file = (strcpy,ptr);//file = filename
			ptr = strtok(NULL, " ");
			char Str[MAX_BUFFER_SIZE];
			string tokmsg;
			strcpy(Str, "");
			while (ptr != NULL) {
				strcat(Str, ptr);
				tokmsg = strcat(Str," ");
				ptr = strtok(NULL, " ");
			}
			string message = tokmsg;
			string pathstr = "c:/server/" + Id + "/" + file + ".txt";// message sender�� chatfile���� ä�ù� �������� ����� �޾ƿ�
			strcpy(path, pathstr.c_str());
			ofstream Write(path, ios::app);
			if (Write.is_open()) {
				cout << "writing file" << endl;
				Write << Id + ": " + message << endl;//�ڽ��� id folder�� message ����
			}
			Write.close(); 
			char filename[MAX_BUFFER_SIZE];
			strcpy(filename, file.c_str());
			ptr = strtok(filename, ",");//index ���� ���� ����
			SOCKET destsock;
			while (ptr != NULL) {//ptr�� ä�ù濡 �ִ� �ٸ� user_id�̴�.
				if (ptr != Id) {
					string str = ptr;// another_user_id
					string index_path = "c:/server/Socket_Id_Map.txt";
					pathstr = "c:/server/" + str + "/chat" + str + "alarm/" + file + ".txt";//filename�� ���� user/alarm/filename�� ���
					strcpy(path, pathstr.c_str());
					ofstream DWrite(path, ios::app);
					if (DWrite.is_open()) {
						cout << "writing file" << endl;
						DWrite << Id + ": " + message << endl;//������ id/alarm/file�� message ����
					}//������ �������� ����.
					else if (DWrite.is_open() == false) {
						return -1;
					}
					DWrite.close();
					iter = socket_info.find(ptr);
					if (iter != socket_info.end()) {}
					else {
						destsock = iter->second;
						cout << "��ǥ ����" + destsock << endl;
						Send(destsock, "Alarm");
					}//if (ptrfind = 1) {//���� �ش� user�� ������
					//	//send alarm message
					//}+
				}
				ptr = strtok(NULL, ",");
			}
		}
	}
}