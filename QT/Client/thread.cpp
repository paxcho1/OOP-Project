#include "thread.h"

Thread::Thread(QObject *parent) :
    QThread(parent)
{

}
Thread::~Thread() {
}

void Thread::SetId(string i) {Id = i;}
void Thread::SetSocket(SOCKET s) {Server = s;}

void Thread::run()
{
    qRegisterMetaType<std::string>("string");
    QString strLine;
    QTextCodec *codec = QTextCodec::codecForLocale();
    QString strUnicodeLine;
    while(1) {
        recv(Server, buf, MAX_BUFFER_SIZE, 0);
        strLine = buf;
        strUnicodeLine = codec->toUnicode( strLine.toLocal8Bit() );
        qDebug().nospace() << qPrintable(strUnicodeLine);
        string code = buf;
        code = code.substr(0,3);
        if(strcmp(code.c_str(),"000")==0){

        }
        else if(strcmp(code.c_str(),"001")==0){
            emit NoUser();
        }
        else if(strcmp(code.c_str(),"002")==0){
            emit FindUser();
        }
        else if(strcmp(code.c_str(),"003")==0){

        }
        else if(strcmp(code.c_str(),"004")==0){

        }
        else if(strcmp(code.c_str(),"005")==0){

        }
        else if(strcmp(code.c_str(),"006")==0){
            strtok(buf," ");
            char* Str;
            Str = strtok(NULL," ");
            char* ptr = strtok(NULL," ");
            while(ptr!=NULL){
                strcat(Str,ptr);
                strcat(Str," ");
                ptr = strtok(NULL," ");
            }

            string msg = Str;
            QString s = QString::fromLocal8Bit(Str);
            emit Send_Message(s);
        }
        else if(strcmp(code.c_str(),"007")==0){
        }
        else if(strcmp(code.c_str(),"008")==0){

        }


        ZeroMemory(buf, MAX_BUFFER_SIZE);


    }
}
