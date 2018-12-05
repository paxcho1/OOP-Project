#include "client.h"
#include <QApplication>
#include <QObject>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 윈속 초기화
        string ip = "127.0.0.1";
        int port = 4296;
        WSADATA data;
        WORD ver = MAKEWORD(2, 2);
        int wsInit = WSAStartup(ver, &data);
        if (wsInit != 0) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Warning!!");
            msgBox.setText("Winsock Reset Failed");
            msgBox.exec();
            exit(1);
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Winsock Reset Succeeded");
            msgBox.exec();
        }


        SOCKET consock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in insock;
        insock.sin_family = AF_INET;
        insock.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &insock.sin_addr);
        int result = connect(consock, (sockaddr*)&insock, sizeof(insock));
        char buf[MAX_BUFFER_SIZE];

        if (result == SOCKET_ERROR)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Warning!!");
            msgBox.setText("connect Failed");
            msgBox.exec();
            exit(1);
        }

        Client w;
        w.SetSocket(consock);
        w.show();


       return a.exec();
}
