#include "AddFriends.h"



AddFriends::AddFriends(SOCKET client,string Id):tool(client)
{
}


AddFriends::~AddFriends()
{
}
int AddFriends::Send_invite(SOCKET client, string Id) {
	return 1;
}