#include "mainwindow.h"
#include <ui_mainwindow.h>
#include <QDebug>

void MainWindow :: application_UISettings(void)
{
    //    控制控件数据显示方式
    //    if (ui->radioButton_HexDisp->isChecked()) {
    //        ui->radioButton_AsciiDisp->
    //    }
    //    if (ui->radioButton_AsciiDisp->isChecked()) {
    //        ui->radioButton_HexDisp->setEnabled(false);
    //    }

    //    发送按键设置为无法启动
    ui->pushButton_Send->setEnabled(false);
    ui->comboBox_PortNO->setCurrentIndex(3);
    //    波特率默认选择：57600
    ui->comboBox_BaudRate->setCurrentIndex(11);
    //    数据位默认：8
    ui->comboBox_DataBits->setCurrentIndex(3);

    //    菜单栏背景色
    ui->menubar->setStyleSheet("background-color:rgb(64, 65, 66)");
    //    ui->menubar->setAutoFillBackground(true);
    //    设置只读文本框
    ui->textEdit_Receipt->setReadOnly(true);

    //    默认ASCII显示
    ui->radioButton_AsciiDisp->click();
    ui->checkBox_Ascii->click();
}

/*
 * 配置串口信息
*/
void MainWindow :: controls_Info()
{
    //        设置当前索引选定串口号:选择前4位
    serial.setPortName((ui->comboBox_PortNO->currentText()).left(4));
    //        设置当前索引选定波特率
    serial.setBaudRate(ui->comboBox_BaudRate->currentText().toInt());
    //        设置当前索引选定数据位：8位
    switch(ui->comboBox_DataBits->currentIndex())
    {
    case 0: serial.setDataBits(QSerialPort :: Data5); break;
    case 1: serial.setDataBits(QSerialPort :: Data6); break;
    case 2: serial.setDataBits(QSerialPort :: Data7); break;
    case 3: serial.setDataBits(QSerialPort :: Data8);
        qDebug() << "//" << serial.dataBits();
        break;
    default: serial.setDataBits(QSerialPort :: UnknownDataBits); break;
    }
    //        设置当前奇偶校验位：none
    switch(ui->comboBox_ParityBit->currentIndex())
    {
    case 0: serial.setParity(QSerialPort :: NoParity); break;
    case 1: serial.setParity(QSerialPort :: EvenParity); break;
    case 2: serial.setParity(QSerialPort :: OddParity); break;
    case 3: serial.setParity(QSerialPort :: SpaceParity); break;
    case 4: serial.setParity(QSerialPort :: MarkParity); break;
    default: serial.setParity(QSerialPort :: UnknownParity); break;
    }
    //        设置当前索引选定对应停止位
    switch(ui->comboBox_StopBit->currentIndex())
    {
    case 0: serial.setStopBits(QSerialPort::OneStop); break;
    case 1: serial.setStopBits(QSerialPort ::TwoStop); break;
        //        一个半拍停止位，case只限定整形
    case 2: serial.setStopBits(QSerialPort :: OneAndHalfStop); break;
    default: break;
    }
    //        设置无数据流控制：none
    serial.setFlowControl(QSerialPort :: NoFlowControl);
}

/*
 * 打开串口设置使能
*/
void MainWindow :: controls_SerialOpen_SetEnabled(bool TFbool)
{
    QString open_close = TFbool ? "打开串口" : "关闭串口";
    //        下拉控件、检测串口失能，不可选择（串口已经打开）
    ui->comboBox_PortNO->setEnabled(TFbool);
    ui->comboBox_BaudRate->setEnabled(TFbool);
    ui->comboBox_DataBits->setEnabled(TFbool);
    ui->comboBox_ParityBit->setEnabled(TFbool);
    ui->comboBox_StopBit->setEnabled(TFbool);
    //        检查串口失能
    ui->pushButton_Check->setEnabled(TFbool );
    //        更改打开串口按钮提示，使可进行串口流关闭
    ui->pushButton_Open->setText(open_close);

    controls_SerialFind_SetEnabled(!TFbool);
}

/*
 * 检测串口设置使能
*/
void MainWindow::controls_SerialFind_SetEnabled(bool TFbool)
{

    ui->checkBox_Ascii->setEnabled(TFbool);
    ui->checkBox_Enter->setEnabled(TFbool);
    //    ui->radioButton_Hex->setEnabled(TFbool);
    ui->checkBox_TimeDisp->setEnabled(TFbool);
    ui->radioButton_HexDisp->setEnabled(TFbool);
    ui->radioButton_AsciiDisp->setEnabled(TFbool);
    //        发送按键使能
    ui->pushButton_Send->setEnabled(TFbool);
    ui->pushButton_Clear->setEnabled(TFbool);

}
