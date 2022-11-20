#include "mainwindow.h"

#include <QMessageBox>
#include <ui_mainwindow.h>
#include <iostream>
#include <QDebug>
#include <QTime>
#include "sleepMS.h"

/*
 * 串口查找和自适应宽度
 */
void MainWindow :: serialPort_Find()
{
    ui->radioButton_HexDisp->setFocus();
    controls_SerialFind_SetEnabled(0);
    ui->textEdit_Receipt->append("查询可用串口中......");
    sleep_MS(100);
    QString QStr_Receipt;
    QStringList QStrList_SerialPort_Name;
    int i = 0,j,l = 0;
    //    通过QSerialPortInfo类进行遍历，查找可用串口设备
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        l ++;
        if (info.isBusy()) {
            QMessageBox::StandardButton btn;
            btn = QMessageBox::question(this, "可用串口提示", (QStr_Receipt = info.portName() + ":" + info.description()) + "被占用！寻找下一串口？", QMessageBox::Yes|QMessageBox::No);
            if (btn == QMessageBox::Yes) {
                continue;
            }else {
                QMessageBox :: information(this,"搜索提示","结束可用串口搜索！",QMessageBox::Ok);
                break;
            }
        }
        QStrList_SerialPort_Name << (QStr_Receipt = info.portName() + ":" + info.description());
        //        对 串口号 ： 串口名称 保存到接收窗口
        ui->textEdit_Receipt->append(QString::number(i++) + "、" + QStr_Receipt);
        //        存在一个可用串口，则更改发送按钮的可用性
        ui->pushButton_Send->setEnabled(QStr_Receipt > 0 ? j + 1 : j = 0);
    }
    ui->textEdit_Receipt->append("\n");
    if (j > 0) {
        //        将可用的串口信息添加到串口号下拉框中做选择
        ui->comboBox_PortNO->addItems(QStrList_SerialPort_Name);
        ui->comboBox_PortNO->adjustItemWidth();
        qDebug() << "test >>> adjustItemWidth()自适应下拉宽度";
    }
    else{
        ui->textEdit_Receipt->clear();
        QMessageBox :: critical(NULL,"信息提示","获取串口信息失败，未检测到可用串口设备");
        return;
    }
}

/*
 * 串口转换进制读取和总数记录
 */
void MainWindow :: serialPort_Record(QByteArray serialPort_Buffer,int countRX)
{

    QString format_Buffer;
    //    qint64 startSec = QDateTime::currentDateTime().toMSecsSinceEpoch(), endSec;
    //    while((global_serials.serialRX = QDateTime::currentDateTime().toMSecsSinceEpoch() - global_serials.serialTx) < 500)

    //获取时间秒数
    //            endSec = QDateTime::currentDateTime().toTime_t();
    //获取时间毫秒数
    //    endSec = QDateTime::currentDateTime().toMSecsSinceEpoch();

    //    数据存在时
    if (serialPort_Buffer.isEmpty() != true)
    {
        ui->textEdit_Receipt->insertPlainText("\n");
        //        时间戳显示
        if (ui->checkBox_TimeDisp->isChecked())
        {
            //            QString()字符定位：%1--第一个arg()   RX表示接收端
            ui->textEdit_Receipt->setTextColor(QColor(Qt::black));
            ui->textEdit_Receipt->insertPlainText(QString("[%1]RX -> ").arg(QTime::currentTime().toString("HH:mm:ss:zzz")));
        }

        //        Hex十六进制显示
        if (ui->radioButton_HexDisp->isChecked())
        {
            format_Buffer = serialPort_Buffer.toHex(' ').trimmed().toUpper();
            ui->textEdit_Receipt->setTextColor(QColor(Qt::red));
            //            ui->textEdit_Receipt->insertPlainText("\n");
        }
        //        ASCII显示
        else if (ui->radioButton_AsciiDisp->isChecked())
        {
            format_Buffer = QString(serialPort_Buffer);
            //            qDebug() << "\\" << format_Buffer;
            ui->textEdit_Receipt->setTextColor(QColor(Qt::darkRed));
            //            ui->textEdit_Receipt->insertPlainText("\n");
        }
        //        ui->textEdit_Receipt->append(format_Buffer);
        ui->textEdit_Receipt->insertPlainText(format_Buffer);
        ui->textEdit_Receipt->insertPlainText("\n");

        //        //    从界面中读取以前收到的数据
        //        QString receipt = ui->textEdit_Receipt->toPlainText();
        //        receipt += QString(format_Buffer);
        //        //    清空以前的显示
        //        ui->textEdit_Receipt->clear();
        //        //    重新显示，后置添加
        //        ui->textEdit_Receipt->insertPlainText(receipt);

        //            更新接收总数
        countRX += serialPort_Buffer.length();
        ui->label_TotalReceiptRX->setText(QString::number(countRX));
    }
    else
    {
        QMessageBox :: warning(NULL,"串口提示","串口数据为空！");
    }
}
