#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    void init();

private:
    QTcpSocket*         m_clientSocket = nullptr;

};

#endif // WIDGET_H
