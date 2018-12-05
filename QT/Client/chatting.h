#ifndef CHATTING_H
#define CHATTING_H

#include "tool.h"

namespace Ui {
class Chatting;
}

class Chatting : public QDialog
{
    Q_OBJECT

public:
    explicit Chatting(QWidget *parent = nullptr);
    ~Chatting();
    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    void SetId(string i);
    string GetId();
    void SetRoomName(string s);
    void SetFilePath(QString q);
    void FileRead();
    void FileMove();


private slots:
    void on_MessageSend_btn_clicked();

    void on_Message_Line_returnPressed();

private:
    Ui::Chatting *ui;
    SOCKET sock;
    string id;
    string R_Name;
    QString filepath;
};

#endif // CHATTING_H
