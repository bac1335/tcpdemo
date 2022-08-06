#include "llstcptransbase.h"
#include <QUdpSocket>
#include <QDebug>

using namespace NetMeaasge;
LLSTransBase::LLSTransBase(QObject *parent):
    QObject (parent)
{

}

void LLSTransBase::MeaasgeFromLocalToTcp(LocalMeaasg &local, TcpMessage &msg)
{
    msg.head.size = local.head.size;
    msg.head.type = local.head.type;
    memset(msg.str,0,sizeof(msg.str));
    memcpy(msg.str,local.data.data(),local.data.size());
}

void LLSTransBase::MessageFromTcpToLocal(TcpMessage &msg, LocalMeaasg &local)
{
    local.head.size = msg.head.size;
    local.head.type = msg.head.type;
    QByteArray array;
    array.resize(msg.head.size - MessageHeadSize);
    memcpy(array.data(),msg.str,msg.head.size);
    local.data = array;
}

bool LLSTransBase::isSocketReadyRead(QUdpSocket *client)
{
    if(client->bytesAvailable() < MessageHeadSize) return false;
    TcpMessage meaasge;
    if(MessageHeadSize != client->peek((char*)&meaasge,MessageHeadSize))
        return false;

    if(client->bytesAvailable() < meaasge.head.size)
        return false;
    return true;
}

void LLSTransBase::onReadData()
{
    QUdpSocket* client = qobject_cast<QUdpSocket*>(sender());
    while(client->hasPendingDatagrams())
    {
        qint64 size = client->pendingDatagramSize();

        //数据包异常大小
        if( size < MessageHeadSize )
            continue;

        QByteArray ba;
        ba.resize( size );
        QHostAddress host;
        quint16 port;

        client->readDatagram( ba.data(),size,&host,&port );

        TcpMessage peekmsg;
        memcpy(&peekmsg,ba.data(),MessageHeadSize);

        //数据包损坏
        if( size != peekmsg.head.size )
            continue;

        memcpy(&peekmsg,ba.data(),size);

        UdpMessage local;
        local.data.resize(peekmsg.head.size - MessageHeadSize);
        memcpy( local.data.data(),peekmsg.str,peekmsg.head.size);
        local.ip = host.toString();
        local.port = port;

        emit sigMessage( local );
    }
}
