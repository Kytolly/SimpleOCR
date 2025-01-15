#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <qmessagebox>
#include <QClipboard>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    //connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_init_service);

    on_init_service();
    connect(ui->label,&QImageLabel::sig_sendImagePath, this , &MainWindow::on_ocr_image);


}

MainWindow::~MainWindow()
{
    worker->stop();
    worker->wait();
    delete ui;
}

void MainWindow::on_init_service(){

    if(worker == nullptr )
    {
        worker = new TirP::Worker;
        worker->start();
        connect(worker, &TirP::Worker::resultReady, this, &MainWindow::onResultReady);
        connect(worker, &TirP::Worker::error, this, [this](const QString &err){
        ui->textBrowser->setPlainText("Error: "+ err);
        });
        ui->textBrowser->setPlainText("server start");
    }

}

void MainWindow::onResultReady(const QString& result){

    jsonResult = result;

    qDebug() << jsonResult;
    QJsonDocument doc = QJsonDocument::fromJson(jsonResult.toUtf8());


        if (!doc.isObject()) {
            ui->textBrowser->setPlainText("JSON 解析失败");
            return ;
        }


        QJsonObject jsonObj = doc.object();
        bool success = jsonObj["statusOK"].isBool();
        qDebug() << success;
        if(success)
        {
            QJsonArray js = jsonObj["records"].toArray();
            //qDebug() << js.size();

            if(js.size())
            {
                for(auto  & jsonvalue : js) {
                    QJsonObject o = jsonvalue.toObject();
                    QString res =  o["result"].toString();
                    ui->textBrowser->setPlainText(res + '\r\n');
                }
                return ;
            }
        }
        ui->textBrowser->setPlainText("识别失败");
}

void MainWindow::showImage(QString path)
{
    QPixmap pixmap(path);

    ui->label->setPixmap(pixmap);

    ui->label->resize(pixmap.width(), pixmap.height());
}



void MainWindow::on_ocr_image(const QString & imagepath)
{

    if(worker)
    {  
        ui->textBrowser->setPlainText("正在识别");
        QString sendText = QString("{\"path\":\"%1\", \"statusOK\":true}").arg(imagepath);
        worker->sendMessage(sendText);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
        QString fileName = QFileDialog::getSaveFileName(this, tr("Export Text"), "", tr("Text Files (*.txt)"));
        if (fileName.isEmpty()) {
            // 用户取消了操作
            return;
        }

        QFile file(fileName);
           if (!file.open(QIODevice::WriteOnly)) {
               QMessageBox::critical(this, tr("Error"), tr("Cannot open file for writing."));
               return;
           }

           QTextStream out(&file);
           out << jsonResult;
           file.close();

           QMessageBox::information(this, tr("提示"), tr("保存成功"));
}


void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Text"), "", tr("Text Files (*.txt)"));
         if (fileName.isEmpty()) {
             return;
         }

         QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Cannot open file for writing."));
                return;
            }

            QTextStream out(&file);
            out << ui->textBrowser->toPlainText();
            file.close();

         QMessageBox::information(this, tr("提示"), tr("保存成功"));
}


void MainWindow::on_pushButton_5_clicked()
{
    QString text = ui->textBrowser->toPlainText();
    if(text.size())
    {
        QApplication::clipboard()->setText(text);
    }
}

