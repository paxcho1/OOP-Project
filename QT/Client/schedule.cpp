#include "schedule.h"
#include "ui_schedule.h"

Schedule::Schedule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Schedule)
{
    ui->setupUi(this);
    thr = new TimeThread(this);
    day = new DailyScheduleAdd(this);

    ui->Schedule_list->addItem("Today's Schedule");
    ui->Schedule_list->addItem("17:00 ~ 18:00 going home");

    QObject::connect(thr, SIGNAL(SchedulSend(QString)), this, SLOT(UpdateToday(QString)));
    QObject::connect(thr, SIGNAL(TodayEnd()), this, SLOT(TodayEnd()));
}

Schedule::~Schedule()
{
    delete day;
    thr->terminate();
    thr->quit();
    delete thr;
    delete ui;
}

void Schedule::SetSocket(SOCKET s) {
    sock = s;
}

void Schedule::SetId(string i) {
    id = i;
}

void Schedule::SetDate(QString d) {
    date = d;
    ui->Today->setText(d);
}

void Schedule::SetThread() {
   thr->SetId(id);
   thr->SetSocket(sock);
   thr->start();
}
void Schedule::on_DaySCheduleAdd_btn_clicked() {
    QString dow = date;
    QString Dat = date;
    day->SetDayofWeek(dow.remove(0, 9));
    Dat.truncate(Dat.lastIndexOf(" "));
    day->SetDate(Dat);
    day->SetSocket(sock);
    day->SetId(id);
    day->setModal(true);
    day->exec();

    SetList();
}

void Schedule::on_DaySCheduleDelete_btn_clicked() {
    QString dow = date;
    QString Dat = date;
    dow.remove(0, 9);
    Dat.truncate(Dat.lastIndexOf(" "));

    QString sel = ui->Schedule_list->currentItem()->text();
    QString ss = sel;
    ss = ss.remove(0, ss.lastIndexOf(" "));
    if (strcmp(ss.toUtf8().constData(), " Schedule") == 0) {
        QMessageBox Msgbox;
        Msgbox.setText("This is not Schedule");
        Msgbox.exec();
    }
    else {
    QStringList ls = sel.split(" ~ ");
    QStringList sls = ls[0].split(":");
    QStringList els = ls[1].split(":");
    QString sh = sls[0];
    QString sm = sls[1];
    QString eh = els[0];
    QString em = els[1];
    em.remove(2,em.size());

    QString qst =  Dat.append(" ").append(sh).append(",").append(sm).append(",").append(eh).append(",").append(em).append(" ").append(dow);
    string da = qst.toUtf8().constData();
    string msg = "003 " + da;
    qDebug(msg.c_str());
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    SetList();
    }
}
//003 yy/mm/dd ss,se,es,ee dow        일간일정삭제
void Schedule::SetList() {
    string da = date.toUtf8().constData();
    string msg = "000 " + da;
    qDebug(msg.c_str());
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
}

void Schedule::UpdateToday(QString str) {
    QString Do = str;
    QStringList ls = str.split(",");
    ls[3].remove(3);
    Do.remove(0, 9);
    QString Time = ls[0].append(":").append(ls[1]).append(" ~ ").append(ls[2]).append(":").append(ls[3]);

    QString sche = Time + " " + Do;
    ui->Schedule_list->addItem(sche);
}

void Schedule::TodayEnd() {
    QString dow = date;
    dow.remove(0, 9);
    string da = dow.toUtf8().constData();
    string ss = da + " Weekly Schedule";
    QString strLine = QString::fromUtf8(ss.c_str());
    QTextCodec *codec = QTextCodec::codecForLocale();
    QString strUnicodeLine = codec->toUnicode( strLine.toLocal8Bit() );
    ui->Schedule_list->addItem(strUnicodeLine);
}

