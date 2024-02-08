#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include"Manager.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
private:
    //初始化UI
    void initUI();
    void connectUse();
private slots:
    void userLogin();

private:
    Ui::Login *ui;
signals:
    //登陆成功发出信号
    void Logined(QString userName);
};

#endif // LOGIN_H
