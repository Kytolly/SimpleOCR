#ifndef QIMAGELABEL_H
#define QIMAGELABEL_H


#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>
#include <QFileInfo>
#include <QDebug>
#include <QFileDialog>

class QImageLabel : public QLabel {
    Q_OBJECT

public:
    QImageLabel(QWidget *parent = nullptr) : QLabel(parent) {
        setAcceptDrops(true);
    }

    void show_iamge(const QString & filePath)
    {
        QFileInfo fileInfo(filePath);
        QString extension = fileInfo.suffix().toLower();
        if (extension == "png" || extension == "jpg" || extension == "jpeg" || extension == "bmp") {
            QPixmap pixmap(filePath);
             setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
             emit sig_sendImagePath(filePath);
        }
    }

signals:
    void sig_sendImagePath(QString imagePath);

protected:


    void dragEnterEvent(QDragEnterEvent *event) override {
        if (event->mimeData()->hasUrls())
        {
                    event->acceptProposedAction();
         }
    }

    void dropEvent(QDropEvent *event) override {
        qDebug() << "filePath";
        if (event->mimeData()->hasUrls()) {
              QList<QUrl> urls = event->mimeData()->urls();
                   if (!urls.isEmpty()) {

                       QString filePath = urls.first().toLocalFile();
                       QFileInfo fileInfo(filePath);
                       QString extension = fileInfo.suffix().toLower();


                       if (extension == "png" || extension == "jpg" || extension == "jpeg" || extension == "bmp") {
                           QPixmap pixmap(filePath);
                            setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                            emit sig_sendImagePath(filePath);
                       }
            }
        }
    }
    void mousePressEvent(QMouseEvent *event) override {
          if (event->button() == Qt::LeftButton  ) {
              QFileDialog dialog(this);
              dialog.setWindowTitle("Open Image");
              dialog.setFileMode(QFileDialog::ExistingFile);
              dialog.setNameFilter(tr("Images (*.png *.bmp *.jpg)"));

              if (dialog.exec()) {
                  QString filePath = dialog.selectedFiles().at(0);

                  QPixmap pixmap(filePath);
                    setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                  emit sig_sendImagePath(filePath);

              }
          }
          QLabel::mousePressEvent(event);
      }
};

#endif // QIMAGELABEL_H
