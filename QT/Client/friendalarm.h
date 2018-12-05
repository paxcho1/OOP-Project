#ifndef FRIENDALARM_H
#define FRIENDALARM_H

#include "tool.h"

namespace Ui {
class FriendAlarm;
}

class FriendAlarm : public QDialog
{
    Q_OBJECT

public:
    explicit FriendAlarm(QWidget *parent = nullptr);
    ~FriendAlarm();

    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    void SetId(string i);
    string GetId();
    void SetList();

private slots:

    void on_Accept_btn_clicked();

    void on_Reject_btn_clicked();

private:
    Ui::FriendAlarm *ui;
    SOCKET sock;
    string id;
    QFileInfoList NewFriend_list;
    QDir dir;
    QFile file;
};

#endif // FRIENDALARM_H
