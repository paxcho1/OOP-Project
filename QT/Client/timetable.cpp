#include "timetable.h"
#include "ui_timetable.h"
#include "chatting.h"

Timetable::Timetable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timetable)
{
    ui->setupUi(this);
}

Timetable::~Timetable()
{
    delete ui;
}

void Timetable::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET Timetable::GetSocket() {
    return sock;
}

void Timetable::SetId(string i) {
    id = i;
}

string Timetable::GetId() {
    return id;
}

void Timetable::on_calendarWidget_clicked(const QDate &date)
{

}

void Timetable::on_Messanger_btn_clicked()
{
    string msg = "Messanger";
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
    Chatting chat;
    chat.setWindowTitle("Messanger");
    send(sock, GetId().c_str(), MAX_BUFFER_SIZE, 0);
    chat.SetSocket(GetSocket());
    chat.SetId(GetId());
    chat.setModal(false);
    chat.exec();
}
