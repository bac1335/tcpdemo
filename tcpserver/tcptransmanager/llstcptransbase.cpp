﻿#include "llstcptransbase.h"

LLSTransBase::LLSTransBase(QObject *parent):
    QObject (parent)
{

}

void LLSTransBase::MeaasgeFromLocalToTcp(TcpMeaasge::LocalMeaasg &local, TcpMeaasge::TcpMessage &msg)
{
    msg.head.size = local.head.size;
    msg.head.type = local.head.type;
    memset(msg.str,0,sizeof(msg.str));
    memcpy(msg.str,local.data.data(),local.data.size());
}

void LLSTransBase::MessageFromTcpToLocal(TcpMeaasge::TcpMessage &msg, TcpMeaasge::LocalMeaasg &local)
{
    local.head.size = msg.head.size;
    local.head.type = msg.head.type;
    QByteArray array;
    array.resize(msg.head.size);
    memcpy(array.data(),msg.str,msg.head.size);
    local.data = array;
}

bool LLSTransBase::fromJson(QJsonObject &object, QString &desString)
{
    QJsonObject::iterator ite = object.begin();

    desString.append("{");
    while(ite != object.end()){
        if(ite != object.end() -1){
            QString str = QString("%1:%2,").arg(ite.key()).arg(getValue(ite.value()));
            desString.append(str);
        }
        else{
            QString str = QString("%1:%2").arg(ite.key()).arg(getValue(ite.value()));
            desString.append(str);
        }
        ite ++;
    }

    desString.append("}");

    return true;
}

bool LLSTransBase::toJson(QString& str,QJsonObject& jsonObject)
{
    QString json;
    //去掉{,},
    json = str.replace("{","");
    json = json.replace("}","");
    QStringList strList = json.split(",");
    if(str.count() <= 0) goto end2;

    for(auto& str : strList){
        str = str.simplified();
        QStringList dataList = str.split(":");
        if(dataList.count() != 2) goto end2;
        jsonObject.insert(dataList.first().simplified(),dataList.last().simplified());
    }
    return true;

end2:
    return false;

}

QString LLSTransBase::getValue(QJsonValueRef value){

    QString str;

    if(value.isObject()){
        QJsonObject object = value.toObject();

        QString data;
        if(fromJson(object,data)){
            str = data;
        }
    }
    else{
        str = value.toString();
    }

    return str;
}
