#pragma once
#include <WinSock2.h>
#include <string>
#include "Tool.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#define MAX_BUFFER_SIZE 40910
using namespace std;
class Signin: public tool
{
public:
	Signin(SOCKET client);
	~Signin();
	int in(SOCKET client);
};

