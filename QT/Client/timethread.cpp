#include "timethread.h"

TimeThread::TimeThread(QObject *parent) :
    QThread(parent)
{

}

TimeThread::~TimeThread() {

}

void TimeThread::SetId(string i) {Id = i;}
void TimeThread::SetSocket(SOCKET s) {Server = s;}

void TimeThread::run() {

    qRegisterMetaType<std::string>("string");
    QString strLine;
    QTextCodec *codec = QTextCodec::codecForLocale();
    QString strUnicodeLine;
    QString mess;
    while(1) {
        qDebug("hi");
        sleep(1000);
        recv(Server, buf, MAX_BUFFER_SIZE, 0);
        strLine = buf;
        strUnicodeLine = codec->toUnicode( strLine.toLocal8Bit() );
        string ms = buf;
        string code = buf;
        code = code.substr(0,3);
        if(strcmp(code.c_str(),"000")==0){
            emit TodayEnd();
        }
        else if(strcmp(code.c_str(),"001")==0){
            strLine.remove(0,4);
            emit SchedulSend(strLine);
        }
        else if(strcmp(code.c_str(),"002")==0){

        }
        else if(strcmp(code.c_str(),"003")==0){
            strLine.remove(0,4);
            emit SchedulSend(strLine);
        }
        else if(strcmp(code.c_str(),"004")==0){

        }
        else if(strcmp(code.c_str(),"005")==0){

        }
        else if(strcmp(code.c_str(),"006")==0){
            strtok(buf, " ");
                    char* Str;
                    Str = strtok(NULL, " ");
                    string filepath = "c:/client/" + Id + "/ChatAlarm/" + Str + ".txt";

                    strLine = QString::fromLocal8Bit(ms.c_str());
                    strLine.remove(0,4);
                    mess = strLine;
                    int a = strLine.indexOf(' ');
                    strLine.remove(0, a + 1);
                    strUnicodeLine = codec->toUnicode(strLine.toLocal8Bit());
                    QString Writefilepath = QString::fromLocal8Bit(filepath.c_str());
                    QFile file(Writefilepath);
                    file.open(QIODevice::WriteOnly | QIODevice::Append);
                    QTextStream stream(&file);
                    stream << strUnicodeLine << endl;
                    file.close();



        }
        else if(strcmp(code.c_str(),"007")==0){


        }
        else if(strcmp(code.c_str(),"008")==0){


        }


        ZeroMemory(buf, MAX_BUFFER_SIZE);


    }
}
