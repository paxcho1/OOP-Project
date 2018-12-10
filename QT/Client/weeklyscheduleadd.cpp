#include "weeklyscheduleadd.h"
#include "ui_weeklyscheduleadd.h"

WeeklyScheduleAdd::WeeklyScheduleAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeeklyScheduleAdd)
{
    ui->setupUi(this);
    ui->WeekSelect->addItem("mon");
    ui->WeekSelect->addItem("tue");
    ui->WeekSelect->addItem("wed");
    ui->WeekSelect->addItem("thr");
    ui->WeekSelect->addItem("fri");
    ui->WeekSelect->addItem("sat");
    ui->WeekSelect->addItem("sun");
}

WeeklyScheduleAdd::~WeeklyScheduleAdd()
{
    delete ui;
}

void WeeklyScheduleAdd::SetSocket(SOCKET s) {
    sock = s;
}

void WeeklyScheduleAdd::SetId(string i) {
    id = i;
}

void WeeklyScheduleAdd::SetToday(QString s) {
    Date = s;
}

void WeeklyScheduleAdd::on_Add_btn_clicked()
{

    DOW = ui->WeekSelect->currentText();
    StartTime = ui->WeekStartTime->time().toString("hh,mm");
    EndTime = ui->WeekEndTime->time().toString("hh,mm");
    Contents = ui->WeekContents->text();

    QString str = "005 ";
    str = str.append(Date);
    str = str.append(" ");
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
//005 yy/mm/dd ss,se,es,ee dow eff    주간일정추가
