#include "Signin.h"



Signin::Signin(SOCKET client)
{
}


Signin::~Signin()
{
}

void Signin::in(SOCKET client)
{
	char id[MAX_BUFFER_SIZE];
	char password[MAX_BUFFER_SIZE];
	int Id_Bytein;
	int Password_Bytein;
	//id 중복검사
	int overlap = 0;
	do {
		
		{
		//id receive
		//에러 메세지
		//id map 검색
		//if () {//id가 없을때
			overlap = 1;
			//id가 없다는 메세지 send
		//}
		//else if {//id가 있을때

			//id 중복 메세지 send

		}
	}while (overlap==0);




}
