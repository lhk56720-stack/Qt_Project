#ifndef QTCPSRV_H
#define QTCPSRV_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QDialog>

namespace Ui {
class QTcpSrv;
}

class QTcpSrv : public QDialog
{
    Q_OBJECT

public:
    explicit QTcpSrv(QWidget *parent = nullptr);
    ~QTcpSrv();
    void sendData();
    void sendHead();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::QTcpSrv *ui;
    QTcpServer *fd; //监听套接字
    QTcpSocket *cfd;    //通信套接字
    unsigned short port;

    QFile file; //文件对象
    QString fileName;   //文件名字
    int fileSize;   //文件大小
    int sendSize;   //已发送文件大小

    QTimer timer;    //定时器

signals:
    void sendFilePath(QString path);
    void showDiaLog();
};

#endif // QTCPSRV_H
