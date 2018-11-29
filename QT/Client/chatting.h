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

private slots:
    void on_MessageSend_btn_clicked();

    void on_Chatroom_List_itemDoubleClicked(QListWidgetItem *item);

    void on_Friend_List_itemDoubleClicked(QListWidgetItem *item);

    void on_Message_Line_returnPressed();

    void on_Chatroom_List_itemChanged(QListWidgetItem *item);

    void on_Chatroom_List_itemSelectionChanged();

private:
    Ui::Chatting *ui;
    SOCKET sock;
    QFileInfoList Friend_list;
    QFileInfoList Chat_list;
    QDir dir;
    QFile file;
    string id;
};

#endif // CHATTING_H
