#pragma once
#include <WinSock2.h>
#include <string>
#define MAX_BUFFER_SIZE 4092
using namespace std;
class tool// recv와 send를 사용하기 쉽게 만들어줌
{
public:
	SOCKET client;
	char buf[MAX_BUFFER_SIZE];
	tool(SOCKET client);
	~tool(); 
	int Recv(SOCKET client, char buf[]);
	void Send(SOCKET client, string msg);
};

