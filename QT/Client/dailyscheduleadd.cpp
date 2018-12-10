#include "dailyscheduleadd.h"
#include "ui_dailyscheduleadd.h"

DailyScheduleAdd::DailyScheduleAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DailyScheduleAdd)
{
    ui->setupUi(this);
}

DailyScheduleAdd::~DailyScheduleAdd()
{
    delete ui;
}

void DailyScheduleAdd::SetSocket(SOCKET s) {
    sock = s;
}

void DailyScheduleAdd::SetId(string i) {
    id = i;
}

void DailyScheduleAdd::SetDate(QString d) {
    Date = d;
}

void DailyScheduleAdd::SetDayofWeek(QString dow) {
    DOW = dow;
}

void DailyScheduleAdd::on_Add_btn_clicked()
{
    StartTime = ui->StartTime->time().toString("hh,mm");
    EndTime = ui->EndTime->time().toString("hh,mm");
    Contents = ui->Contents->text();
    qDebug(StartTime.toUtf8().constData());
    qDebug(EndTime.toUtf8().constData());

    QString str = "002 ";
    str = str.append(Date.append(" "));
    str = str.append(StartTime);
    str = str.append(",");
    str = str.append(EndTime);
    str = str.append(" ");
    str = str.append(DOW);
    str = str.append(" ");
    str = str.append(Contents);

    qDebug(str.toUtf8().constData());

    string msg = str.toUtf8().constData();

    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Schedule added"));
    Msgbox.exec();

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    this->close();
}
//002 yy/mm/dd ss,se,es,ee dow effasd    일간일정추가
