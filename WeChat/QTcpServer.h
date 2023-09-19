#ifndef QTCPSERVER_H
#define QTCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class QTcpServer;
}

class QTcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit QTcpServer(QWidget *parent = nullptr);
    ~QTcpServer();

private:
    Ui::QTcpServer *ui;
    QTcpServer *fd;     //监听套接字
    QTcpSocket *cfd;    //通信套接字
    unsigned short port;
};

#endif // QTCPSERVER_H
