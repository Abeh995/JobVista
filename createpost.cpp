#include "createpost.h"
#include "ui_createpost.h"
#include"basicclasses.h"
#include"splash.h"

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
#include <QMainWindow>
#include <QMediaPlaylist>
#include<QDateTime>

#include <QSqlDatabase>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

QString filePath2,filePathAme;
QByteArray mediaData;
QString mediaType;
QString sw2;


QHBoxLayout *media_groupBoxLayout = new QHBoxLayout;
int sw=0;

createPost::createPost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createPost)
{
    ui->setupUi(this);

    setWindowTitle("Create Post");
    ui->media_groupBox->hide();


//    QSqlQuery q;
//    q.prepare("SELECT media FROM Posts WHERE id = :id");
//    q.bindValue(":id", ID);
//    if(q.exec()){
//        if(q.next()){
//            QByteArray imageData = q.value(0).toByteArray();
//            QPixmap pixmap;
//            pixmap.loadFromData(imageData);
//                    // Save pixmap to a file
//                    filePath2 = QDir::homePath() + "/profilePhoto.png";
//                    if(pixmap.save(filePath2)){
//                        // Set the image on the button using styleSheet
//                       // ui->profilePhoto_label->setStyleSheet(QString("QPushButton {border-image: url(%1); border-radius:55px;}").arg(imagePath));

//                        imageLabel->setMinimumSize(500, 300);
//                        ui->profilePhoto_label->setScaledContents(true);
//                        ui->profilePhoto_label->setStyleSheet(QString("border-image: url(%1);").arg(filePath2));

//                    }
//                    else{
//                        // Handle error if saving failed
//                        qDebug() << "Error saving image file";
//                        q.lastError().text();
//                    }
//                }
//            }
//            else{
//                // Handle the error
//                qDebug() << "Error retrieving profile photo:" << q.lastError().text();
//            }



}

createPost::~createPost()
{
    delete ui;
}

void createPost::on_media_pushButton_clicked()
{
     filePath2 = QFileDialog::getOpenFileName(this, tr("Select media"), QDir::homePath(), tr("Media Files (*.png *.jpg *.jpeg *.mp4 *.GIF *.mkv)"));
        if (!filePath2.isEmpty()) {
            filePathAme=filePath2;
            // Save the media to the database
            QFile file(filePath2);
            if (file.open(QIODevice::ReadOnly)) {
                 mediaData = file.readAll();

            } else {
                // Handle the error if the file can't be opened
                qDebug() << "Error opening image file:" << file.errorString();
            }

            // Determine the media format
            QFileInfo fileInfo(filePath2);
            QString suffix = fileInfo.suffix().toLower();

            // Clear previous media
            if (imageLabel) {
                delete imageLabel;
                imageLabel = nullptr;
            }
            if (gifLabel) {
                delete gifLabel;
                gifLabel = nullptr;
            }
            if (mediaPlayer) {
                delete mediaPlayer;
                mediaPlayer = nullptr;
            }
            if (videoWidget) {
                delete videoWidget;
                videoWidget = nullptr;
            }

            if (suffix == "png" || suffix == "jpg" || suffix == "jpeg") {
                // Display image
                ui->media_groupBox->show();
                mediaType = "image";
                imageLabel = new QLabel(this);
                imageLabel->setMinimumSize(500, 300);
                imageLabel->setScaledContents(true);
                imageLabel->setStyleSheet(QString("border-image: url(%1);").arg(filePath2));

                media_groupBoxLayout->addWidget(imageLabel);
                ui->media_groupBox->setLayout(media_groupBoxLayout);

            } else if (suffix == "gif") {
                // Display GIF
                ui->media_groupBox->show();
                mediaType = "gif";

                gifLabel = new QLabel(this);
                QMovie *movie = new QMovie(filePath2);
                gifLabel->setMovie(movie);
                gifLabel->setScaledContents(true);
                gifLabel->show();
                movie->start();
                media_groupBoxLayout->addWidget(gifLabel);
                ui->media_groupBox->setLayout(media_groupBoxLayout);

                }

                else if (suffix == "mp4" || suffix == "mkv") {
                // Display video

                ui->media_groupBox->show();
                mediaType = "video";

                playlist = new QMediaPlaylist(this);
                playlist->addMedia(QUrl::fromLocalFile(filePath2));
                playlist->setPlaybackMode(QMediaPlaylist::Loop);

                mediaPlayer = new QMediaPlayer(this);
                videoWidget = new QVideoWidget(this);
                mediaPlayer->setVideoOutput(videoWidget);
                mediaPlayer->setPlaylist(playlist);

                connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
                    if (status == QMediaPlayer::InvalidMedia) {
                        qDebug() << "Error loading media:" << mediaPlayer->errorString();
                    } else if (status == QMediaPlayer::LoadedMedia) {
                        qDebug() << "Media loaded successfully";
                    }
                });

                connect(mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, [=](QMediaPlayer::Error error) {
                    qDebug() << "Media player error:" << mediaPlayer->errorString();
                });

                QHBoxLayout* currentLayout = new QHBoxLayout;
                videoWidget->setMinimumHeight(400);
                videoWidget->setMinimumWidth(800);
                ui->media_groupBox->setMinimumHeight(450);

                currentLayout->addWidget(videoWidget);
                videoWidget->show();
                mediaPlayer->play();
                ui->media_groupBox->setLayout(currentLayout);

                delete currentLayout;
                //currentLayout = media_groupBoxLayout;

            }
            else {
                qDebug() << "Unsupported media format:" << suffix;
            }
            sw2 =suffix;
            file.close();
        }

}



void createPost::on_emoji_pushButton_clicked()
{
    // Set up the emoji menu
        QStringList emojis = {"😀", "😁", "😂", "🤣", "😃", "😄", "😅", "😆", "😉", "😊"};

        for (const QString &emoji : emojis) {
            QAction *emojiAction = new QAction(emoji, this);
            connect(emojiAction, &QAction::triggered, this, &createPost::insertEmoji);
            emojiMenu->addAction(emojiAction);
        }
}


void createPost::showEmojiMenu()
{
    emojiMenu->exec(QCursor::pos());
}

void createPost::insertEmoji()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        ui->postText_textEdit->insertPlainText(action->text());
    }
}

void createPost::on_post_pushButton_clicked()
{

    QString newPostId;
    QString mmd="0/0/0";
    QSqlQuery q;

    QDateTime dateTime = QDateTime::currentDateTime();

        // Extract the year, month, day, hour, minute, and second
        int year = dateTime.date().year();
        int month = dateTime.date().month();
        int day = dateTime.date().day();
        int hour = dateTime.time().hour();
        int minute = dateTime.time().minute();
        int second = dateTime.time().second();

        // Combine them into a single string
        QString timeString = QString("%1%2%3%4%5%6")
                .arg(year, 4, 10, QChar('0'))   // Year with 4 digits
                .arg(month, 2, 10, QChar('0'))  // Month with 2 digits
                .arg(day, 2, 10, QChar('0'))    // Day with 2 digits
                .arg(hour, 2, 10, QChar('0'))   // Hour with 2 digits
                .arg(minute, 2, 10, QChar('0')) // Minute with 2 digits
                .arg(second, 2, 10, QChar('0'));// Second with 2 digits

    q.exec("SELECT postCounter FROM Users WHERE id = '"+ID+"'");
    if(q.first()){

        newPostId=q.value(0).toString();
        int ame=newPostId.toInt();
        ame+=1;
        newPostId=QString("%1").arg(ame);
        ui->profilePhoto_label->setText(newPostId);
        ui->name_label->setText(ID);
        q.exec("UPDATE Users SET postCounter = '"+QString("%1").arg(ame)+"' WHERE id ='"+ID+"'");
    }
    else{
        qDebug()<< "MMD!!!!!!!!!!!!!!!";
    }

    q.exec("INSERT INTO Posts (id, postId, tag ) VALUES ('"+ID+"','"+newPostId+"','"+ui->tag_comboBox->currentText()+"' )");
    q.exec("UPDATE Posts SET text = '" + ui->postText_textEdit->toPlainText() + "' WHERE id = '" + ID + "' AND postId = '" + newPostId + "'");
    QFile file(filePathAme);
    if (file.open(QIODevice::ReadOnly)) {
        QSqlQuery ame;
        QByteArray mediaDataAme=file.readAll();
        ame.prepare("UPDATE Posts SET media  = :photo WHERE id= :id AND postId = :newPostId");
        ame.bindValue(":photo", mediaDataAme);
        ame.bindValue(":id", ID);
        ame.bindValue(":newPostId", newPostId);
        if (ame.exec()) {
            qDebug() << "Yay!";
        } else {
            qDebug() << ame.executedQuery();
            qDebug() << ame.lastError();
        }

        qDebug()<< "ame have problem" << ame.lastError();
    }
    q.exec("UPDATE Posts SET mediaType  ='"+mediaType+"' WHERE id= '"+ID+"' AND postId = '"+newPostId+"'");
    q.exec("UPDATE Posts SET likersId  ='"+QString("")+"' WHERE id='"+ID+"' AND postId = '"+newPostId+"'");
    q.exec("UPDATE Posts SET comments  ='"+QString("")+"' WHERE id='"+ID+"' AND postId = '"+newPostId+"'");
    q.exec("UPDATE Posts SET LCR_counter  ='"+mmd+"' WHERE id='"+ID+"' AND postId = '"+newPostId+"'");
    q.exec("UPDATE Posts SET rePostId  ='"+QString("empty")+"' WHERE id='"+ID+"' AND postId = '"+newPostId+"'");
    q.exec("UPDATE Posts SET time  ='"+timeString+"' WHERE id='"+ID+"' AND postId = '"+newPostId+"'");
//    qint64 timestamp = QDateTime::currentMSecsSinceEpoch() / 1000;
//    QString qstr=QString("UPDATE Posts SET time  = %1 WHERE id= %2 AND postId = %3 ").arg(timestamp).arg(ID).arg(newPostId);
//    if(!q.exec(qstr)){
//        qWarning()<<" faild to update post"<<q.lastError();
//    }
//    else{
//        qDebug()<<"succsess";
//    }

//    ui->profilePhoto_label->setText(filePathAme);
//    ui->name_label->setText(filePath2);

//    mediaPlayer->stop();
    if(sw2 == "mp4" || sw2 == "mkv"){
        mediaPlayer->stop();
    }
//    this->close();
}

void createPost::closeEvent(QCloseEvent *event)
{
    if(sw2 == "mp4" || sw2 == "mkv"){
        mediaPlayer->stop();
    }
    QString imagePath = QDir::homePath() + "/profilePhoto.png";
    if(QFile::exists(imagePath)){
        if(!QFile::remove(imagePath)){
            // Handle error if deletion failed
            qDebug() << "Error deleting image file";
        }
    }
    // Call the base class implementation of closeEvent
    QWidget::closeEvent(event);
}

