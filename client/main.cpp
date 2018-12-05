#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mutex>
#pragma comment(lib,"ws2_32.lib")
#define MAX_BUFFER_SIZE (4092)
using namespace std;
mutex mtx;
void Get(SOCKET server, char msg[])
{
	while (1)
	{
		mtx.lock();
		ZeroMemory(msg, MAX_BUFFER_SIZE);
		recv(server, msg, MAX_BUFFER_SIZE, 0);
		cout << msg << endl;
		mtx.unlock();
	}
}
void Send(SOCKET server)
{
	char buffer[MAX_BUFFER_SIZE];
	cin.getline(buffer,sizeof(buffer));
	send(server, buffer, MAX_BUFFER_SIZE, 0);
}
int main()
{
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

	thread Getm(&Get, consock, buf);
	
	while (1)
	{
		Send(consock);
	}

	Getm.join();

	WSACleanup();
	return 0;

}