#include "Signin.h"


Signin::Signin(SOCKET client):tool(client)
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
	set<pair<string, string>> user_Info;
	do {
		Id_Bytein = tool::Recv(client, id);
		if (Id_Bytein <= 0) {
			return -1;
		}
		ifstream rFile("Id_index.bin", ios_base::binary);//파일 읽기로 열기
		unsigned vsize;

		//읽기
		rFile.read(reinterpret_cast<char*>(&vsize), sizeof(unsigned));
		vector<string> theId(vsize);
		rFile.read(reinterpret_cast<char*>(&theId[0]), vsize * sizeof(string));
		V_id = theId;
		rFile.close();
		//in_index 파일 불러오기(binary)
		//ifstream File("Id_index.bin", ios::in | ios::binary);
		
		cout << "미래가 안보여";
		if (find(V_id.begin(), V_id.end(), id) == V_id.end()) {
			//id가 없을때
			overlap = 1;
			send(client, "succeed", 8, 0);
			//id가 없다는 메세지 send
			//다음창

			Id_Bytein = tool::Recv(client, id);
			if (Id_Bytein <= 0) {
				return -1;
			}
			Password_Bytein = tool::Recv(client, password);
			if (Password_Bytein <= 0) {
				return -1;
			}
			//vector에 정보 추가
			V_id.push_back(id);
			ofstream wFile("Id_index.bin",ios_base::binary);//파일 쓰기로 열기
			unsigned V_idSize = V_id.size();
			//파일 기
			wFile.write(reinterpret_cast<char *>(&V_idSize), sizeof(unsigned));
			wFile.write(reinterpret_cast<char *>(&V_id[0]), V_id.size() * sizeof(string));
			wFile.close();
			//binary 저장
		}
		else {

			send(client, "overlap", 8, 0);
		}
		
			//id 중복 메세지 send
	}while (overlap==0);


	return 0;

}
