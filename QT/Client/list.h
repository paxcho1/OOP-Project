#ifndef LIST_H
#define LIST_H

#include "tool.h"
#include "thread.h"

namespace Ui {
class List;
}

class List : public QDialog
{
    Q_OBJECT

public:
    explicit List(QWidget *parent = nullptr);
    ~List();
    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    void SetId(string i);
    string GetId();
    void SetList();
    void Receive();
    void Thre();

private slots:

    void on_Chatroom_List_itemDoubleClicked(QListWidgetItem *item);

    void on_Friendsearch_btn_clicked();

    void on_Friendalarm_btn_clicked();

    void on_MakeChatroom_btn_clicked();

private:
    void closeEvent(QCloseEvent *bar);
    Ui::List *ui;
    SOCKET sock;
    QFileInfoList Friend_list;
    QFileInfoList Chat_list;
    QDir dir;
    QFile file;
    string id;
    Thread* thread;
};

#endif // LIST_H
