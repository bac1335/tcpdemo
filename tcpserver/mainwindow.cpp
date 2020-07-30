#include "mainwindow.h"
#include <QTcpSocket>
using namespace TcpMeaasge;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    this->resize(800,600);
    this->setPalette(QPalette("#242424"));

    m_pTcpServer = new QTcpServer(this);
    m_pTcpServer->listen(QHostAddress::LocalHost,1234);
    connect(m_pTcpServer,&QTcpServer::newConnection,this,&MainWindow::onConnect);

    connect(this,&MainWindow::sigMessage,this,&MainWindow::onMeaasge);

}

bool MainWindow::isSocketReadyRead(QTcpSocket* client)
{
    if(client->bytesAvailable() < MeaasgeHeadSize) return false;
    TcpMessage meaasge;

    if(MeaasgeHeadSize != client->peek((char*)&meaasge,MeaasgeHeadSize))
        return false;

    qDebug() << "--->lls<---" << __FUNCTION__  << client->bytesAvailable() << meaasge.head.size;

    if(client->bytesAvailable() < meaasge.head.size)
        return false;
    return true;
}

void MainWindow::onConnect()
{
    qDebug()<<"--->lls<---" << __FUNCTION__<< "================================";
    if(m_pTcpServer->hasPendingConnections()){
         QTcpSocket* client = m_pTcpServer->nextPendingConnection();
         connect(client,&QTcpSocket::readyRead,this,&MainWindow::onRead);
         m_socketList.push_back(client);
    }
}

void MainWindow::onRead()
{
    qDebug() << "--->lls<---" << __FUNCTION__  << "server_resiver";
    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());
    if(!m_socketList.contains(client)) return;
    while(true){
        if(!isSocketReadyRead(client)) break;   //数据不满足，不读取

        TcpMessage readmsg;
        memset(&readmsg,0,sizeof(readmsg));
        TcpMessage peekmsg;
        client->peek((char*)&peekmsg, MeaasgeHeadSize);
        client->read((char*)&readmsg,peekmsg.head.size);

        LocalMeaasg local;

        MessageFromTcpToLocal(readmsg,local);

        emit sigMessage(local);
    }


}

void MainWindow::onMeaasge(LocalMeaasg message)
{
    qDebug() << "=================123====================" << message.data;
}
