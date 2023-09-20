#ifndef QTCPRCV_H
#define QTCPRCV_H

#include <QFile>
#include <QWidget>
#include <QTcpSocket>
#include <QDialog>

namespace Ui {
class QTcpRcv;
}

class QTcpRcv : public QDialog
{
    Q_OBJECT

public:
    explicit QTcpRcv(QWidget *parent = nullptr);
    ~QTcpRcv();
    void connectSrv();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::QTcpRcv *ui;

    QTcpSocket *cfd;

    QFile file; //文件对象
    QString fileName;   //文件名字
    int fileSize;   //文件大小
    int recvSize;   //已接收文件大小

    bool ishead;    //判断是否为头
signals:
    void rcvCloseEvent();
};

#endif // QTCPRCV_H
