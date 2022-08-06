#ifndef TCPDEF_H
#define TCPDEF_H
#define MAXSIZE 1024*4
#include <QtGlobal>
#include <QByteArray>

namespace  NetMeaasge{

    /**
    * @brief  数据头文件，用于检验，校准
    */
    struct MessageHead{
        signed short size;
        unsigned short type;
    };

    /**
    * @brief  tcpc传输数据
    */
    struct TcpMessage{
        MessageHead head;
        char str[MAXSIZE];
    };

    /**
    * @brief  本地数据
    */
    struct LocalMeaasg{
        MessageHead head;
        QByteArray data;  //防止char*指向内容被销毁
    };

    //
    struct UdpMessage
    {
        uint port;
        QString ip;
        QByteArray data;  //防止char*指向内容被销毁
    };
}

#define MessageHeadSize sizeof(MessageHead)

#endif // TCPDEF_H
