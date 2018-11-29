#include "chatting.h"
#include "ui_chatting.h"
#include "receiver.h"

Chatting::Chatting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chatting)
{
    ui->setupUi(this);

    Receiver receiver(GetSocket(), GetId());

    receiver.Chat(GetSocket(), GetId());
    receiver.Chatin(GetSocket(), GetId());
    receiver.FriendsIndex(GetSocket(), GetId());
    receiver.NewInvite(GetSocket(), GetId());
    receiver.NewFriends(GetSocket(), GetId());

    QString friendFilePath = "C:/client/";
    friendFilePath.append(QString::fromStdString(GetId()));
    dir = friendFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    ui->Friend_List->clear();
    Friend_list = dir.entryInfoList();
    for (int i = 0; i < Friend_list.size(); i++) {
    QFileInfo root = Friend_list.at(i);
    ui->Friend_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    }

    QString chatFilePath = "C:/client/";
    chatFilePath.append(QString::fromStdString(GetId()));
    dir = chatFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    ui->Chatroom_List->clear();
    Chat_list = dir.entryInfoList();
    for (int i = 0; i < Chat_list.size(); i++) {
    QFileInfo root = Chat_list.at(i);
    ui->Chatroom_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    }

}

Chatting::~Chatting()
{
    delete ui;
}

void Chatting::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET Chatting::GetSocket() {
    return sock;
}

void Chatting::SetId(string i) {
    id = i;
}

string Chatting::GetId() {
    return id;
}

void Chatting::on_MessageSend_btn_clicked()
{
    QString str = ui->Message_Line->text();
    ui->Message_Line->clear();
    string msg = str.toUtf8().constData();

}

void Chatting::on_Chatroom_List_itemDoubleClicked(QListWidgetItem *item)
{
    QString fileName;
    fileName = QString("%1").arg(Chat_list.at(ui->Chatroom_List->currentIndex().row()).absoluteFilePath());
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    ui->Chatting_Text->clear();
    ui->Chatting_Text->append(file.readAll());
    file.close();
}

void Chatting::on_Friend_List_itemDoubleClicked(QListWidgetItem *item)
{
    QString fileName;
    fileName = QString("%1").arg(Friend_list.at(ui->Friend_List->currentIndex().row()).absoluteFilePath());
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    ui->Chatting_Text->clear();
    ui->Chatting_Text->append(file.readAll());
    file.close();
}

void Chatting::on_Message_Line_returnPressed()
{
    QString str = ui->Message_Line->text();
    ui->Chatting_Text->append(str);
    ui->Message_Line->clear();
    string msg = str.toUtf8().constData();

    QString fileName;
    fileName = QString("%1").arg(Chat_list.at(ui->Chatroom_List->currentIndex().row()).absoluteFilePath());
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);
    out << ui->Chatting_Text->toPlainText().toUtf8().constData();
    file.close();
}

void Chatting::on_Chatroom_List_itemChanged(QListWidgetItem *item)
{

}

void Chatting::on_Chatroom_List_itemSelectionChanged()
{

}
