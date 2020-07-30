#include "widget.h"
#include <QHostAddress>
#include "tcpmessagedef.h"
using namespace TcpMeaasge;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init();
}

Widget::~Widget()
{

}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "--->lls<---" << __FUNCTION__  << "cliend_send";

    LocalMeaasg message;
    message.data = "123123qwdasdasdqwe21ewads";
    message.head.type = 123;
    message.head.size = message.data.size() + MeaasgeHeadSize;

    TcpMessage msg;
    MeaasgeFromLocalToTcp(message,msg);
    qDebug() << "--->lls<---" << __FUNCTION__  << "======================" << msg.head.size ;

    QByteArray array;
    array.resize(msg.head.size);
    memcpy(array.data(),&msg,msg.head.size);

    m_clientSocket->write(array);
}

void Widget::init()
{
    m_clientSocket = new QTcpSocket(this);
    m_clientSocket->connectToHost(QHostAddress::LocalHost,1234);
    bool ok = m_clientSocket->waitForConnected(10000);
    qDebug() << "===================================" << ok;
}
