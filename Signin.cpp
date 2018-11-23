#include "Signin.h"


Signin::Signin(SOCKET client) :tool(client)
{
}


Signin::~Signin()
{
}

int Signin::in(SOCKET client)
{
	char id[MAX_BUFFER_SIZE];
	char password[MAX_BUFFER_SIZE];
	int Id_Bytein;
	int Password_Bytein;
	//id 중복검사
	int overlap = 0;
	vector<string> V_id;
	string file_string;
	map<string, string> user_Info;
	do {
		Id_Bytein = tool::Recv(client, id);
		if (Id_Bytein <= 0) {
			return -1;
		}
		tool::TxtToVector("id_index.txt", V_id);

		//in_index 파일 불러오기(txt)

		cout << "미래가 안보여";
		if (find(V_id.begin(), V_id.end(), id) == V_id.end()) {
			//id가 없을때
			overlap = 1;
			send(client, "succeed\nYou can use this id\nNow enter your password", 55, 0);
			//id가 없다는 메세지 send
			//다음창

			/*Id_Bytein = tool::Recv(client, id);
			if (Id_Bytein <= 0) {
			   return -1;
			}
			*/
			//vector에 정보 추가
			V_id.push_back(id);
			Password_Bytein = tool::Recv(client, password);
			if (Password_Bytein <= 0) {
				return -1;
			}
			tool::VectorToTxt("id_index.txt", V_id);

			//txt파일 저장
		}
		else {

			send(client, "overlap\nRe-enter your id\n", 27, 0);
		}

		//id 중복 메세지 send

	} while (overlap == 0);
	send(client, "Successfully finished signin", 29, 0);
	user_Info.insert(pair<string, string>(id, password));

	tool::MapToTxt("Id_Ps_map.txt", user_Info);
	return 0;

}
