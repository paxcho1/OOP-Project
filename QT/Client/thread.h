#ifndef THREAD_H
#define THREAD_H
#include "tool.h"

class Thread: public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);
    ~Thread();
    void SetId(string i);
    void SetSocket(SOCKET s);

private:
    SOCKET Server;
    string Id;
    char buf[MAX_BUFFER_SIZE];
    void run();

signals:
    void Close();                   //000
    void NoUser();                  //001
    void FindUser();                //002
    void AcceptInvite();            //003
    void Send_Message(QString);     //006
    void ReceiveInvite(QString);           //007
    void AccceptFriend(QString);           //008
    void FinishCount(const int value);


public slots:

};

#endif // THREAD_H
