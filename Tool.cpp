#include "tool.h"


tool::tool(SOCKET client)
{
}


tool::~tool()
{
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
void tool::Send(SOCKET client, string msg) {
	send(client, msg.c_str(), msg.size() + 1, 0);
}