﻿#include "Tool.h"


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
	send(client, msg.c_str(), msg.size() + 1, 0);
}

int tool::Recv(SOCKET client, char buf[]) {

	ZeroMemory(buf, MAX_BUFFER_SIZE);
	int Bytein = recv(client, buf, MAX_BUFFER_SIZE, 0);//error handle
	if (Bytein <= 0) {
		return -1;
	}
	else {
		return 1;
	}
}

string tool::MessangerRecv(SOCKET client, string Id, char buf[]) {

	map<string, SOCKET>::iterator iter;
	map<string, SOCKET>socket_info;
	ZeroMemory(buf, MAX_BUFFER_SIZE);
	int Bytein = recv(client, buf, MAX_BUFFER_SIZE, 0);//error handle
	if (strcmp(buf, "MessangerClose") == 0) {// 메신저 종료
		cout << "id:" + Id + " is now logout" << endl;
		tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
		iter = socket_info.find(Id);
		socket_info.erase(iter);
		tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
		return "MessangerClose";
	}
	else if (strcmp(buf, "Alarm") == 0) {
		cout << "Sending new chat alarm" << endl;
		Alarm alarm(client, Id);
		alarm.Chatin(client, Id);
		return MessangerRecv(client, Id, buf);
		//알람이 아니라 msg를 받을때까지 계속 반복
	}
	else if (strcmp(buf, "NewInvite") == 0) {//새 친구 초대를 받았습니다
		cout << "Invite someone" << endl;
		Alarm alarm(client, Id);
		alarm.FriendsInvite(client, Id);
		return MessangerRecv(client,Id, buf);
	}
	else if (strcmp(buf, "NewFriend") == 0) {//친구를 추가했습니다.
		cout << "Accepting invite message" << endl;
		Alarm alarm(client, Id);
		alarm.NewFriends(client, Id);
		return MessangerRecv(client,Id, buf);
	}
	else if (Bytein <= 0) {
		cout << "id:" + Id + " is now logout" << endl;
		tool::TxtToSocket("c:/server/Id_Socket_map.txt", socket_info);
		iter = socket_info.find(Id);
		socket_info.erase(iter);
		cout << "id:" + Id + " is now logout" << endl;
		tool::SocketToTxt("c:/server/Id_Socket_map.txt", socket_info);
		return "SocketError";
	}
	return buf;
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
	while (getline(rFile, file_string)) {
		splitString(v_str, file_string, '|');
		for (vector<string>::iterator iterator = v_str.begin(); iterator != v_str.end(); (++iterator)) {

			Map[*(--iterator)] = *(++iterator);
			++iterator;
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
		for (vector<string>::iterator iterator = v_str.begin(); iterator != v_str.end(); ++iterator) {
			Id_Socket[*(--iterator)] = stoi(*(++iterator));
			++iterator;
		}
	}
}