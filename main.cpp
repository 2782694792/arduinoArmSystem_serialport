#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

//  命令行变量的数量argc  命令行变量的数组argv
int main(int argc, char *argv[])
{
    //  应用程序对象，有且仅有一个
    QApplication a(argc, argv);
    //  窗口对象MainWindow  -->  父类Widget   -->   基类QMainWindow、QDialog
    MainWindow w;
    w.setWindowTitle("串口调试助手");
    //  默认不显示窗口对象，需show
    w.show();
    //  应用对象进入消息循环，实现代码阻塞，实时更新
    //    Qt消息框
    QMessageBox::aboutQt(NULL, "QtAbout");

    qDebug("进入主页");
    return a.exec();
}

/*
    * 运行ctrl R
    * 编译ctrl B
    * 查找替换ctrl F
    * 移动整行ctrl shift ↑
    * 选中光标所在单词ctrl u
    * 对齐ctrl I
    * 快速添加函数定义(头文件中定义)alt Enter
    * 快捷窗口alt 1-8
    * 添加删除书签ctrl M          跳转书签ctrl .
    * 帮助文档F1        Assitant            左侧帮助按钮
    * 同名源文件和头文件进行切换F4
*/
