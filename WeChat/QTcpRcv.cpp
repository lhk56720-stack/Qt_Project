#include "QTcpRcv.h"
#include "ui_QTcpRcv.h"
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>

QTcpRcv::QTcpRcv(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::QTcpRcv)
{
    ui->setupUi(this);

    cfd=new QTcpSocket(this);
    ishead=true;
    ui->progressBar->setValue (0);

    connectSrv ();
    show ();

    connect(cfd,&QTcpSocket::readyRead,this,[=](){
        //接收数据
        QByteArray buf=cfd->readAll ();
         if(ishead)
         {        //接收头
             //解析头部信息并初始化
             fileName=QString(buf).section ("##",0,0);
             fileSize=QString(buf).section ("##",1,1).toUInt ();
             recvSize=0;
             //打开文件
             qDebug()<<"fileName:"<<fileName<<endl;
             file.setFileName (fileName);
             if(!file.open (QIODevice::WriteOnly)){
                 qDebug()<<"只写模式打开文件失败"<<endl;
                 cfd->disconnectFromHost ();
                 cfd->close ();
                 return;
             }
             ishead=false;

             //设置进度条
             ui->progressBar->setMinimum (0);
             if(fileSize>10*1024*1024)
                 ui->progressBar->setMaximum (fileSize/1024);
             else
                  ui->progressBar->setMaximum (fileSize);


             ui->progressBar->setValue (0);
         }
         else{      //接收文件信息
             int len=file.write (buf);
             if(len>0){
                 recvSize+=len;
             }
             if(fileSize>10*1024*1024)
                 ui->progressBar->setValue (recvSize/1024);
             else
                 ui->progressBar->setValue (recvSize);

             if(recvSize==fileSize){
                 QMessageBox::information (this,"接收完毕","文件接收完成！");
                 qDebug()<<"文件接收完毕"<<endl;
                 file.close ();
                 cfd->disconnectFromHost ();
                 cfd->close ();
             }
         }
    });
}

QTcpRcv::~QTcpRcv()
{
    delete ui;
}

void QTcpRcv::connectSrv()
{
    QString ip=ui->lineEdit_ip->text ();
    unsigned short port=ui->lineEdit_port->text ().toInt ();
    cfd->connectToHost (QHostAddress(ip),port);
    qDebug()<<"尝试连接"<<endl;
}
// 重写窗口关闭事件，发射自定义信号
void QTcpRcv::closeEvent(QCloseEvent *)
{
    emit rcvCloseEvent ();
}


