#include "Login.h"
#include"Manager.h"
#include "WeChatMainWindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    Manager m;
    m.show ();
#else
    for(int i=0;;++i)
    {
        WeChatMainWindow *win=new WeChatMainWindow("userName");
        win->show ();
        qDebug()<<"第"<<i<<"次启动";
    }
#endif
    return a.exec();
}
