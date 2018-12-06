#include "timetable.h"
#include "ui_timetable.h"
#include "chatting.h"
#include "list.h"

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

    QDate Date = ui->calendarWidget->selectedDate();
    QString str = Date.toString("yyMMdd ddd");
    string da = str.toUtf8().constData();
    string msg = "000 " +da;
    char buf[MAX_BUFFER_SIZE];

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
}

void Timetable::on_Messanger_btn_clicked()
{
    string msg = "Messanger";
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
    send(sock, GetId().c_str(), MAX_BUFFER_SIZE, 0);

    List list;
    list.setWindowTitle("Friend&Chatting room List");
    list.SetSocket(GetSocket());
    list.SetId(GetId());
    list.setModal(false);
    list.Receive();
    list.Thre();
    list.exec();
}
void Timetable::get(){
    char buf[MAX_BUFFER_SIZE];
    while(1){
    R->Get(sock,id,buf);
    }
}
