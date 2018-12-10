#ifndef WEEKLYSCHEDULEADD_H
#define WEEKLYSCHEDULEADD_H

#include "tool.h"

namespace Ui {
class WeeklyScheduleAdd;
}

class WeeklyScheduleAdd : public QDialog
{
    Q_OBJECT

public:
    explicit WeeklyScheduleAdd(QWidget *parent = nullptr);
    ~WeeklyScheduleAdd();
    void SetSocket(SOCKET s);
    void SetId(string i);
    void SetToday(QString s);

private slots:
    void on_Add_btn_clicked();

private:
    Ui::WeeklyScheduleAdd *ui;
    QString Date;
    QString DOW;
    QString StartTime;
    QString EndTime;
    QString Contents;
    SOCKET sock;
    string id;
};

#endif // WEEKLYSCHEDULEADD_H
