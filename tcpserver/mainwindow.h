#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include "tcpmessagedef.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init();
    bool isSocketReadyRead(QTcpSocket* client);

signals:
    void sigMessage(TcpMeaasge::LocalMeaasg message);

private slots:
    void onConnect();
    void onRead();
    void onMeaasge(TcpMeaasge::LocalMeaasg message);

private:
    QTcpServer*         m_pTcpServer = nullptr;
    QList<QTcpSocket*>  m_socketList;

};

#endif // MAINWINDOW_H
