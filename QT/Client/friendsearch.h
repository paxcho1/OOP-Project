#ifndef FRIENDSEARCH_H
#define FRIENDSEARCH_H

#include "tool.h"

namespace Ui {
class FriendSearch;
}

class FriendSearch : public QDialog
{
    Q_OBJECT

public:
    explicit FriendSearch(QWidget *parent = nullptr);
    ~FriendSearch();
    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    void SetId(string i);
    string GetId();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FriendSearch *ui;
    SOCKET sock;
    string id;
};

#endif // FRIENDSEARCH_H
