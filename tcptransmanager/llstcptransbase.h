#ifndef LLSTCPTRANSBASE_H
#define LLSTCPTRANSBASE_H

#include <QObject>
#include "llstcpdef.h"

#define PORT 12341
class QUdpSocket;
class LLSTransBase : public QObject{
    Q_OBJECT
public:
    enum MeaasGeType{
        type_Init,            //接受到初始化数据
        type_Meaasge,         //普通json数据，需细分
        type_Heartbeat        //心跳数据
    };

    explicit LLSTransBase(QObject* parent = 0);
    virtual void bind(QVariant ip,QVariant port) = 0;
//    virtual void write(LocalMeaasg& message) = 0;

protected:
    //应用层传输数据到tcp
    static void MeaasgeFromLocalToTcp(NetMeaasge::LocalMeaasg& local,NetMeaasge::TcpMessage& msg);

    //tcp解析数据到应用层
    static void MessageFromTcpToLocal(NetMeaasge::TcpMessage& msg,NetMeaasge::LocalMeaasg& local);

private:
    bool isSocketReadyRead(QUdpSocket* client);

signals:
    //解析数据供应用层使用
    void sigMessage( const NetMeaasge::UdpMessage& );

protected slots:
    //数据解析
    void onReadData();
};


#endif // LLSTCPTRANSBASE_H
