#include "Messanger.h"
Messanger::Messanger(SOCKET client,string Id):tool(client)
{
}
Messanger::~Messanger()
{
}
int Messanger::in(SOCKET client,string Id) {
	char path[255];
	char msg[MAX_BUFFER_SIZE];
	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	cout << "메신저 접속 id:" + Id << endl;
	tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
	socket_info.insert(pair<string, SOCKET>(Id, client));
	tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
	socket_info.clear();
	while (1) {
		int Bytein = Recv(client, msg);//메세지 입력받음 여기서 메신저의 종료도 입력받는다.
		if (strcmp(msg, "MessangerClose") == 0) {// 메신저 종료
			tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
			cout << "id:" + Id + " is now logout" << endl;
			iter = socket_info.find(Id);
			socket_info.erase(iter);
			tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
			return 0;
		}
		else if (strcmp(msg, "Alarm") == 0) {
			Send(client, "Alarm");
			Alarm alam(client, Id);
			alam.Chatin(client, Id);
			//알람이 아니라 msg를 받을때까지 계속 반복
		}
		else if (strcmp(msg, "SendInvite") == 0) {
			cout << "Sending invite message" << endl;
			char buf[MAX_BUFFER_SIZE];
			string recv_id = MessangerRecv(client,Id, buf);
			if (strcmp(msg, "MessangerClose") == 0 || strcmp (msg,"SocketError")==0)
			{
				cout << "id:" + Id + " is now logout" << endl;
				return 0;
			}
			AddFriends Add(client, Id , recv_id);
			Add.Send_invite(client, Id, recv_id);
		}
		else if (strcmp(msg, "AcceptInvite") == 0) {
			cout << "Accepting invite message" << endl;
			char buf[MAX_BUFFER_SIZE];
			string recv_id =MessangerRecv(client,Id, buf);
			if (strcmp(msg, "MessangerClose") == 0 || strcmp(msg, "SocketError") ==0)
			{
				cout << "id:" + Id + " is now logout" << endl;
				return 0;
			}
			AddFriends Add(client, Id, recv_id);
			Add.Accept_invite(client, Id, recv_id);
		}
		else if (strcmp(msg, "MakeChat") == 0) {
			cout << "Making Chating room" << endl;
			MakeChat Make(client, Id);
			Make.Make(client, Id);
		}
		else if (Bytein <= 0) {
			tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
			iter = socket_info.find(Id);
			socket_info.erase(iter);
			cout << "id:" + Id + " is now logout" << endl;
			tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
			return -1;
		}
		else {//메세지를 입력받았다 //filename msg 형태로 받음
			
			char* ptr = strtok(msg, " ");
			string file = (strcpy,ptr);//file = filename
			ptr = strtok(NULL, " ");
			char Str[MAX_BUFFER_SIZE];
			string tokmsg;
			strcpy(Str, "");
			while (ptr != NULL) {
				strcat(Str, ptr);
				tokmsg = strcat(Str," ");
				ptr = strtok(NULL, " ");
			}
			string message = tokmsg;
			string pathstr = "c:/server/" + Id + "/" + file + ".txt";// message sender의 chatfile에서 채팅방 참가자의 목록을 받아옴
			strcpy(path, pathstr.c_str());
			ofstream Write(path, ios::app);
			if (Write.is_open()) {
				cout << "writing file" << endl;
				Write << Id + ": " + message << endl;//자신의 id folder에 message 저장
			}
			Write.close(); 
			char filename[MAX_BUFFER_SIZE];
			strcpy(filename, file.c_str());
			ptr = strtok(filename, ",");//index 관련 전부 삭제
			SOCKET destsock;
			while (ptr != NULL) {//ptr은 채팅방에 있는 다른 user_id이다.
				if (ptr != Id) {
					string str = ptr;// another_user_id
					string index_path = "c:/server/Socket_Id_Map.txt";
					pathstr = "c:/server/" + str + "/chat" + str + "alarm/" + file + ".txt";//filename은 같다 user/alarm/filename의 경로
					strcpy(path, pathstr.c_str());
					ofstream DWrite(path, ios::app);
					if (DWrite.is_open()) {
						cout << "writing file" << endl;
						DWrite << Id + ": " + message << endl;//참여자 id/alarm/file에 message 저장
					}//파일이 없을수는 없다.
					else if (DWrite.is_open() == false) {
						return -1;
					}
					DWrite.close();
					tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
					iter = socket_info.find(ptr);
					if (iter == socket_info.end()) {}
					else {
						destsock = iter->second;
						cout << "목표 소켓" + destsock << endl;
						Send(destsock, "Alarm");
					}
					socket_info.clear();
					//if (ptrfind = 1) {//현재 해당 user가 접속중
					//	//send alarm message
					//}+
				}
				ptr = strtok(NULL, ",");
			}
		}
	}
}