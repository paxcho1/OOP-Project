#include "friendsearch.h"
#include "ui_friendsearch.h"

FriendSearch::FriendSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendSearch)
{
    ui->setupUi(this);
}

FriendSearch::~FriendSearch()
{
    delete ui;
}

void FriendSearch::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET FriendSearch::GetSocket() {
    return sock;
}

void FriendSearch::SetId(string i) {
    id = i;
}

string FriendSearch::GetId() {
    return id;
}

void FriendSearch::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    string str2 = str.toUtf8().constData();
    string msg = "002 " + str2;
    char buf[MAX_BUFFER_SIZE];
    QMessageBox Msgbox;
    string path = "c:/client/" + id + "/FriendsIndex/" + str2 + ".txt";
    QString filepath = QString::fromLocal8Bit(path.c_str());

    if (QFile::exists(filepath)) {
        Msgbox.setText("exist friend");
        Msgbox.exec();
        ui->lineEdit->clear();
    }
    else if (str2 == id) {
        Msgbox.setText("don't enter your id");
        Msgbox.exec();
        ui->lineEdit->clear();
    }
    else {
        send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

        recv(sock, buf, MAX_BUFFER_SIZE, 0);

        if(strcmp(buf, "001") == 0){
            Msgbox.setText("Can't find friend");
            Msgbox.exec();
            ui->lineEdit->clear();
        }
        else if(strcmp(buf, "002") == 0) {
            Msgbox.setText("Sending message friend request");
            Msgbox.exec();
            ui->lineEdit->clear();
        }
    }
}
