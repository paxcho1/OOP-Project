#include "groupscheduleaccept.h"
#include "ui_groupscheduleaccept.h"

GroupScheduleAccept::GroupScheduleAccept(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupScheduleAccept)
{
    ui->setupUi(this);
}

GroupScheduleAccept::~GroupScheduleAccept()
{
    delete ui;
}

void GroupScheduleAccept::SetSocket(SOCKET s) {
    sock = s;
}

void GroupScheduleAccept::SetId(string i) {
    id = i;
}

void GroupScheduleAccept::SetThread(QThread *t) {
    thr = t;
}

void GroupScheduleAccept::SetRoomName(string s) {
    R_Name = s;
}

void GroupScheduleAccept::SetDate(QString s) {
    Date = s;
}

void GroupScheduleAccept::SetTime(QString s) {
    Time = s;
}

void GroupScheduleAccept::SetDOW(QString s) {
    DOW = s;
}

void GroupScheduleAccept::SetContents(QString s) {
    Contents = s;
}

void GroupScheduleAccept::on_Accept_clicked() {
    QObject::disconnect(thr, SIGNAL(GroupAddSuccess()), this, SLOT(Success()));      //003 성공
    QObject::disconnect(thr, SIGNAL(GroupAddFailed()), this, SLOT(Failed()));        //004 실패

    QString ss = "008 ";
    qDebug(Contents.toUtf8().constData());
    ss = ss.append(R_Name.c_str()).append(" ").append(Date).append(" ").append(Time).append(" ").append(DOW).append(" ").append(Contents);

    string msg = ss.toUtf8().constData();
    qDebug(msg.c_str());

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    QObject::connect(thr, SIGNAL(GroupAddSuccess()), this, SLOT(Success()));      //003 성공
    QObject::connect(thr, SIGNAL(GroupAddFailed()), this, SLOT(Failed()));        //004 실패
}

void GroupScheduleAccept::on_Reject_clicked() {
    QString ss = "009 ";
    qDebug(Contents.toUtf8().constData());
    ss = ss.append(R_Name.c_str()).append(" ").append(Date).append(" ").append(Time).append(" ").append(DOW).append(" ").append(Contents);

    string msg = ss.toUtf8().constData();
    qDebug(msg.c_str());

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Didn't participate in the schedle"));
    Msgbox.exec();
    this->close();
}

void GroupScheduleAccept::Success() {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Schedule added"));
    Msgbox.exec();
    this->close();
}

void GroupScheduleAccept::Failed() {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Overlaps with another schedule"));
    Msgbox.exec();
    this->close();
}

