#include <winsock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <sstream>
#include <thread>
#include "Signin.h"

using namespace std;

#pragma comment(lib,"ws2_32.lib")
void Sign(SOCKET client) {
	Signin sign(client);
	sign.in(client);
}
/*void Login(SOCKET client) {
	Login login(client);

}
*/
int main() {
	while (1) {
		WSADATA data;
		WORD ver = MAKEWORD(2, 2);

		int wsInit = WSAStartup(ver, &data);
		if (wsInit != 0) {
			cout << "���� �ʱ�ȭ ����" << endl;
		}
		cout << "���� �ʱ�ȭ ����" << endl;

		SOCKET listensocket = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in insocket;
		insocket.sin_family = AF_INET;
		int port = 4296;
		insocket.sin_port = htons(port);
		string ip = "127.0.0.1";
		inet_pton(AF_INET, ip.c_str(), &insocket.sin_addr);
		::bind(listensocket, (sockaddr*)&insocket, sizeof(insocket));
		listen(listensocket, SOMAXCONN);
		fd_set Fd;
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
					char buf[4096];
					ZeroMemory(buf, 4096);
					int byteIn = recv(sock, buf, 4096, 0);
					if (byteIn <= 0) {
						closesocket(sock);
						FD_CLR(sock, &Fd);
					}
					else {
						if (strcmp(buf,"Signin")!=1) {//client�� login ��û
							//thread Signin
							thread SIGN(&Sign, sock);
							SIGN.detach();
						}
						else if (buf == "Login") {
							//thread Login
							//thread Login();
						
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
