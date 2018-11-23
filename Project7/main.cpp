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
			cout << "윈속 초기화 실패" << endl;
		}
		cout << "윈속 초기화 성공" << endl;

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
		cout << "listensock을 master에 추가" << endl;
		while (1) {
			fd_set copy = Fd;

			int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
			cout << "select 실행" << socketCount << "에 이벤트 발생" << endl;
			for (int i = 0; i < socketCount; i++) {
				SOCKET sock = copy.fd_array[i];
				if (sock == listensocket)
				{
					SOCKET client = accept(listensocket, nullptr, nullptr);
					cout << "소켓 accept" << endl;
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
						if (strcmp(buf,"Signin")!=1) {//client의 login 요청
							//thread Signin
							thread SIGN(&Sign, sock);
							SIGN.detach();
						}
						else if (buf == "Login") {
							//thread Login
							//thread Login();
						
						}
						//메세지 수신
						//event 수신
						//recv 현재 client의 상태를 입력받고
						//switch(msg)

						//thread 구분 detach
						{
								//case 구분
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
