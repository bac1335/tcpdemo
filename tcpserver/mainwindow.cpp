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


}

void MainWindow::init()
{
    this->resize(800,600);
    this->setPalette(QPalette("#242424"));

    m_tcpServer = new LLSTcpTransServer(this);
    connect(m_tcpServer,SIGNAL(sigMessage( const NetMeaasge::UdpMessage& )),this,SLOT(slot_message( const NetMeaasge::UdpMessage& )));
}

void MainWindow::slot_message( const NetMeaasge::UdpMessage& data )
{
    qDebug() << "=======================================" << data.ip << data.port << data.data;
}
