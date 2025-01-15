#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_init_service();
    void onResultReady(const QString & result);
    void on_ocr_image(const QString & imagepath);


    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

private:
    void showImage(QString path);
    Ui::MainWindow *ui;
    TirP::Worker *worker = 0;
    QString filePath;
    QString jsonResult;
};
#endif // MAINWINDOW_H
