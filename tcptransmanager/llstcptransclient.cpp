#include "llstcptransclient.h"
#include <QTcpSocket>
#include <QUdpSocket>
#include <QHostAddress>

using namespace NetMeaasge;
LLSTcpTransClient::LLSTcpTransClient(LLSTcpTransClient::NetType type, QObject *parent)
    :LLSTransBase(parent),m_netType(type)
{
     init();
}

void LLSTcpTransClient::bind(QVariant ip, QVariant port)
{

}

void LLSTcpTransClient::write(const QByteArray &msg)
{
    TcpMessage message;
    message.head.type = type_Meaasge;
    message.head.size = MessageHeadSize + msg.size();
    memcpy(message.str,msg.data(),msg.size());

    QByteArray sendData;
    sendData.resize( message.head.size );
    memcpy( sendData.data(),&message,message.head.size );
    m_pClient->writeDatagram(sendData,QHostAddress("127.0.0.1"),PORT);
}

void LLSTcpTransClient::write(const char *data,int size )
{
    QByteArray msg;
    msg.resize( size );
    memcpy(msg.data(),data,size);

    TcpMessage message;
    message.head.type = type_Meaasge;
    message.head.size = MessageHeadSize + msg.size();
    memcpy(message.str,msg.data(),msg.size());

    QByteArray sendData;
    sendData.resize( message.head.size );
    memcpy( sendData.data(),&message,message.head.size );
    m_pClient->writeDatagram(sendData,QHostAddress("127.0.0.1"),PORT);
}

LLSTcpTransClient *LLSTcpTransClient::instance()
{
    static LLSTcpTransClient instance(UDP_Type);
    return &instance;
}

void LLSTcpTransClient::init()
{
    m_pClient = new QUdpSocket(this);
}
