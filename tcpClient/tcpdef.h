#ifndef TCPDEF_H
#define TCPDEF_H
#define MAXSIZE 1024*8
#include <QtGlobal>
#include <QByteArray>

struct MessageHead{
    signed short size;
    unsigned short type;
};

struct TcpMessage{
    MessageHead head;
    char str[MAXSIZE];
};

struct localMeaasg{
    MessageHead head;
    QByteArray data;  //防止char*指向内容被销毁
};

void MeaasgeFromLocalToTcp(localMeaasg& local,TcpMessage& msg){
    msg.head.size = local.head.size;
    msg.head.type = local.head.type;
    memset(msg.str,0,sizeof(msg.str));
    memcpy(msg.str,local.data.data(),local.data.size());
}

#define MeaasgeHeadSize sizeof(MessageHead)

#endif // TCPDEF_H
