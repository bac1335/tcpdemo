#include "tcpmessagedef.h"

void TcpMeaasge::MeaasgeFromLocalToTcp(TcpMeaasge::LocalMeaasg &local, TcpMeaasge::TcpMessage &msg)
{
    msg.head.size = local.head.size;
    msg.head.type = local.head.type;
    memset(msg.str,0,sizeof(msg.str));
    memcpy(msg.str,local.data.data(),local.data.size());

}

void TcpMeaasge::MessageFromTcpToLocal(TcpMeaasge::TcpMessage &msg, TcpMeaasge::LocalMeaasg &local)
{
    local.head.size = msg.head.size;
    local.head.type = msg.head.type;
    QByteArray array;
    array.resize(msg.head.size);
    memcpy(array.data(),msg.str,msg.head.size);
    local.data = array;
}
