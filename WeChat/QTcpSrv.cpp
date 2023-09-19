#include "QTcpSrv.h"
#include "ui_QTcpSrv.h"

#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>

QTcpSrv::QTcpSrv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QTcpSrv)
{
    ui->setupUi(this);
    port=7373;
    fd=new QTcpServer(this);
    //启动监听
    fd->listen (QHostAddress::Any,port);
    //获取新的连接
    connect(fd,&QTcpServer::newConnection,this,[=](){
       //获取通信套接字
        cfd=fd->nextPendingConnection ();
        qDebug()<<"连接客户端成功"<<endl;
        //获取对方的IP和端口
        QString ip=cfd->peerAddress ().toString ();
        unsigned short port1=cfd->peerPort ();
        QString str=QString("[%1,%2] 连接成功").arg (ip).arg (port1);
        ui->textEdit->setText (str);
    });

    connect(&timer,&QTimer::timeout,this,[=](){
        //关闭定时器
        timer.stop ();

        //发送文件
        sendData ();
    });
}

QTcpSrv::~QTcpSrv()
{
    delete ui;
}

void QTcpSrv::sendData()
{
    int len=0;
    do{
       //每次发送数据的大小
        char buf[4*1024]={0};
        len=0;

        //往文件中读取4K数据
        len=file.read (buf,sizeof (buf));
        //发送数据，读取多少发送多少
        len=cfd->write (buf,len);

        //更新已发送的数据
        sendSize+=len;
    }while(len>0);

    //是否发送文件完毕
    if(sendSize==fileSize){
        ui->textEdit->append ("文件发送完毕");
        file.close ();

        //把客户端端口关闭
        cfd->disconnectFromHost ();
        cfd->close();
    }
}

void QTcpSrv::sendHead()
{
    qDebug()<<"发送头部信息"<<endl;
    //先发送文件头信息
    QString head=QString("%1##%2").arg (fileName).arg (fileSize);
    //发送头部信息
    int len=cfd->write (head.toUtf8 ());
    if(len>0){  //头部信息发送成功
        //发送文件真正信息
        //防止TCP粘包问题
        //需要通过定时器延时
        timer.start (20);

    }
    else{
        qDebug()<<"头部信息发送失败"<<endl;
        file.close ();
    }
    qDebug()<<"头部信息发送完毕"<<endl;
}


void QTcpSrv::on_pushButton_clicked()
{
    QString filePath=QFileDialog::getOpenFileName (this,"打开文件","../");
    if(!filePath.isEmpty ()){   //选择文件路径有效
        emit sendFilePath (filePath);
        fileName.clear ();
        fileSize=0;
        //获取文件信息
        QFileInfo info(filePath);
        fileName=info.fileName ();  //获取文件名字
        fileSize=info.size ();  //获取文件大小

        sendSize=0;  //发送文件大小

        //只读方式打开文件
        file.setFileName (filePath);
        if(!file.open (QIODevice::ReadOnly)){
            qDebug()<<"只读方式打开文件失败"<<endl;
        }
}
    else{
        qDebug()<<"选择文件路径出错"<<endl;
    }
        ui->textEdit->append ("filePath:"+filePath);
        ui->textEdit->append ("fileName"+fileName);
        ui->textEdit->append ("fileSize"+QString::number (fileSize));
}
void QTcpSrv::on_pushButton_2_clicked()
{
   emit showDiaLog ();
}
