#include <winsock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <sstream>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

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
		fd_set Fs;
		FD_ZERO(&Fs);
		FD_SET(listensocket, &Fs);
		cout << "listensock을 master에 추가" << endl;
		while (1) {
			fd_set copy = Fs;

			int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
			cout << "select 실행" << socketCount << "에 이벤트 발생" << endl;
			for (int i = 0; i < socketCount; i++) {
				SOCKET sock = copy.fd_array[i];
				if (sock == listensocket)
				{
					SOCKET client = accept(listensocket, nullptr, nullptr);
					cout << "소켓 accept" << endl;
					FD_SET(client, &Fs);
				}
				else {
					char buf[4096];
					ZeroMemory(buf, 4096);
					int byteIn = recv(sock, buf, 4096, 0);
					if (byteIn <= 0) {
						closesocket(sock);
						FD_CLR(sock, &Fs);
					}
					else {
						for (int i = 0; i < Fs.fd_count; i++) {
							SOCKET outSock = Fs.fd_array[i];
							if (outSock != listensocket && outSock != sock) {
								cout << sock << "에 메세지 송신" << endl;
								ostringstream ss;
								ss << "SOCKET #" << sock << " : " << buf << "\r\n";
								string strOut = ss.str();
								send(outSock, strOut.c_str(), strOut.size() + 1, 0);

							}
						}
					}
				}
			}
		}
	}
}