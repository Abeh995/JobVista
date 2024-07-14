#ifndef CREATEPOST_H
#define CREATEPOST_H

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


namespace Ui {
class createPost;
}

class createPost : public QWidget
{
    Q_OBJECT

public:
    explicit createPost(QWidget *parent = nullptr);
    ~createPost();

private slots:
    void on_media_pushButton_clicked();

    void on_emoji_pushButton_clicked();

    void showEmojiMenu();

    void insertEmoji();

    void on_post_pushButton_clicked();

    void on_schedule_pushButton_clicked();

private:
    QLabel *imageLabel = nullptr;
        QLabel *gifLabel = nullptr;
        QMediaPlayer *mediaPlayer = nullptr;
        QVideoWidget *videoWidget = nullptr;
        QMediaPlaylist *playlist = nullptr;
        QMenu *emojiMenu;
    Ui::createPost *ui;

protected:
    void closeEvent(QCloseEvent *event) override;

};

#endif // CREATEPOST_H
