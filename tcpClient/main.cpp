#include "mainwindow.h"
#include <QApplication>
#include "llstcptransclient.h"

static void logOutput( QtMsgType type,const char*msg )
{
    UDPLOG(msg);
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMsgHandler( logOutput );
    MainWindow w;
    w.show();

    return a.exec();
}
