#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include "tool.h"

class TimeThread : public QThread
{
    Q_OBJECT
public:
    TimeThread(QObject *parent = 0);
    ~TimeThread();
    void SetId(string i);
    void SetSocket(SOCKET s);

private:
    SOCKET Server;
    string Id;
    char buf[MAX_BUFFER_SIZE];
    void run();

signals:
    void SchedulSend(QString);
    void TodayEnd();
};

#endif // TIMETHREAD_H
