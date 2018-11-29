#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <direct.h>
#include <mutex>
#include "Receiver.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
mutex mtx;
void get(SOCKET server, string Id, char msg[])
{
	Receiver down(server, Id);
	while (1)
	{
		
		mtx.lock();
		ZeroMemory(msg, MAX_BUFFER_SIZE);
		down.Get(server,Id, msg);
		if (strcmp(msg, "error") == 0) {
			exit(0);
		}
		cout << msg << endl;
		mtx.unlock();
	}
}
void Send(SOCKET server)
{
	char buffer[4096];
	cin.getline(buffer, MAX_BUFFER_SIZE);
	if (strcmp(buffer, "AcceptInvite") ==0) {
		send(server, buffer, MAX_BUFFER_SIZE, 0);
		cin.getline(buffer, MAX_BUFFER_SIZE);
		// �ڽ��� ������ �ִ� invite file/buffer.txt ����
		send(server, buffer, MAX_BUFFER_SIZE, 0);
	}
	else if (strcmp(buffer, "SendInvite")==0) {
		send(server, buffer, MAX_BUFFER_SIZE, 0);
		//�ڽ��� ģ����Ͽ� �ش��ϴ°� Ȯ��
		cin.getline(buffer, MAX_BUFFER_SIZE);
		send(server, buffer, MAX_BUFFER_SIZE,0);
	}

	send(server, buffer, MAX_BUFFER_SIZE,0);
}
int main()
{
	string Id;
	// ���� �ʱ�ȭ
	string ip = "127.0.0.1";
	int port = 4296;
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsInit = WSAStartup(ver, &data);
	if (wsInit != 0) {
		cout << "���� �ʱ�ȭ ����" << endl;
	}
	else
	{
		cout << "���� �ʱ�ȭ ����" << endl;
	}
	
	SOCKET consock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in insock;
	insock.sin_family = AF_INET;
	insock.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &insock.sin_addr);
	int result = connect(consock, (sockaddr*)&insock, sizeof(insock));
	char buf[4096];
	cout << "id�� �Է��ϼ���" << endl;
	cin >> Id;

	string filepath = "c:/client";//�α����ϸ� ���ϻ���
	_mkdir(filepath.c_str());
	filepath = "c:/client/" + Id;//�α����ϸ� ���ϻ���
	_mkdir(filepath.c_str());
	filepath = "c:/client/" + Id + "/ChatAlarm";//�α����ϸ� ���ϻ���
	_mkdir(filepath.c_str());
	filepath = "c:/client/" + Id + "/FriendsIndex";//�α����ϸ� ���ϻ���
	_mkdir(filepath.c_str());
	filepath = "c:/client/" + Id + "/InviteAlarm";//�α����ϸ� ���ϻ���
	_mkdir(filepath.c_str());
	if (result == SOCKET_ERROR)
	{
		cout << "connect ����" << endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "connect ����" << endl;
	}

	thread Getm(&get, consock,Id, buf);

	while (1)
	{
		Send(consock);
	}

	Getm.join();
	WSACleanup();
	return 0;

}