#include "thread.h"

Thread::Thread(QObject *parent) :
    QThread(parent)
{

}
Thread::~Thread() {
}

void Thread::run()
{
        recv(Server,buf,MAX_BUFFER_SIZE,0);
        qDebug(buf);

}

void Thread::SetId(string i) {Id = i;}
void Thread::SetSocket(SOCKET s) {Server = s;}
