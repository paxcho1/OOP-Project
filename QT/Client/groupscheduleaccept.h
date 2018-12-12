#ifndef GROUPSCHEDULEACCEPT_H
#define GROUPSCHEDULEACCEPT_H

#include "tool.h"

namespace Ui {
class GroupScheduleAccept;
}

class GroupScheduleAccept : public QDialog
{
    Q_OBJECT

public:
    explicit GroupScheduleAccept(QWidget *parent = nullptr);
    ~GroupScheduleAccept();
    void SetSocket(SOCKET s);
    void SetId(string i);
    void SetRoomName(string s);
    void SetThread(QThread* t);
    void SetDate(QString s);
    void SetTime(QString s);
    void SetDOW(QString s);
    void SetContents(QString s);

private slots:
    void on_Accept_clicked();
    void on_Reject_clicked();
    void Success();
    void Failed();

private:
    Ui::GroupScheduleAccept *ui;
    SOCKET sock;
    string id;
    string R_Name;
    QString Date;
    QString Time;
    QString DOW;
    QString Contents;
    QThread* thr;
};

#endif // GROUPSCHEDULEACCEPT_H
