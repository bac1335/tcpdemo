#ifndef TCPDEF_H
#define TCPDEF_H
#define MAXSIZE 1024*8
#include <QtGlobal>
#include <QByteArray>


namespace  TcpMeaasge{

    struct MessageHead{
        signed short size;
        unsigned short type;
    };

    struct TcpMessage{
        MessageHead head;
        char str[MAXSIZE];
    };

    struct LocalMeaasg{
        MessageHead head;
        QByteArray data;  //防止char*指向内容被销毁
    };


    //应用层传输数据到tcp
    void MeaasgeFromLocalToTcp(LocalMeaasg& local,TcpMessage& msg);

    //tcp解析数据到应用层
    void MessageFromTcpToLocal(TcpMessage& msg,LocalMeaasg& local);

}

#define MeaasgeHeadSize sizeof(MessageHead)

#endif // TCPDEF_H
