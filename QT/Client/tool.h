#ifndef TOOL_H
#define TOOL_H
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <QString>
#include <QMessageBox>
#include <QTimer>
#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QCloseEvent>
#include <QDate>
#include <QListView>
#include <QListWidget>
#include <QFileDialog>
#include <QDir>
#include <QObject>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include <algorithm>
#include <direct.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#define MAX_BUFFER_SIZE 4092
using namespace std;
class tool
{
public:
    SOCKET client;
    char buf[MAX_BUFFER_SIZE];
    tool(SOCKET client);
    ~tool();
    int Recv(SOCKET client, char buf[]);
    void Send(SOCKET client, string msg);
};

#endif // TOOL_H
