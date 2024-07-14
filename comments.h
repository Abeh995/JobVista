#ifndef COMMENTS_H
#define COMMENTS_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include "QDebug"
#include "QSqlError"
#include <QFileDialog>
#include <QBuffer>
#include <QWidget>
#include<QMenu>
#include <QGroupBox>
#include <QGridLayout>
#include <QWidget>


namespace Ui {
class comments;
}

class comments : public QWidget
{
    Q_OBJECT

public:
    explicit comments(QWidget *parent = nullptr);
    QWidget* scrollWidget;
    QGridLayout* scrollLayout;
    ~comments();

private slots:
    void on_media_pushButton_clicked();

    void on_send_pushButton_clicked();

public slots:
    QString getTime();
private:
    QLabel *imageLabel = nullptr;
    QLabel *gifLabel = nullptr;
    QMediaPlayer *mediaPlayer = nullptr;
    QVideoWidget *videoWidget = nullptr;
    QMediaPlaylist *playlist = nullptr;
    Ui::comments *ui;
};

#endif // COMMENTS_H
