#ifndef LLSTCPTRANSCLIENT_H
#define LLSTCPTRANSCLIENT_H
#include "llstcptransbase.h"

#define UDPLOG(msg) LLSTcpTransClient::instance()->write( msg,qstrlen(msg) -1 );

class QUdpSocket;
class LLSTcpTransClient : public LLSTransBase
{
    Q_OBJECT
public:
    enum NetType{TCP_Tpe,UDP_Type};
    explicit LLSTcpTransClient(NetType,QObject* paernt = 0);

    void bind(QVariant ip,QVariant port) ;
    void write(const QByteArray& msg);
    void write(const char*,int size);

    static LLSTcpTransClient* instance();

private:
    void init();

private:
    QUdpSocket*             m_pClient;
    NetType                  m_netType;
};

#endif // LLSTCPTRANSCLIENT_H
