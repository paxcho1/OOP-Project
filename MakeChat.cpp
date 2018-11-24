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
	tool::TxtToSocket("c:/server/Id_socket_map.txt", socket_info);
	char buf[MAX_BUFFER_SIZE];//���� �̸� ���� ���۹���
	string filename = MessangerRecv(client, Id, buf);
	if (strcmp(filename.c_str(), "MessangerClose") == 0 || strcmp(filename.c_str(), "SocketError"))
	{
		cout << "client:" + Id + " out" << endl;
		return 0;
	}
	string Filename = filename;
	ZeroMemory(buf, MAX_BUFFER_SIZE);
	// �� �������� id ���۹���
	string recv_id = MessangerRecv(client,Id,buf);
	if (strcmp(recv_id.c_str(), "MessangerClose") == 0 || strcmp(recv_id.c_str(), "SocketError"))
	{
		cout << "client:" + Id + " out" << endl;
		return 0;
	}
	while (strcmp(recv_id.c_str(), "EndId") ==0) {
		int length = recv_id.length();
		recv_id = recv_id.substr(3,length);//id:(��¥id) �� ����
		string filepath = "c:/server/" + recv_id +"/" + filename + ".txt";
		ofstream Write(filepath, ios::app);
		if (Write.is_open()) {
			cout << "making a chat file on id:" + recv_id << endl;
			Write << "'" + Id + "'���� '" + filename + "' �ʴ��߽��ϴ�.";
		}
		iter = socket_info.find(recv_id);
		if (iter != socket_info.end()) {}
		else {
			SOCKET destsock = iter->second;
			cout << "��ǥ ����" + destsock << endl;
			Send(destsock, "Alarm");
		}//if (ptrfind = 1) {//���� �ش� user�� ������
		Write.close();
		ZeroMemory(buf, MAX_BUFFER_SIZE);
		recv_id = MessangerRecv(client, Id, buf);
		if (strcmp(recv_id.c_str(), "MessangerClose") == 0 || strcmp(recv_id.c_str(), "SocketError"))
		{
			cout << "client:" + Id + " out" << endl;
			return 0;
		}
	
	}
	Send(client, "Alarm");//Alarm�� ä��â ���θ� Ȯ���غ��� �˶�

	return 1;
}