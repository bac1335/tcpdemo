#include "llstcptransserver.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

LLSTcpTransServer::LLSTcpTransServer(QObject *parent):
    LLSTransBase(parent)
{

}

void LLSTcpTransServer::bind(QVariant ip, QVariant port)
{
    m_pTcpServer = new QTcpServer(this);
    m_pTcpServer->listen(QHostAddress(ip.toString()),port.toInt());
    connect(m_pTcpServer,&QTcpServer::newConnection,this,&LLSTcpTransServer::onNewConnect);

    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000);
    connect(m_pTimer,&QTimer::timeout,this,&LLSTcpTransServer::onCheakClient);
}

void LLSTcpTransServer::write(LocalMeaasg &message)
{
    TcpMessage tcpMsg;
    MeaasgeFromLocalToTcp(message,tcpMsg);

    QByteArray array;
    array.resize(tcpMsg.head.size);
    memcpy(array.data(),tcpMsg.str,tcpMsg.head.size);

    for(int i = 0;i<m_socketList.count();i++){
        m_socketList.at(i)->write(array);
    }
}

void LLSTcpTransServer::onNewConnect()
{
    if(m_pTcpServer->hasPendingConnections()){
        QTcpSocket* socket = m_pTcpServer->nextPendingConnection();
        connect(socket,&QTcpSocket::readyRead,this,&LLSTcpTransServer::onReadData);

        m_socketList.push_back(socket);

        if(!m_pTimer->isActive()){
            m_pTimer->start();
        }
    }
}

void LLSTcpTransServer::onReadData()
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

void LLSTcpTransServer::onCheakClient()
{
    LocalMeaasg message;
    QJsonObject object{{QString::number(type_Heartbeat),1 },{QString::number(type_Init),0 },{QString::number(type_Meaasge),"" }};
    QString beat;
    fromJson(object,beat);

    QByteArray array = beat.toUtf8();
    message.data = array ;
    message.head.size = array.size() + MeaasgeHeadSize;

    for(int i = 0;i< m_socketList.count();i++){
        QTcpSocket* client = m_socketList.at(i);

        if(-1 == client->write(array)){
            removeClient(client);
        }
    }
}

void LLSTcpTransServer::removeClient(QTcpSocket *client)
{
    if(m_socketList.contains(client)){
        m_socketList.removeOne(client);
        client->deleteLater();
        client = nullptr;
    }

    if(m_socketList.count() <= 0){
        m_pTimer->stop();
    }
}

bool LLSTcpTransServer::isSocketReadyRead(QTcpSocket *client)
{
    if(client->bytesAvailable() < MeaasgeHeadSize) return false;
    TcpMessage meaasge;
    if(MeaasgeHeadSize != client->peek((char*)&meaasge,MeaasgeHeadSize))
        return false;

    if(client->bytesAvailable() < meaasge.head.size)
        return false;

    return true;
}
