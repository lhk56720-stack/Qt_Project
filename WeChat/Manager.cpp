#include "Manager.h"
#include "ui_Manager.h"
#include"Login.h"

QSet<QString> onlineUsers; // 定义全局变量

Manager::Manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);
    QSet<QString> onlineUsers; // 定义全局变量
    initUI();
    connectUse();
}

Manager::~Manager()
{
    delete ui;
}

void Manager::initUI()
{
    // 禁用最大化按钮
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    // 设置固定的窗口大小，禁止调整窗口大小
    setFixedSize(width(), height());
    //设置背景颜色
    setStyleSheet("background-color: white;");
    ui->bt->setStyleSheet("background-color: rgb(60, 176, 80);");
    ui->icon_lbl->setPixmap (QPixmap(":/icon/wechat.png"));
    ui->icon_lbl->setFixedSize(QPixmap(":/icon/wechat.png").size());
    setWindowIcon (QIcon(":/icon/wechat.png"));
    setWindowTitle ("微信客户端启动项");
    ui->bt->setText ("启动微信");
    //设置Enter有效
    ui->bt->setAutoDefault (true);
}

void Manager::connectUse()
{
    //启动登录界面
    connect(ui->bt,&QPushButton::clicked,this,[=](){
        Login *login=new Login;
        login->show ();
        connect(login,&Login::Logined,this,&Manager::addOnlineUsers);
    });
}

void Manager::addOnlineUsers(QString userName)
{
    //添加登录的用户
    onlineUsers.insert (userName);
}
