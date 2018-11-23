#include "tool.h"


tool::tool(SOCKET client)
{
}


tool::~tool()
{
}
void tool::splitString(vector<string> &v_str, const string &str, const char ch) {
	string sub;
	string::size_type pos = 0;
	string::size_type old_pos = 0;
	bool flag = true;

	while (flag) {
		pos = str.find_first_of(ch, pos);
		if (pos == string::npos) {

			flag = false;
			pos = str.size();
		}
		sub = str.substr(old_pos, pos - old_pos);
		v_str.push_back(sub);
		old_pos = ++pos;
	}
}
void tool::Send(SOCKET client, string msg) {
	send(client, msg.c_str(), msg.size()+1, 0);
}

int tool::Recv(SOCKET client, char buf[]) {

	ZeroMemory(buf, MAX_BUFFER_SIZE);
	int Bytein = recv(client, buf, MAX_BUFFER_SIZE, 0);//메세지를 입력받음
	if (Bytein <= 0) {
		return 0;
	}
	else {
		return 1;
	}
}
void tool::VectorToTxt(const char* fileName, vector<string> &Vector) {
	ofstream wFile(fileName);
	ostream_iterator<string> wFile_iterator(wFile, "\n");
	copy(Vector.begin(), Vector.end(), wFile_iterator);
	wFile.close();
}
void tool::TxtToVector(const char* fileName, vector<string> &Vector) {
	string file_string;
	ifstream rFile(fileName);
	while (getline(rFile, file_string)) {
		if (file_string.size() > 0)
			Vector.push_back(file_string);
	}
	rFile.close();
}
void tool::MapToTxt(const char* fileName, map<string, string> &Map) {
	ofstream wFile(fileName);
	for (map<string, string>::const_iterator iterator = Map.begin(); iterator != Map.end(); ++iterator) {
		wFile << iterator->first << "|" << iterator->second;
		wFile << "\n";
	}
	wFile.close();
}
void tool::TxtToMap(const char* fileName, map<string, string> &Map) {
	ifstream rFile(fileName);
	string file_string;
	string key;
	vector<string> v_str;
	while (getline(rFile,file_string)) {
		splitString(v_str, file_string, '|');
		for (vector<string>::iterator iterator = v_str.begin();iterator != v_str.end(); (++iterator)) {
			
			Map[*iterator] = *(++iterator);
			
		}
	}

}
void tool::SocketToTxt(const char* fileName, map<string, SOCKET> &Map) {
	ofstream wFile(fileName);
	for (map<string, SOCKET>::const_iterator iterator = Map.begin(); iterator != Map.end(); ++iterator) {
		wFile << iterator->first << "|" << iterator->second;
		wFile << "\n";
	}
	wFile.close();
}
void tool::TxtToSocket(const char* fileName, map<string, SOCKET> &Id_Socket) {
	ifstream rFile(fileName);
	string file_string;
	string key;
	vector<string> v_str;
	while (getline(rFile, file_string)) {
		splitString(v_str, file_string, '|');
		for (vector<string>::iterator iterator = v_str.begin();iterator != v_str.end(); ++iterator) {
			Id_Socket[*iterator] = stoi(*(++iterator));
		}
	}
}