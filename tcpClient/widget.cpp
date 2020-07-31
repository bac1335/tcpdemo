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

    QByteArray array;
    array.resize(msg.head.size);
    memcpy(array.data(),&msg,msg.head.size);
    qDebug() << "--->lls<---" << __FUNCTION__  << "======================" <<array;

    m_clientSocket->write(array,array.size());
}

void Widget::init()
{
    m_clientSocket = new QTcpSocket(this);
    m_clientSocket->connectToHost(QHostAddress::LocalHost,12341);
    bool ok = m_clientSocket->waitForConnected(10000);
    qDebug() << "===================================" << ok;
}
