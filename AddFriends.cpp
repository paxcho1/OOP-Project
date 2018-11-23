#include "AddFriends.h"
AddFriends::AddFriends(SOCKET client,string Id,string recv_id):tool(client)
{
}
AddFriends::~AddFriends()
{
}
int AddFriends::Send_invite(SOCKET client, string Id , string recv_id) {//id �� �ʴ��� recv id �� �ʴ� ������
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	SOCKET destsock;
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	string filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "invite/" + Id + ".txt";//�ʴ����� friendsrecv_idinvite�� ����
	ofstream Write(filepath, ios::app);
	if (Write.is_open()) {
		cout << "writing file" << endl;
		Write << Id << endl;
	}
	Write.close();
	iter = socket_info.find(recv_id);
	if (iter == socket_info.end()) {}
	else {
		destsock = iter->second;
		cout << "��ǥ ����" + destsock << endl;
		Send(destsock, "Alarm");
	}
	return 0;
}
int AddFriends::Accept_invite(SOCKET client, string Id, string recv_id) {//id�� �ʴ� ������recv id �� �ʴ���
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	SOCKET destsock;
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	string filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "/" + Id + ".txt";//�ʴ븦 ������ �ٷ� ģ�� ������� ����
	ofstream DWrite(filepath, ios::app);
	if (DWrite.is_open()) {
		cout << "friends write on" + recv_id << endl;
		DWrite << " " << endl;
	}
	filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "alarm/" + Id + ".txt";//�ʴ븦 ������ �޾Ҵٴ� �˸��� server�� ������^^
	ofstream AWrite(filepath, ios::app);
	if (AWrite.is_open()) {
		cout << "friends write on" + recv_id << endl;
		AWrite << " " << endl;
	}
	AWrite.close();
	filepath = "c:/server/" + Id + "/" + "friends" + Id + "/" + recv_id + ".txt";
	ofstream IWrite(filepath, ios::app);
	if (IWrite.is_open()) {
		cout << "friends write on : " + Id << endl;
		IWrite << " " << endl;
	}
	IWrite.close();

	iter = socket_info.find(recv_id);
	if (iter == socket_info.end()) {}
	else {
		destsock = iter->second;
		cout << "��ǥ ����" + destsock << endl;
		Send(destsock, "NewFriend");
	}
	return 0;
}