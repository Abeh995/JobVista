#include "comments.h"
#include "ui_comments.h"
#include "splash.h"
#include "basicclasses.h"

#include <QDebug>
#include <QApplication>
#include <QTabWidget>
#include <QTabBar>
#include <QStyleOptionTab>
#include <QToolBar>
#include <QMainWindow>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include<QFileDialog>
#include<QBuffer>
#include <QImage>
#include <QPainter>
#include <QMediaPlaylist>

#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QByteArray>

QString suffix;
QString filePath3,filePathKhale;
QByteArray mediaData2;
QString mediaType2;
QHBoxLayout *fileDialogue_groupBoxLayout = new QHBoxLayout;


//QString sw3;
comments::comments(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comments)
{
    ui->setupUi(this);

    setWindowTitle("Comments");
    scrollWidget = new QWidget;
    scrollLayout = new QGridLayout(scrollWidget);
    QVector<Comment> comments;
    scrollWidget->setLayout(scrollLayout);
    ui->scrollArea->setWidget(scrollWidget);

    QGroupBox* caption_groupBox = new QGroupBox;
    caption_groupBox->setMinimumHeight(500);
    caption_groupBox->setMaximumSize(500, 16777215);
    QVBoxLayout* caption_groupBoxLayout = new QVBoxLayout;
    caption_groupBox->setLayout(caption_groupBoxLayout);
    caption_groupBox->setStyleSheet("border-radius:5px");

    QGroupBox* captionInfo_groupBox = new QGroupBox/*(QString("prof-%1" ).arg(i))*/;
    captionInfo_groupBox->setMaximumHeight(70);
    QHBoxLayout* captionInfo_groupboxLayout = new QHBoxLayout;
    captionInfo_groupBox->setLayout(captionInfo_groupboxLayout);
    captionInfo_groupBox->setStyleSheet("border-radius:5px;");

    QLabel * captionProfile_label = new QLabel;
    captionProfile_label->setMinimumSize(50, 50);
    captionProfile_label->setMaximumSize(50, 50);
    captionProfile_label->setScaledContents(true);
    captionInfo_groupboxLayout->addWidget(captionProfile_label);

    QByteArray captionProf;
    QSqlQuery q3;
    q3.prepare("SELECT profilePhoto FROM Users WHERE id = :id");
    q3.bindValue(":id", postSenderID);
    if(q3.exec()){
        if(q3.next()){
            QByteArray prof=q3.value("profilePhoto").toByteArray();
            if(!prof.isEmpty()){

                captionProf=prof;
            }
            else{
                qDebug()<< "ame is empty"<<q3.lastError();
            }

        }
        else{
            qDebug()<< "ame is dead be mola "<< q3.lastError();
        }
    } else{
        qDebug()<< "error loading profile for id: "<< postSenderID<<" ERROR: "<<q3.lastError();
    }

    QPixmap pix;
    if (!pix.loadFromData(captionProf)) {
        qDebug() << "Error: Failed to load pixmap from profPhoto for post ID" << postSenderID;
    } else {
        QPixmap circularPixmap(50, 50);
                circularPixmap.fill(Qt::transparent);

                QPainterPath path;
                path.addEllipse(0, 0, 50, 50);

                QPainter painter(&circularPixmap);
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, pix.scaled(50, 50, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

                captionProfile_label->setPixmap(circularPixmap);
    }

    captionProfile_label->setStyleSheet("border-radius: 25px;");

    QLabel* id_label = new QLabel(QString(""));
    id_label->setText(postSenderID);
    captionInfo_groupboxLayout->addWidget(id_label);
    caption_groupBoxLayout->addWidget(captionInfo_groupBox);

    QGroupBox* captionMedia_groupBox = new QGroupBox;
    captionMedia_groupBox->setMinimumHeight(400);
    QVBoxLayout* captionMedia_groupBoxLayout = new QVBoxLayout;
    captionMedia_groupBox->setLayout(captionMedia_groupBoxLayout);
    captionMedia_groupBox->setStyleSheet("background-color: rgb(51, 167, 255);");

    QLabel* captionPostImage_label = new QLabel;
    captionPostImage_label->setMaximumSize(650, 300);
    captionPostImage_label->setScaledContents(true);
    QByteArray media;

//        QPixmap pix;


    captionPostImage_label->setStyleSheet("border-radius: 25px;");

    QSqlQuery q4;
    q4.prepare("SELECT * FROM Posts WHERE id = :id AND postId = :postid");
    q4.bindValue(":id", postSenderID);
    q4.bindValue(":postid", postID);

    if(!q4.exec()){
        qDebug() << "Error: failed to execute query -" << q4.lastError();
    }
    while(q4.next()){
        media=q4.value("media").toByteArray();
    }

    if (!pix.loadFromData(media)) {
        captionPostImage_label->hide();
        captionPostImage_label->setMaximumHeight(60);
        //qDebug() << "Error: Failed to load pixmap from media for post ID" << posts[i].id;
    } else {
                captionPostImage_label->setPixmap(pix);
    }
    captionMedia_groupBoxLayout->addWidget(captionPostImage_label);

////////////////////////////////////////////////////text does not work!
    QLabel* captionText_label = new QLabel;
    captionText_label->setWordWrap(true);
    captionText_label->setText(q4.value("text").toString());
    captionMedia_groupBoxLayout->addWidget(captionText_label);

    caption_groupBoxLayout->addWidget(captionMedia_groupBox);
    scrollLayout->addWidget(caption_groupBox);

    QGroupBox* space_groupBox = new QGroupBox;
    space_groupBox->setMinimumHeight(50);
    space_groupBox->setMaximumHeight(50);
    space_groupBox->setStyleSheet("border-radius:5px");
    scrollLayout->addWidget(space_groupBox);



    //vector of comments
    QSqlQuery q;
    q.prepare("SELECT * FROM Comments WHERE senderId = :senderid AND postId = :postid  ORDER BY time DESC");
    q.bindValue(":senderid", postSenderID);
    q.bindValue(":postid", postID);

    if(!q.exec()){
        qDebug() << "Error: failed to execute query -" << q.lastError();
    }
    while(q.next()){
        Comment comment;
        comment.id = q.value("id").toString();
        //profile photo
        QSqlQuery q2;
        q2.prepare("SELECT profilePhoto FROM Users WHERE id = :id");
        q2.bindValue(":id", comment.id);
        if(q2.exec()){
            if(q2.next()){
                QByteArray prof=q2.value("profilePhoto").toByteArray();
                if(!prof.isEmpty()){

                    comment.profilePhoto=prof;
                }
                else{
                    qDebug()<< "ame is empty"<<q2.lastError();
                }

            }
            else{
                qDebug()<< "ame is dead be mola "<< q2.lastError();
            }
        } else{
            qDebug()<< "error loading profile for id: "<< comment.id<<" ERROR: "<<q2.lastError();
        }

        comment.postId = q.value("postId").toString();
        comment.text = q.value("text").toString();

        QByteArray media=q.value("media").toByteArray();
                // Check if media is valid
        if (!media.isEmpty()) {
            comment.media = media;
         } else {
                qDebug() << "Warning: Post with ID" << comment.id << "has empty media.";
            }
                // Handling media (BLOBs)
        QString mediaType = q.value("mediaType").toString();
        comments.append(comment);

    }
    int size = comments.size();
    for(int i=0; i<size; i++){

        QGroupBox* comment_groupBox = new QGroupBox;
        comment_groupBox->setMinimumHeight(100);
        comment_groupBox->setMaximumSize(500, 16777215);
        QVBoxLayout* comment_groupBoxLayout = new QVBoxLayout;
        comment_groupBox->setLayout(comment_groupBoxLayout);
        comment_groupBox->setStyleSheet("border-radius:5px");

        QGroupBox* info_groupBox = new QGroupBox;
        info_groupBox->setMaximumHeight(70);
        QHBoxLayout* info_groupboxLayout = new QHBoxLayout;
        info_groupBox->setStyleSheet("border-radius:5px;");
        info_groupBox->setLayout(info_groupboxLayout);

        QLabel * profile_label = new QLabel;
        profile_label->setMinimumSize(50, 50);
        profile_label->setMaximumSize(50, 50);
        profile_label->setScaledContents(true);
        info_groupboxLayout->addWidget(profile_label);

        QPixmap pix;
        if (!pix.loadFromData(comments[i].profilePhoto)) {
            qDebug() << "Error: Failed to load pixmap from profPhoto for post ID" << comments[i].id;
        } else {
            QPixmap circularPixmap(50, 50);
                    circularPixmap.fill(Qt::transparent);

                    QPainterPath path;
                    path.addEllipse(0, 0, 50, 50);

                    QPainter painter(&circularPixmap);
                    painter.setClipPath(path);
                    painter.drawPixmap(0, 0, pix.scaled(50, 50, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

                    profile_label->setPixmap(circularPixmap);
        }

        profile_label->setStyleSheet("border-radius: 25px;");

        QLabel* id_label = new QLabel(QString(""));
        id_label->setText(comments[i].id);
        info_groupboxLayout->addWidget(id_label);

        QGroupBox* media_groupBox = new QGroupBox;
        QVBoxLayout* media_groupBoxLayout = new QVBoxLayout;
        media_groupBox->setStyleSheet("background-color: rgb(250, 250, 180);");
        media_groupBox->setLayout(media_groupBoxLayout);
        comment_groupBoxLayout->addWidget(info_groupBox);

        QLabel* postImage_label = new QLabel;
        postImage_label->setMaximumSize(650, 300);
        postImage_label->setScaledContents(true);

//        QPixmap pix;
        if (!pix.loadFromData(comments[i].media)) {
            postImage_label->hide();
            comment_groupBox->setMaximumHeight(250);
            media_groupBox->setMaximumHeight(60);
            qDebug() << "Error: Failed to load pixmap from media for post ID" << comments[i].id;
        } else {
                    postImage_label->setPixmap(pix);
        }

        postImage_label->setStyleSheet("border-radius: 25px;");
        media_groupBoxLayout->addWidget(postImage_label);

        QLabel* text_label = new QLabel;
        text_label->setWordWrap(true);
        text_label->setText(comments[i].text);
        media_groupBoxLayout->addWidget(text_label);

        comment_groupBoxLayout->addWidget(media_groupBox);
        scrollLayout->addWidget(comment_groupBox);
    }

    ui->media_groupBox->setLayout(fileDialogue_groupBoxLayout);
    ui->media_groupBox->setMaximumHeight(200);
    ui->media_groupBox->hide();


}

comments::~comments()
{
    delete ui;
}

void comments::on_media_pushButton_clicked()
{
    filePath3 = QFileDialog::getOpenFileName(this, tr("Select media"), QDir::homePath(), tr("Media Files (*.png *.jpg *.jpeg *.mp4 *.GIF *.mkv)"));
       if (!filePath3.isEmpty()) {
           filePathKhale=filePath3;
           // Save the media to the database
           QFile file(filePath3);
           if (file.open(QIODevice::ReadOnly)) {
                mediaData2 = file.readAll();

           } else {
               // Handle the error if the file can't be opened
               qDebug() << "Error opening image file:" << file.errorString();
           }

           // Determine the media format
           QFileInfo fileInfo(filePath3);
           suffix = fileInfo.suffix().toLower();

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
               mediaType2 = "image";
               imageLabel = new QLabel(this);
               imageLabel->setMinimumSize(500, 300);
               imageLabel->setScaledContents(true);
               imageLabel->setStyleSheet(QString("border-image: url(%1);").arg(filePath3));

               fileDialogue_groupBoxLayout->addWidget(imageLabel);
               ui->media_groupBox->setLayout(fileDialogue_groupBoxLayout);

           } else if (suffix == "gif") {
               // Display GIF
               ui->media_groupBox->show();
               mediaType2 = "gif";

               gifLabel = new QLabel(this);
               QMovie *movie = new QMovie(filePath3);
               gifLabel->setMovie(movie);
               gifLabel->setScaledContents(true);
               gifLabel->show();
               movie->start();
               fileDialogue_groupBoxLayout->addWidget(gifLabel);
               ui->media_groupBox->setLayout(fileDialogue_groupBoxLayout);

               }

               else if (suffix == "mp4" || suffix == "mkv") {
               // Display video
               ui->media_groupBox->show();
               mediaType2 = "video";

               playlist = new QMediaPlaylist(this);
               playlist->addMedia(QUrl::fromLocalFile(filePath3));
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
           file.close();
       }

}


void comments::on_send_pushButton_clicked()
{




    QSqlQuery q, q2;
    QStringList lcr;
    q2.prepare("SELECT LCR_counter FROM Posts WHERE id = :id AND postId = :postid");
    q2.bindValue(":id", postSenderID);
    q2.bindValue(":postid", postID);

    if(!q2.exec()) {
        qDebug() << "Error executing SELECT query:" << q2.lastError().text();
        return;
    }

    if(q2.next()) {
        lcr = q2.value(0).toString().split('/');
        qDebug() << "AME 1 : " << lcr[0];
        qDebug() << "AME 2 : " << lcr[1];
        qDebug() << "AME 3 : " << lcr[2];
        QString newLCR=lcr[0]+'/'+QString::number(lcr[1].toInt()+1)+'/'+lcr[2];
        q2.exec("UPDATE Posts SET LCR_counter = '"+newLCR+"' WHERE id = '"+postSenderID+"' AND postId = '"+postID+"' ");
    } else {
        qDebug() << "No results found";
        return;
    }
    int newCommentId=lcr[1].toInt();
    newCommentId++;
    qDebug() << newCommentId;

    // Prepare the insert query
    q.prepare("INSERT INTO Comments (id, senderId, postId, commentId, text, time) VALUES (:id, :senderId, :postId, :commentId, :text, :time)");
    q.bindValue(":id", ID); // Assuming ID is defined somewhere
    q.bindValue(":senderId", postSenderID); // Assuming postSenderID is defined somewhere
    q.bindValue(":postId", postID); // Assuming postID is defined somewhere
    q.bindValue(":text", ui->comment_textEdit->toPlainText());
    q.bindValue(":commentId", QString::number(newCommentId));
    q.bindValue(":time", getTime());

    if(!q.exec()) {
        qDebug() << "Error executing INSERT query:" << q.lastError().text();
    } else {
        qDebug() << "Insert successful"<<getTime();
    }
        QFile file(filePathKhale);
        if (file.open(QIODevice::ReadOnly)) {
            QSqlQuery ame;
            QByteArray mediaDataAme=file.readAll();
            ame.prepare("UPDATE Comments SET media = :media, mediaType = :mediatype WHERE id = :id AND postId = :postid AND senderId = :senderid AND commentId = :commentid");
                    ame.bindValue(":media", mediaDataAme);
                    ame.bindValue(":mediatype", mediaType2);
                    ame.bindValue(":id", ID);
                    ame.bindValue(":postid", postID);
                    ame.bindValue(":senderid", postSenderID);
                    ame.bindValue(":commentid", newCommentId);

                    if (!ame.exec()) {
                        qDebug() << "Error executing media update query:" << ame.lastError().text();
                        qDebug() << "Executed query:" << ame.executedQuery();
                    } else {
                        qDebug() << "Media update successful";
                    }
        }
    if(suffix == "mp4" || suffix == "mkv"){
        mediaPlayer->stop();
    }


    QVector<Comment> comments;
    QSqlQuery q10;
    q10.prepare("SELECT * FROM Comments WHERE senderId = :senderid AND postId = :postid  ORDER BY time DESC");
    q10.bindValue(":senderid", postSenderID);
    q10.bindValue(":postid", postID);

    if(!q10.exec()){
        qDebug() << "Error: failed to execute query -" << q10.lastError();
    }
    while(q10.next()){
        Comment comment;
        comment.id = q10.value("id").toString();
        //profile photo
        QSqlQuery q2;
        q2.prepare("SELECT profilePhoto FROM Users WHERE id = :id");
        q2.bindValue(":id", comment.id);
        if(q2.exec()){
            if(q2.next()){
                QByteArray prof=q2.value("profilePhoto").toByteArray();
                if(!prof.isEmpty()){

                    comment.profilePhoto=prof;
                }
                else{
                    qDebug()<< "ame is empty"<<q2.lastError();
                }

            }
            else{
                qDebug()<< "ame is dead be mola "<< q2.lastError();
            }
        } else{
            qDebug()<< "error loading profile for id: "<< comment.id<<" ERROR: "<<q2.lastError();
        }

        comment.postId = q10.value("postId").toString();
        comment.text = q10.value("text").toString();

        QByteArray media=q10.value("media").toByteArray();
                // Check if media is valid
        if (!media.isEmpty()) {
            comment.media = media;
         } else {
                qDebug() << "Warning: Post with ID" << comment.id << "has empty media.";
            }
                // Handling media (BLOBs)
        QString mediaType = q10.value("mediaType").toString();
        comments.append(comment);

    }

    int size = comments.size();
    int id;
    for(int i=0; i<comments.size(); i++){
        if(comments[i].id == ID){
            id = i;
            break;
        }
    }
    for(int i=0; i<1; i++){

        QGroupBox* comment_groupBox = new QGroupBox;
        comment_groupBox->setMinimumHeight(100);
        comment_groupBox->setMaximumSize(500, 16777215);
        QVBoxLayout* comment_groupBoxLayout = new QVBoxLayout;
        comment_groupBox->setLayout(comment_groupBoxLayout);
        comment_groupBox->setStyleSheet("border-radius:5px");

        QGroupBox* info_groupBox = new QGroupBox;
        info_groupBox->setMaximumHeight(70);
        QHBoxLayout* info_groupboxLayout = new QHBoxLayout;
        info_groupBox->setStyleSheet("border-radius:5px;");
        info_groupBox->setLayout(info_groupboxLayout);

        QLabel * profile_label = new QLabel;
        profile_label->setMinimumSize(50, 50);
        profile_label->setMaximumSize(50, 50);
        profile_label->setScaledContents(true);
        info_groupboxLayout->addWidget(profile_label);

        QPixmap pix;
        if (!pix.loadFromData(comments[id].profilePhoto)) {
            qDebug() << "Error: Failed to load pixmap from profPhoto for post ID" << comments[id].id;
        } else {
            QPixmap circularPixmap(50, 50);
                    circularPixmap.fill(Qt::transparent);

                    QPainterPath path;
                    path.addEllipse(0, 0, 50, 50);

                    QPainter painter(&circularPixmap);
                    painter.setClipPath(path);
                    painter.drawPixmap(0, 0, pix.scaled(50, 50, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

                    profile_label->setPixmap(circularPixmap);
        }

        profile_label->setStyleSheet("border-radius: 25px;");

        QLabel* id_label = new QLabel(QString(""));
        id_label->setText(ID);
        info_groupboxLayout->addWidget(id_label);

        QGroupBox* media_groupBox = new QGroupBox;
        QVBoxLayout* media_groupBoxLayout = new QVBoxLayout;
        media_groupBox->setStyleSheet("background-color: rgb(250, 250, 180);");
        media_groupBox->setLayout(media_groupBoxLayout);
        comment_groupBoxLayout->addWidget(info_groupBox);

        QLabel* postImage_label = new QLabel;
        postImage_label->setMaximumSize(650, 300);
        postImage_label->setScaledContents(true);

//        QPixmap pix;
        if (!pix.loadFromData(comments[id].media)) {
            postImage_label->hide();
            comment_groupBox->setMaximumHeight(250);
            media_groupBox->setMaximumHeight(60);
            qDebug() << "Error: Failed to load pixmap from media for post ID" << comments[id].id;
        } else {
                    postImage_label->setPixmap(pix);
        }

        postImage_label->setStyleSheet("border-radius: 25px;");
        media_groupBoxLayout->addWidget(postImage_label);

        QLabel* text_label = new QLabel;
        text_label->setWordWrap(true);
        text_label->setText(comments[id].text);
        media_groupBoxLayout->addWidget(text_label);

        comment_groupBoxLayout->addWidget(media_groupBox);
        scrollLayout->addWidget(comment_groupBox);
    }

    ui->media_groupBox->setLayout(fileDialogue_groupBoxLayout);
    ui->media_groupBox->setMaximumHeight(200);
    ui->media_groupBox->hide();

}

QString comments::getTime()
{
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
        return timeString;
}

