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
	if (iter == socket_info.end()) {}//��밡 �������϶� �˶��� ����
	else {
		destsock = iter->second;
		cout << "��ǥ ����" + destsock << endl;
		Send(destsock, "NewInvite");//�� ģ���ʴ밡 �ִٴ� �˶�
		Alarm aram(destsock,recv_id);//���� ����
		aram.FriendsIndex(destsock, recv_id);
	}
	return 0;
}
int AddFriends::Accept_invite(SOCKET client, string Id, string recv_id) {//id�� �ʴ� ������recv id �� �ʴ���
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	SOCKET destsock;
	string filepath = "c:/server/" + Id + "/friends" + Id + "invite/" + recv_id + ".txt";
	remove(filepath.c_str());
	filepath = "c:/server/" + recv_id + "/friends" + recv_id + "/" + Id + ".txt";//�ʴ븦 ������ �ٷ� ģ�� ������� ����
	ofstream DWrite(filepath, ios::app);
	if (DWrite.is_open()) {
		cout << "friends write on" + recv_id << endl;
		DWrite << " " << endl;
	}
	filepath = "c:/server/" + Id + "/" + "friends" + Id + "/" + recv_id + ".txt";//�ʴ븦 ������ �ٷ� ģ��������� ����
	ofstream IWrite(filepath, ios::app);
	if (IWrite.is_open()) {
		cout << "friends write on : " + Id << endl;
		IWrite << " " << endl;
	}
	IWrite.close();

	filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "alarm/" + Id + ".txt";//�ʴ븦 ������ �޾Ҵٴ� �˸��� server�� ������^^
	ofstream AWrite(filepath, ios::app);
	if (AWrite.is_open()) {
		cout << "friends write on" + recv_id << endl;
		AWrite << " " << endl;
	}
	AWrite.close();
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	iter = socket_info.find(recv_id);
	if (iter == socket_info.end()) {}
	else {

		destsock = iter->second;
		cout << "��ǥ ����" + destsock << endl;
		Send(destsock, "NewFriend");//���� ��밡 �������̶�� �ٷ� ģ���� �߰�����//ģ�� ���Ϸ� �ٷ� ����
		Alarm aram(destsock, recv_id);// ���� ����
		aram.NewFriends(destsock, recv_id);
	}
	socket_info.clear();
	Send(client, "NewFriend");
	Alarm clialarm(client, Id);
	clialarm.NewFriends(client, Id);//client�� ģ���� �߰���
	return 0;
}