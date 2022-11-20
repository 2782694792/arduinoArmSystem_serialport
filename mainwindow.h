#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct global_serial
{
    bool isSerialOpen = 0;
    QString textEdit_SendText;
    QByteArray textEdit_SendTextUTF8;
    int serialDataCountTx = 0, serialDataCountRx = 0;
    qint64 serialTx, serialRX;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    struct global_serial global_serials;


    QByteArray buffer;


    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    //    主界面控制显示设置
    void application_UISettings();
    //    串口查询和自适应宽度
    void serialPort_Find();
    //    打开关闭串口时，控件使能与失能
    void controls_SerialOpen_SetEnabled(bool = true);
    //    发送时，控件使能与失能
    void controls_SerialSend_SetEnabled(bool = true);
    //    检测时，控件使能与失能
    void controls_SerialFind_SetEnabled(bool = true);

    //    串口对应的波特率、数据位、校验位、停止位的信息判定
    void controls_Info();
    //    串口转换发送
    void serialPort_Write(QByteArray, int);
    //    发送文本框槽函数
    void textEdit_Changed();
    //    串口数据显示记录
    void serialPort_Record(QByteArray, int);

private:
    //    自带的串口类
    QSerialPort serial;

    //槽函数
private slots:
    //    发送信息
    void on_pushButton_Send_clicked();
    //    检查串口
    void on_pushButton_Check_clicked();
    //    读取可用串口号
    void serialPort_ReadAvailable();
    //    打开串口
    void on_pushButton_Open_clicked();
    //    菜单栏监听回调
    void menuBar_Action(QAction *a);
    void on_textEdit_Receipt_textChanged();
};
#endif // MAINWINDOW_H
