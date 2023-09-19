#include "Login.h"
#include<Manager.h>
#include <QApplication>
#include<Globals.h>
#include "QTcpRcv.h"
#include "QTcpSrv.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manager m;
    m.show ();
//    QTcpSrv srv;
//    srv.show ();
//    QTcpRcv rcv;
//    rcv.show ();
    return a.exec();
}
