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
#define MAX_BUFFER_SIZE (4092)
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
	cin.getline(buffer, sizeof(buffer));
	send(server, buffer, 4092, 0);
}
int main()
{
	string Id;
	// 윈속 초기화
	string ip = "127.0.0.1";
	int port = 4296;
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsInit = WSAStartup(ver, &data);
	if (wsInit != 0) {
		cout << "윈속 초기화 실패" << endl;
	}
	else
	{
		cout << "윈속 초기화 성공" << endl;
	}
	
	SOCKET consock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in insock;
	insock.sin_family = AF_INET;
	insock.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &insock.sin_addr);
	int result = connect(consock, (sockaddr*)&insock, sizeof(insock));
	char buf[4096];
	cout << "id를 입력하세요" << endl;
	cin >> Id;

	string filepath = "c:/client";//로그인하면 파일생성
	_mkdir(filepath.c_str());
	filepath = "c:/client/" + Id;//로그인하면 파일생성
	_mkdir(filepath.c_str());
	filepath = "c:/client/" + Id + "/ChatAlarm";//로그인하면 파일생성
	_mkdir(filepath.c_str());
	filepath = "c:/client/" + Id + "/FriendsAlarm";//로그인하면 파일생성
	_mkdir(filepath.c_str());
	filepath = "c:/client/" + Id + "/FriendsIndex";//로그인하면 파일생성
	_mkdir(filepath.c_str());
	filepath = "c:/client/" + Id + "/InviteAlarm";//로그인하면 파일생성
	_mkdir(filepath.c_str());
	if (result == SOCKET_ERROR)
	{
		cout << "connect 실패" << endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "connect 성공" << endl;
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