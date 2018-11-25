#include "MakeChat.h"

MakeChat::MakeChat(SOCKET client, string Id) : tool(client) 
{
}
MakeChat::~MakeChat() 
{
}
int MakeChat::Make(SOCKET client, string Id) {
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	char buf[MAX_BUFFER_SIZE];//���� �̸� ���� ���۹���
	string filename = MessangerRecv(client, Id, buf);
	if (strcmp(filename.c_str(), "MessangerClose") ==0 || strcmp(filename.c_str(), "SocketError") ==0)
	{
		cout << "client:" + Id + " out" << endl;
		return 0;
	}
	string Filename = filename;
	ZeroMemory(buf, MAX_BUFFER_SIZE);
	// �� �������� id ���۹���
	string recv_id = MessangerRecv(client,Id,buf);
	if (strcmp(recv_id.c_str(), "MessangerClose") ==0 || strcmp(recv_id.c_str(), "SocketError") == 0)
	{
		cout << "client:" + Id + " out" << endl;
		return 0;
	}
	string filepath = "c:/server/" + Id + "/" + filename + ".txt";
	ofstream Dwrite(filepath, ios::app);
	if (Dwrite.is_open()) {
		cout << "making a chat file on id:" + Id << endl;
		Dwrite << "'" + Id + "'���� '" + filename + "' �ʴ��߽��ϴ�." << endl;
	}
	Dwrite.close();
	while (strcmp(recv_id.c_str(), "EndId") !=0) {
		int length = recv_id.length();
		recv_id = recv_id.substr(3,length);//id:(��¥id) �� ����
		filepath = "c:/server/" + recv_id +"/chat" + recv_id +"alarm/" + filename + ".txt";//���� �޼��� �˶������� ������
		ofstream Write(filepath, ios::app);
		if (Write.is_open()) {
			cout << "making a chat file on id:" + recv_id << endl;
			Write << "'" + Id + "'���� '" + filename + "' �ʴ��߽��ϴ�." <<endl;
		}
		Write.close();
		tool::TxtToSocket("c:/server/Id_socket_map.txt", socket_info);
		iter = socket_info.find(recv_id);
		if (iter == socket_info.end()) {}
		else {
			SOCKET destsock = iter->second;
			cout << "��ǥ ������ ��������" << endl;
			Send(destsock, "Alarm");
			Alarm alarm(destsock, recv_id);
			alarm.Chatin(destsock, recv_id);
		}//if (ptrfind = 1) {//���� �ش� user�� ������
		Write.close();
		socket_info.clear();
		ZeroMemory(buf, MAX_BUFFER_SIZE);
		recv_id = MessangerRecv(client, Id, buf);
		if (strcmp(recv_id.c_str(), "MessangerClose") == 0 || strcmp(recv_id.c_str(), "SocketError") == 0)
		{
			cout << "client:" + Id + " out" << endl;
			return 0;
		}
	}//Alarm�� ä��â ���θ� Ȯ���غ��� �˶�
	Send(client, "Chat");
	return 1;
}