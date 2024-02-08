#include "Login.h"
#include "Register.h"
#include "ui_Login.h"
#include<WeChatMainWindow.h>

#include<QTextStream>
#include <QFile>
#include<QMessageBox>
#include<QDebug>
#include<QFileDialog>
#include <QTextCodec>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    initUI();
    connectUse();
}

Login::~Login()
{
    delete ui;
}

void Login::initUI()
{
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);  // 禁用最大化按钮
    setFixedSize(width(), height());  // 设置固定的窗口大小，禁止调整窗口大小
    setWindowIcon (QIcon(":/icon/wechat.png"));
    setWindowTitle ("登录");
    ui->wechat->setPixmap (QPixmap(":/icon/wechat.png").scaled (150,150));
    //设置背景颜色
    setStyleSheet("background-color: white;");
    //测试代码
#if 0
    ui->passWord->setText ("123");
    static int i=0;
    if(i==0){
        ui->userName->setText ("hdm");
    }
    else if (i==1) {
        ui->userName->setText ("wxc");
    }
    else if(i==2){
        ui->userName->setText ("lzh");
    }
    else {
        ui->userName->clear ();
    }
    i++;
#endif
}

void Login::connectUse()
{
    //登录按钮点击事件
    connect(ui->login_btn,&QPushButton::clicked,this,&Login::userLogin);
    //注册按钮点击事件
    connect(ui->register_btn,&QPushButton::clicked,this,[=](){
       Register *reg=new Register();
       reg->show ();
    });
}

void Login::userLogin()
{
    bool flag=false;
    QFile userfile("user.txt");
    QTextStream stream(&userfile);
//    stream.setCodec ("UTF-8");
    if(!userfile.open (QIODevice::ReadWrite|QIODevice::Text)){
        QMessageBox::information (this,"打开文件","打开文件失败!");
        return;
    }
    QString userName=ui->userName->text ();
    QString passWord=ui->passWord->text ();
    QString user="用户名:";
    while(!stream.atEnd ()){
        QString userline=stream.readLine ();
        QString passwordline=stream.readLine ();
        if("用户名:"+userName==userline&&"密码:"+passWord==passwordline&&!onlineUsers.contains (userName)){
            emit Logined (userName);
             flag=true;
             break;
        }
        qDebug()<<"用户名:"+userName<<" "<<userline<<endl;
        qDebug()<<"密码:"+passWord<<" "<<passwordline<<endl;
    }
    userfile.close ();
    if(flag){
           WeChatMainWindow *win=new WeChatMainWindow(userName);
           win->show ();
           this->close ();
    }
    else if(onlineUsers.contains (userName)){
        QMessageBox::warning (this,tr("登录"),tr("您的账户已登录,请勿重复登陆!"));
    }
    else
        QMessageBox::warning (this,tr("登录"),tr("请输入正确的账号或密码！"));
}
