#include "mainwindow.h"
#include "llstcptransserver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"--->lls<---" << __FUNCTION__;

    QJsonObject object{{"ad",12},{"ad","ad"}};


    LocalMeaasg message;
    message.data = J(object);

    message.head.size = MeaasgeHeadSize +sizeof (message.data);
    m_tcpServer->write(message);
}

void MainWindow::init()
{
    this->resize(800,600);
    this->setPalette(QPalette("#242424"));

    m_tcpServer = new LLSTcpTransServer(this);
    m_tcpServer->bind("127.0.0.1",12341);

}

