#include "AddFriends.h"
AddFriends::AddFriends(SOCKET client,string Id,string recv_id):tool(client)
{
}
AddFriends::~AddFriends()
{
}
int AddFriends::Send_invite(SOCKET client, string Id , string recv_id) {//id 는 초대자 recv id 는 초대 수신인
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	SOCKET destsock;
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	string filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "invite/" + Id + ".txt";//초대장은 friendsrecv_idinvite에 저장
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
		cout << "목표 소켓" + destsock << endl;
		Send(destsock, "Alarm");
	}
	return 0;
}
int AddFriends::Accept_invite(SOCKET client, string Id, string recv_id) {//id는 초대 수신인recv id 는 초대자
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	SOCKET destsock;
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	string filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "/" + Id + ".txt";//초대를 받으면 바로 친구 목록으로 보냄
	ofstream DWrite(filepath, ios::app);
	if (DWrite.is_open()) {
		cout << "friends write on" + recv_id << endl;
		DWrite << " " << endl;
	}
	filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "alarm/" + Id + ".txt";//초대를 받으면 받았다는 알림을 server에 저장함^^
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
		cout << "목표 소켓" + destsock << endl;
		Send(destsock, "NewFriend");
	}
	return 0;
}