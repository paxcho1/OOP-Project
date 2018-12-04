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
	char str[MAX_BUFFER_SIZE];
	int Id_Bytein;
	int Password_Bytein;
	//id �ߺ��˻�
	int overlap = 0;
	vector<string> V_id;
	string file_string;
	map<string, string> user_Info;
	tool::TxtToVector("id_index.txt", V_id);
	do {
		Id_Bytein = tool::Recv(client, id);
		if (strcmp(id, "SigninClose") == 0) {
			return -1;
		}
		else if (Id_Bytein <= 0) {
			return -1;
		}

		//in_index ���� �ҷ�����(txt)

		if (find(V_id.begin(), V_id.end(), id) == V_id.end()) {
			//id�� ������
			overlap = 1;
			strcpy_s(str, sizeof(str), "Successfully finished signin");
			send(client, str, MAX_BUFFER_SIZE, 0);
			/*Id_Bytein = tool::Recv(client, id);
			if (Id_Bytein <= 0) {
			return -1;
			}
			*/
			//vector�� ���� �߰�
			V_id.push_back(id);
			Password_Bytein = tool::Recv(client, password);

			tool::VectorToTxt("id_index.txt", V_id);

			//txt���� ����
		}
		else {
			strcpy_s(str, sizeof(str), "overlap\nRe-enter your id\n");
			send(client, str, MAX_BUFFER_SIZE, 0);
		}
		//id �ߺ� �޼��� send
	} while (overlap == 0);

	string file = id;
	string path = "c:/server/" + file;
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/chat" + file + "alarm";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/friends" + file + "alarm";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/friends" + file + "invite";
	_mkdir(path.c_str());
	path = "c:/server/" + file + "/friends" + file;
	_mkdir(path.c_str());
	path = "c:/server/schedule/daily" + file ;
	_mkdir(path.c_str());
	path = "c:/server/schedule/weekly" + file;
	_mkdir(path.c_str());
	path = "c:/server/schedule/weekly" + file + "/mon";
	_mkdir(path.c_str());
	path = "c:/server/schedule/weekly" + file + "/tue";
	_mkdir(path.c_str());
	path = "c:/server/schedule/weekly" + file + "/wed";
	_mkdir(path.c_str());
	path = "c:/server/schedule/weekly" + file + "/thu";
	_mkdir(path.c_str());
	path = "c:/server/schedule/weekly" + file + "/fri";
	_mkdir(path.c_str());
	path = "c:/server/schedule/weekly" + file + "/sat";
	_mkdir(path.c_str());
	path = "c:/server/schedule/weekly" + file + "/sun";
	_mkdir(path.c_str());
	//txt���� map����
	tool::TxtToMap("c:/server/Id_Ps_map.txt", user_Info);
	user_Info.insert(pair<string, string>(id, password));

	tool::MapToTxt("c:/server/Id_Ps_map.txt", user_Info);
	return 0;

}