#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comboBoxUp.h"
#include <QDebug>

#include <QMessageBox>

/*
 * 主窗口
 */
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //    连接信号和槽：连接函数（指定类《控件》,信号，主体应用，槽函数）
    connect(ui->menubar,SIGNAL(triggered(QAction*)), this, SLOT(menuBar_Action(QAction*)));
    connect(&serial, &QSerialPort::readyRead, this, &MainWindow::serialPort_ReadAvailable);
    //    发送文本框信号槽
    textEdit_Changed();
    //    控件设置
    application_UISettings();
    controls_SerialFind_SetEnabled(0);
    this->setWindowIcon(QIcon(".\\Image\\serial2.png"));

}

/*
 * 析构函数
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * 串口数据发送
 */
void MainWindow::on_pushButton_Send_clicked()
{
    global_serials.textEdit_SendText = ui->textEdit_Send->toPlainText();
    if(global_serials.isSerialOpen == true){
        //        ui->pushButton_Send->setEnabled(false);
        //        ui->pushButton_Send->setText("发送中...");
        //    获取界面数据并转换成utf-8格式的字节流
        QByteArray data = (global_serials.textEdit_SendText).toUtf8();
        //    写入串口进行数据显示
        serialPort_Write(data, global_serials.serialDataCountTx);
    }
    else{
        //            消息窗口弹窗提示
        QMessageBox :: information(NULL, "提示", "发送信息之前，请当前串口无法读写，请确认是否处于打开状态！");
        return;
    }
}

/*
 * 串口查询
 */
void MainWindow::on_pushButton_Check_clicked()
{
    //    查找串口号之前对选定的串口号进行数据清空
    ui->comboBox_PortNO->clear();
    //    ui->textEdit_Receipt->clear();
    controls_SerialFind_SetEnabled(0);
    serialPort_Find();
    ui->pushButton_Send->setEnabled(0);
}

/*
 * 接收串口读取的数据
 */
void MainWindow::serialPort_ReadAvailable()
{
    QByteArray qre;
    if (serial.bytesAvailable()) {
        //    串口收到的数据并非连续的，需要进行缓存再进行解析
        //    从串口接收缓冲区中读取所有数据

//        qDebug() << "打开设备进行读写" << serial.open(QIODevice::ReadWrite);
        qre = serial.readAll();
        buffer.append(qre);
    }
    else
        return;
    //    if (buffer.contains("\n")) {
    if (1) {
        qDebug() << "已接收：" << buffer;
        serialPort_Record(buffer, global_serials.serialDataCountRx);
        buffer.clear();
    }
    else
    {
        qDebug() << "部分已接收：" << buffer;
    }

}


/*
 * 打开串口
 */
void MainWindow::on_pushButton_Open_clicked()
{
    if(ui->pushButton_Open->text() == QString("打开串口"))
    {
        //                serial = new QSerialPort(this);
        controls_Info();
        //        打开串口输出输入流设备(进行读写)出现异常时
        if(!serial.open(QIODevice :: ReadWrite))
        {
            //            消息窗口弹窗提示
            QMessageBox :: critical(NULL, "警告", "无法打开" + ui->comboBox_PortNO->currentText() + "当前串口！");
            global_serials.isSerialOpen = false;
            controls_SerialOpen_SetEnabled(1);
            qDebug() << "test >>> pushButton_Open无法打开串口" ;
        }
        else{
            serial.open(QIODevice::ReadWrite);
            global_serials.isSerialOpen = true;
            controls_SerialOpen_SetEnabled(0);
            qDebug() << "test >>> pushButton_Open打开串口";
            ui->textEdit_Receipt->append(">> 串口打开成功，请输入数据进行调试");
        }
    }
    else
    {
        //        关闭串口号
        serial.close();
        qDebug("test >>> pushButton_Close关闭串口");
        global_serials.isSerialOpen = false;
        //        删除串口对象
        //        serial.deleteLater();
        //        serial.reset();
        controls_SerialOpen_SetEnabled(1);
        ui->textEdit_Receipt->append(">> 当前串口已关闭");
    }
}

//菜单栏Home回调槽函数
void MainWindow::menuBar_Action(QAction* a)
{
    if(a->text() == "Home"){
        MainWindow().show();
        qDebug("返回主页");
    }else if(a->text() == "Exit"){
        this->close();
        qDebug("退出程序");
    }

}

//发送文本框信号槽
void MainWindow::textEdit_Changed()
{
    connect(ui->textEdit_Receipt, &QTextEdit::textChanged, this, [=](){
        //        获取发送文本框字符
        QString sendText = ui->textEdit_Send->document()->toPlainText();
        if (sendText.isEmpty()) {
            return;
        }
        //         勾选hex发送进行非法判断
        if (ui->radioButton_Hex->isChecked()) {

            char ch;
            bool flag = false;
            uint32_t i, len;
            //        替换无用符号
            sendText = sendText.replace(' ',"")
                    .replace(',',"")
                    .replace('\r',"")
                    .replace('\n',"")
                    .replace('\t',"")
                    .replace("0x","")
                    .replace("0X","");
            //        判断数据合法性
            for (i = 0, len = sendText.length();i < len;i++) {
                ch = sendText.at(i).toLatin1();
                if (ch >= '0' && ch <= '9') {
                    flag = false;
                }else if (ch >= 'a' && ch <= 'f') {
                    flag = false;
                }else if (ch >= 'A' && ch <= 'F') {
                    flag = false;
                }else {
                    flag = true;
                }
            }
            if(flag){
                QMessageBox::warning(this,"输入警告","输入内容包含非法16进制字符");
                return;
            }
        }
        global_serials.textEdit_SendText = sendText;
    });
}

/*
 * 调整滚动滑轮
*/
void MainWindow::on_textEdit_Receipt_textChanged()
{
    ui->textEdit_Receipt->moveCursor(QTextCursor::End);
}
