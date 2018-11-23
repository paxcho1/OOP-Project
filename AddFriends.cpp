#include "AddFriends.h"



AddFriends::AddFriends(SOCKET client,string Id,string recv_id):tool(client)
{
}


AddFriends::~AddFriends()
{
}
int AddFriends::Send_invite(SOCKET client, string Id , string recv_id) {
	char path[255];
	char file[MAX_BUFFER_SIZE];
	string filepath = "c:/server/" + recv_id + "/" + "friends" + recv_id + "alarm/" + Id + ".txt";
	ofstream Write(filepath, ios::app);
	if (Write.is_open()) {
		cout << "writing file" << endl;
		Write << Id << endl;
	}
	Write.close();
	//Send("Alarm");
	return 1;
}