#include "mainwindow.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <QTime>
#include <QDebug>

/*
 * 数据发送
*/
void MainWindow::serialPort_Write(QByteArray serialPort_TextSend,int countTX)
{
    QString bufferStr;

    //    ui->checkBox_Ascii->click();
    if (serialPort_TextSend.isEmpty() != true) {
        //            加回车换行
        if (ui->checkBox_Enter->isChecked()) {
            serialPort_TextSend.append("\n");
        }

        //        hex发送
        //        if (ui->radioButton_Hex->isChecked()) {
        //            //            1.获取hex格式的数据
        //            bufferData = serialPort_TextSend.fromHex(serialPort_TextSend);
        //            //            2.发送hex数据
        //            serial.write(bufferData);
        //            qDebug() << "已发送：" <<  QString::fromUtf8(serialPort_TextSend);
        //            //            3.判断是否显示时间戳    TX表示发送端
        //            if (ui->checkBox_TimeDisp->isChecked()) {
        //                bufferStr = bufferData.toHex(' ').trimmed().toUpper();
        //                ui->textEdit_Receipt->setTextColor(QColor("green"));
        //                ui->textEdit_Receipt->append(QString("[%1]TX -> ").arg(QTime::currentTime().toString("HH:mm:ss:zzz")));
        //                ui->textEdit_Receipt->setTextColor(QColor("black"));
        //                ui->textEdit_Receipt->insertPlainText(bufferStr);
        //            }
        //        }

        if (ui->checkBox_TimeDisp->isChecked()) {
            ui->textEdit_Receipt->setTextColor(QColor("blue"));
            ui->textEdit_Receipt->insertPlainText(QString("\n[%1]TX -> ").arg(QTime::currentTime().toString("HH:mm:ss:zzz")));
            ui->textEdit_Receipt->setTextColor(QColor("black"));
            ui->textEdit_Receipt->insertPlainText(QString(serialPort_TextSend));
        }

        //        ascii发送
        if (ui->checkBox_Ascii->isChecked())  {
            serial.write(QString(serialPort_TextSend).toUtf8());
        }else {
            serial.write(serialPort_TextSend);
        }
        qDebug() << "已发送：" <<  serialPort_TextSend;
        //        移动光标至最后
        ui->textEdit_Receipt->moveCursor(QTextCursor :: End);
        //        发送实现接收数据总数更新
        countTX += serialPort_TextSend.length();
        ui->label_TotalSendTX->setText(QString::number(countTX));
        //        发送开始时间 毫秒
        //        global_serials.serialTx = QDateTime::currentDateTime().toMSecsSinceEpoch();
        //        秒
        global_serials.serialTx = QDateTime::currentDateTime().toTime_t();
    }
    else {
        serial.write(NULL);
        if (!serial.bytesAvailable())
        {
            QMessageBox::critical(this,"串口警告","串口不存在可用的字节数据！",QMessageBox::Ok);
        }
        else{
            QMessageBox::critical(this,"发送警告","发送数据失败",QMessageBox::Ok);
        }
        ui->pushButton_Send->setEnabled(true);
        ui->pushButton_Send->setText("发送");
        return;
    }
}
