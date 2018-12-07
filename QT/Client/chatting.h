#ifndef CHATTING_H
#define CHATTING_H

#include "tool.h"
#include <QTextCodec>

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
    void SetThread(QThread* t);
    void FileRead();
    void FileMove();


private slots:
    void on_MessageSend_btn_clicked();
    void Msg_Handle();

private:
    Ui::Chatting *ui;
    SOCKET sock;
    string id;
    string R_Name;
    QString filepath;
    QThread* thr;
};

#endif // CHATTING_H
