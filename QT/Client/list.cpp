#include "list.h"
#include "ui_list.h"
#include "receiver.h"
#include "friendsearch.h"
#include "friendalarm.h"
#include "makechatroom.h"
#include "chatting.h"

List::List(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::List)
{
    ui->setupUi(this);
}

List::~List()
{
    delete ui;
}

void List::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET List::GetSocket() {
    return sock;
}

void List::SetId(string i) {
    id = i;
}

string List::GetId() {
    return id;
}

void List::Receive() {

    SOCKET server = GetSocket();
    string Id = GetId();
    Receiver receiver(server, Id);

    receiver.Messanger(server, Id);

    SetList();
}

void List::SetList() {

    ui->Friend_List->clear();
    ui->Chatroom_List->clear();

    QString friendFilePath = "C:/client/";
    friendFilePath.append(QString::fromStdString(id));
    friendFilePath.append("/FriendsIndex");
    dir = friendFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Friend_list = dir.entryInfoList();
    for (int i = 0; i < Friend_list.size(); i++) {
    QFileInfo root = Friend_list.at(i);
    ui->Friend_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    }

    QString chatFilePath = "C:/client/";
    chatFilePath.append(QString::fromStdString(id));
    chatFilePath.append("/ChatAlarm");
    dir = chatFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Chat_list = dir.entryInfoList();
    int size = Chat_list.size();
    for (int i = 0; i < Chat_list.size(); i++) {
    QFileInfo root = Chat_list.at(i);
    ui->Chatroom_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    ui->Chatroom_List->item(i)->setForeground(Qt::blue);
    }
    chatFilePath.truncate(chatFilePath.lastIndexOf(QChar('/')));
    dir = chatFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Chat_list.append(dir.entryInfoList());
    for (int i = size; i < Chat_list.size(); i++) {
    QFileInfo root = Chat_list.at(i);
    ui->Chatroom_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    }
}

void List::closeEvent(QCloseEvent *bar) {
    string id = "000";
    send(sock, id.c_str(), MAX_BUFFER_SIZE, 0);
    bar->accept();
}

void List::on_Chatroom_List_itemDoubleClicked(QListWidgetItem *item)
{
    QString filepath;
    filepath = QString("%1").arg(Chat_list.at(ui->Chatroom_List->currentIndex().row()).absoluteFilePath());

    string path = "C:/client/" + id + "/ChatAlarm";
    QString r_name = ui->Chatroom_List->currentItem()->text();
    string str = r_name.toUtf8().constData();
    string msg = "006 " + str;

    Chatting chat;
    chat.setWindowTitle(r_name);
    chat.SetSocket(GetSocket());
    chat.SetId(GetId());
    chat.SetFilePath(filepath);
    chat.SetRoomName(str);
    chat.FileRead();
    filepath.truncate(filepath.lastIndexOf(QChar('/')));
    if (strcmp(filepath.toUtf8().constData(), path.c_str()) == 0) {
        chat.FileMove();
        send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
    }
    chat.setModal(false);
    chat.exec();

}


void List::on_Friendsearch_btn_clicked()
{
    FriendSearch search;
    search.setWindowTitle("Friend Search");
    search.SetSocket(GetSocket());
    search.SetId(GetId());
    search.setModal(false);
    search.exec();
}

void List::on_Friendalarm_btn_clicked()
{
    FriendAlarm alarm;
    alarm.setWindowTitle("Friend Alarm");
    alarm.SetSocket(GetSocket());
    alarm.SetId(GetId());
    alarm.SetList();
    alarm.setModal(false);
    alarm.exec();
}

void List::on_MakeChatroom_btn_clicked()
{
    MakeChatRoom make;
    make.setWindowTitle("Make Chat Room");
    make.SetSocket(GetSocket());
    make.SetId(GetId());
    make.SetList();
    make.setModal(false);
    make.exec();
}
