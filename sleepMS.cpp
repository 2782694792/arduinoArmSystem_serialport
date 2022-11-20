#include <QCoreApplication>
#include <QTime>
#include <mainwindow.h>

//自定义延时
void sleep_MS(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
}
