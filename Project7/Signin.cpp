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
	//id �ߺ��˻�
	int overlap = 0;
	vector<string> V_id;
	string file_string;
	map<string, string> user_Info;
	do {
		Id_Bytein = tool::Recv(client, id);
		if (Id_Bytein <= 0) {
			return -1;
		}
		ifstream rFile("Id_index.txt");
		while (getline(rFile, file_string)) {
			if (file_string.size() > 0)
				V_id.push_back(file_string);
		}
		rFile.close();
			/*
			ifstream rFile("Id_index.bin", ios_base::binary);
			unsigned vsize;

			rFile.read(reinterpret_cast<char*>(&vsize), sizeof(unsigned));
			//V_id.resize(vsize);
			vector<string> the_Id(vsize);
			rFile.read(reinterpret_cast<char*>(&the_Id[0]), vsize * sizeof(string));
			V_id = the_Id;
			rFile.close();
		*/
		//in_index ���� �ҷ�����(binary)
		//ifstream File("Id_index.bin", ios::in | ios::binary);
		
		cout << "�̷��� �Ⱥ���";
		if (find(V_id.begin(), V_id.end(), id) == V_id.end()) {
			//id�� ������
			overlap = 1;
			send(client, "succeed", 8, 0);
			//id�� ���ٴ� �޼��� send
			//����â

			Id_Bytein = tool::Recv(client, id);
			if (Id_Bytein <= 0) {
				return -1;
			}
			Password_Bytein = tool::Recv(client, password);
			if (Password_Bytein <= 0) {
				return -1;
			}
			//vector�� ���� �߰�
			
			V_id.push_back(id);
			ofstream wFile("Id_index.txt");
			ostream_iterator<string> wFile_iterator(wFile, "\n");
			copy(V_id.begin(), V_id.end(), wFile_iterator);
			wFile.close();
			/*
			ofstream wFile("Id_index.bin",ios_base::binary);
			unsigned V_idSize = V_id.size();
			wFile.write(reinterpret_cast<char *>(&V_idSize), sizeof(unsigned));
			wFile.write(reinterpret_cast<char *>(&V_id[0]), V_id.size() * sizeof(string));
			wFile.close();
			*/
			//binary ����
		}
		else {

			send(client, "overlap", 8, 0);
		}
		
			//id �ߺ� �޼��� send
	
	}while (overlap==0);
	
	user_Info.insert(pair<string, string>(id, password));
	
	ofstream wFile("Id_Ps_map.txt");
	for (map<string, string>::const_iterator iterator = user_Info.begin(); iterator != user_Info.end();) {
		wFile << iterator->first << "|" << iterator->second;
		wFile << "\n";
	}

	wFile.close();

	return 0;

}
 