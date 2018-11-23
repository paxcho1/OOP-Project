#include <algorithm>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <WinSock2.h>
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
	void VectorToTxt(const char* fileName, vector<string> &theId);
	void TxtToVector(const char* fileName, vector<string> &theId);
	void MapToTxt(const char* fileName, map<string, string> &user_Info);
	void Send(SOCKET client, string msg);

};