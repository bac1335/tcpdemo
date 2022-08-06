#ifndef LLSTCPTRANSSERVER_H
#define LLSTCPTRANSSERVER_H

#include "llstcptransbase.h"
class QUdpSocket;
class QTcpSocket;
class QTimer;
class LLSTcpTransServer : public LLSTransBase{
    Q_OBJECT
public:
    explicit LLSTcpTransServer(QObject* parent = 0);
    void write(QString& msg);
    virtual void bind(QVariant ip,QVariant port);

private:
    void write( NetMeaasge::LocalMeaasg& message);

private slots:
    /**
    * @brief  新客户端接入
    */
    void onNewConnect();
    /**
    * @brief  检测客户端是否在线
    */
    void onCheakClient();
    /**
    * @brief  移除客户端
    */
    void removeClient(QTcpSocket* client);

private:
    QUdpSocket*             m_pUdpServer;
    QList<QTcpSocket*>      m_socketList;
    QTimer*                 m_pTimer;

};

#endif // LLSTCPTRANSSERVER_H
