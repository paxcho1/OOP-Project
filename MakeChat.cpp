#include "MakeChat.h"

MakeChat::MakeChat(SOCKET client, string Id) : tool(client) 
{
}
MakeChat::~MakeChat() 
{
}
int MakeChat::Make(SOCKET client, string Id) {
	char buf[MAX_BUFFER_SIZE];
	Recv(client, buf);



	return 1;
}