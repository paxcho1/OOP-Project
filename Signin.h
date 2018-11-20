#pragma once
#include <WinSock2.h>
#include <string>
#include "signin.h"
#define MAX_BUFFER_SIZE 40910
using namespace std;
class Signin
{
public:
	Signin(SOCKET client);
	~Signin();

	SOCKET client;

	void in(SOCKET client);
};

