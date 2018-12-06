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
    void FinishCount(const int value);

public slots:

};

#endif // THREAD_H
