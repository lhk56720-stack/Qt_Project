#include "QTcpServer.h"
#include "ui_QTcpServer.h"

QTcpServer::QTcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTcpServer)
{
    ui->setupUi(this);
    port=7373;
    fd=new QTcpServer(this);

    //启动监听套接字
    fd->listen(QHostAddress::Any,port);
}

QTcpServer::~QTcpServer()
{
    delete ui;
}
