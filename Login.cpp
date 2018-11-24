#include "Login.h"



Login::Login(SOCKET client) :tool(client)
{
}


Login::~Login()
{
}
int Login::logging(SOCKET client) {
	char Id[MAX_BUFFER_SIZE];
	char Password[MAX_BUFFER_SIZE];
	int Id_Bytein;
	int Password_Bytein;
	map<string, string> user_Info;
	map<string, string>::iterator iter;
	map<string, SOCKET> IdSocketInfo;
	string str;
	tool::TxtToMap("c://Id_Ps_map.txt", user_Info);
	do {
		Id_Bytein = tool::Recv(client, Id); //아이디 받기
		Password_Bytein = tool::Recv(client, password);//비번 받기

		
		int CheckId = 0;
		int CheckPassword = 0;

		for (iter = user_Info.begin(); iter == user_Info.end(); (++iter)) {
			if (iter->first == Id) {
				CheckId = 1;//Id가 등록되어 있음
				if (iter->second == password) {
						CheckPassword = 1;
						send(client, str = "Successfully Login", str.size(), 0);
				}
				else {
					send(client, str = "Ether your id or password is wrong", str.size(), 0);
				}
					
			}
			else {//Id가 등록되어 있지 않음
				send(client, str = "Ether your id or password is wrong", str.size(), 0);
			}
		}
			
		


	} while (CheckId == 1 && CheckPassword == 1);
	
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", IdSocketInfo);
	IdSocketInfo.insert(pair<string, SOCKET>(id, client));
	tool::SocketToTxt("c:/server/Id_Socket_map.txt", IdSocketInfo);
	
	return 0;
}

	
	

