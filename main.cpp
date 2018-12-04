#include <winsock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <sstream>
#include <thread>  
#include <direct.h>
#include <WS2tcpip.h>
#include "Signin.h"
#include "Alarm.h"
#include "Login.h"
#include "Messanger.h"
#include "Tool.h"
//#include "TimeTable.h"
using namespace std;

fd_set Fd;
#pragma comment(lib,"ws2_32.lib")
void Sign(SOCKET client) {
	Signin sign(client);
	sign.in(client);
}
void Log(SOCKET client) {
	Login login(client);
	login.logging(client);
}
void Message(SOCKET client, string id) {
	Alarm alarm(client, id);
	alarm.Messanger(client, id);
	Messanger messanger(client, id);
	messanger.in(client, id);
}
int Table(SOCKET client, string id) {
	//DailySchedule DailySchedule;

	while (1) {

		char buf[MAX_BUFFER_SIZE];
		ZeroMemory(buf, MAX_BUFFER_SIZE);
		int byteIn = recv(client, buf, MAX_BUFFER_SIZE, 0);
		string code = buf;
		code = code.substr(0, 3);

		if (byteIn <= 0) {
			return 0;
		}
		else {
			if (strcmp(code.c_str(), "000") == 0) {
				//����

			}
			else if (strcmp(code.c_str(), "001") == 0) {
				//MessangerIn
				Alarm alarm(client, id);
				alarm.Messanger(client, id);
				Messanger messanger(client, id);
				messanger.in(client, id);
			}
			else if (strcmp(code.c_str(), "002") == 0) {

			}
			else if (strcmp(code.c_str(), "003") == 0) {

			}



		}
	}
}
int main() {
	while (1) {
		WSADATA data;
		WORD ver = MAKEWORD(2, 2);
		map<string, SOCKET>socket_info;
		ofstream wFile("c:/server/Id_Socket_map.txt");
		for (map<string, SOCKET>::const_iterator iterator = socket_info.begin(); iterator != socket_info.end(); ++iterator) {
			wFile << iterator->first << "|" << iterator->second;
			wFile << "\n";
		}
		wFile.close();
		int wsInit = WSAStartup(ver, &data);
		if (wsInit != 0) {
			cout << "���� �ʱ�ȭ ����" << endl;
		}
		cout << "���� �ʱ�ȭ ����" << endl;
		_mkdir("c:/server");
		SOCKET listensocket = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in insocket;
		insocket.sin_family = AF_INET;
		int port = 4296;
		insocket.sin_port = htons(port);
		string ip = "127.0.0.1";
		inet_pton(AF_INET, ip.c_str(), &insocket.sin_addr);
		::bind(listensocket, (sockaddr*)&insocket, sizeof(insocket));
		listen(listensocket, SOMAXCONN);
		FD_ZERO(&Fd);
		FD_SET(listensocket, &Fd);
		cout << "listensock�� master�� �߰�" << endl;
		while (1) {
			fd_set copy = Fd;

			int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
			cout << "select ����" << socketCount << "�� �̺�Ʈ �߻�" << endl;
			for (int i = 0; i < socketCount; i++) {
				SOCKET sock = copy.fd_array[i];
				if (sock == listensocket)
				{
					SOCKET client = accept(listensocket, nullptr, nullptr);
					cout << "���� accept" << endl;
					FD_SET(client, &Fd);
				}
				else {
					char buf[MAX_BUFFER_SIZE];
					ZeroMemory(buf, MAX_BUFFER_SIZE);
					int byteIn = recv(sock, buf, MAX_BUFFER_SIZE, 0);
					if (byteIn <= 0) {
						closesocket(sock);
						FD_CLR(sock, &Fd);
					}
					else {
						if (strcmp(buf, "Signin") == 0) {//client�� login ��û
						   //thread Signin
							thread SIGN(&Sign, sock);
							SIGN.detach();
						}
						else if (strcmp(buf, "Login") == 0) {
							thread LOGIN(&Log, sock);
							LOGIN.detach();
						}
						else if (strcmp(buf, "Messanger") == 0) {
							cout << "Messanger in" << endl;
							char buf[MAX_BUFFER_SIZE];
							ZeroMemory(buf, MAX_BUFFER_SIZE);
							int byteIn = recv(sock, buf, MAX_BUFFER_SIZE, 0);
							if (byteIn <= 0) {
								closesocket(sock);
								FD_CLR(sock, &Fd);
							}
							else {
								thread Messange(&Message, sock, buf);
								Messange.detach();
							}
						}
						else if (strcmp(buf, "TimeTable") == 0) {
							thread TimeTable(&Table, sock, buf);
							TimeTable.detach();
						}
						//�޼��� ����
						//event ����
						//recv ���� client�� ���¸� �Է¹ް�
						//switch(msg)

						//thread ���� detach
						{
							//case ����
							{
								//login();

								//sendmsg();

								//plusfri();

								//makemultichat();

								//msgread(currid,file);
							}
						}

					}
				}
			}
		}
	}
}