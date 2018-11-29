#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "tool.h"

namespace Ui {
class Timetable;
}

class Timetable : public QDialog
{
    Q_OBJECT

public:
    explicit Timetable(QWidget *parent = nullptr);
    ~Timetable();    
    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    void SetId(string i);
    string GetId();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_Messanger_btn_clicked();

private:
    Ui::Timetable *ui;
    SOCKET sock;
    string id;
};

#endif // TIMETABLE_H
