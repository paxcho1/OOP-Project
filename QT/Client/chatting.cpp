#include "chatting.h"
#include "ui_chatting.h"
#include <QTextCodec>

Chatting::Chatting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chatting)
{
    ui->setupUi(this);
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

void Chatting::SetRoomName(string s) {
    R_Name = s;
}

void Chatting::SetFilePath(QString q) {
    filepath = q;
}

void Chatting::on_MessageSend_btn_clicked()
{
    QString str = ui->Message_Line->text();
    string contents = str.toUtf8().constData();
    ui->Message_Line->clear();

    string msg = "005 " + R_Name + " " + contents;
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
}

void Chatting::on_Message_Line_returnPressed()
{
    QString str = ui->Message_Line->text();
    string contents = str.toUtf8().constData();
    ui->Message_Line->clear();

    string msg = "005 " + R_Name + " " + contents;
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

}

void Chatting::FileRead() {
//    ifstream Read(filepath.toLocal8Bit().constData());
//    if (Read.is_open()) {
//        string msg;
//        getline(Read, msg);
//        while (!Read.eof()) {
//            ui->Chatting_Text->append(msg.c_str());
//            getline(Read, msg);
//        }
//        Read.close();
//    }

    QFile file(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    ui->Chatting_Text->clear();
    QTextStream stream(&file);
    while(!stream.atEnd()) {
    QString strLine = stream.readLine();
    QTextCodec *codec = QTextCodec::codecForLocale();
    QString strUnicodeLine = codec->toUnicode( strLine.toLocal8Bit() );
    ui->Chatting_Text->append(strUnicodeLine);
    }
    file.close();
}

void Chatting::FileMove() {
    string chatfilepath = "c:/client/" + id + "/" + R_Name + ".txt";
    string alarmfilepath = filepath.toUtf8().constData();

    ofstream Write(chatfilepath, ios::app);
    ifstream Read(alarmfilepath);
    if (Write.is_open() && Read.is_open()) {
        string message;
        getline(Read, message);
        while (!Read.eof()) {
            Write << message << endl;
            getline(Read, message);
        }
        Write.close();
        Read.close();
    }
    remove(alarmfilepath.c_str());
}

