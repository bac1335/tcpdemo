#ifndef LLSTCPTRANSBASE_H
#define LLSTCPTRANSBASE_H

#include <QObject>
#include "llstcpdef.h"
#include <QJsonObject>

#define D(STRING) QString("%1:%2").arg(QString::number(LLSTransBase::type_Meaasge)).arg(STRING).toUtf8()  //普通数据

#define J(JSONOBJECT)   [=](QJsonObject object)->QByteArray{  \
                        QString disStr;QString str;     \
                        if(LLSTransBase::fromJson(object,str)){     \
                        disStr = str;     \
                        };     \
                        disStr = QString("%1:%2").arg(QString::number(LLSTransBase::type_Meaasge)).arg(disStr);   \
                        return disStr.toUtf8();     \
                        }(JSONOBJECT);  //jsonObject数据

using namespace TcpMeaasge;

class LLSTransBase : public QObject{
    Q_OBJECT
public:
    enum MeaasGeType{
        type_Init,            //接受到初始化数据
        type_Meaasge,         //普通json数据，需细分
        type_Heartbeat        //心跳数据
    };

    explicit LLSTransBase(QObject* parent = nullptr);
    virtual void bind(QVariant ip,QVariant port) = 0;
    virtual void write(LocalMeaasg& message) = 0;

    //json数据转为QString数据
    static bool fromJson(QJsonObject& object,QString& desString);
    //QString数据转为json数据
    static bool toJson(QString& str,QJsonObject& jsonObject);

protected:
    //应用层传输数据到tcp
    static void MeaasgeFromLocalToTcp(LocalMeaasg& local,TcpMessage& msg);

    //tcp解析数据到应用层
    static void MessageFromTcpToLocal(TcpMessage& msg,LocalMeaasg& local);

private:
    static QString getValue(QJsonValueRef value);

signals:
    //解析数据供应用层使用
    void sigMessage(LocalMeaasg);

protected slots:
    //数据解析
    virtual void onReadData() = 0;
};

#endif // LLSTCPTRANSBASE_H
