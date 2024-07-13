#include "home.h"
#include "ui_home.h"
#include"splash.h"
#include"basicclasses.h"
#include <createpost.h>
#include<ui_createpost.h>
#include "createpost.h"
#include "wholiked.h"

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
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QMovie>
#include <QMediaPlayer>
#include <QVideoWidget>
#include<QBuffer>

#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QByteArray>

QVector<Post> posts;

QVector<Post> SGposts;

QVector<Post> RNDposts;

QList<QMediaPlayer*> allPlayers;

int i=0;

home::home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home)
{
    ui->setupUi(this);

    setWindowTitle("Home");

    QWidget* scrollWidget = new QWidget;
    QGridLayout* scrollLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(scrollLayout);
    ui->scrollArea->setWidget(scrollWidget);

    generatePost(scrollLayout);

}

home::~home()
{
    delete ui;
}

void home::generatePost(QGridLayout *scrollLayout)
{
    QSqlQuery connectionQuery;

    connectionQuery.prepare("SELECT * FROM Users WHERE id = :id");
    connectionQuery.bindValue(":id", ID);
    if(!connectionQuery.exec()){
        qDebug()<<"connection Query error"<<connectionQuery.lastError();
    }
    QStringList connectionList;
    QString user_skill_occupation;
    if(connectionQuery.next()){
        connectionList = connectionQuery.value("connections").toString().split('/');


        if(connectionQuery.value("post").toString() =="Employer"){
            user_skill_occupation=connectionQuery.value("CM_occupation").toString();
        }
        else{
            user_skill_occupation=connectionQuery.value("JS_intended_J").toString();
        }
    } else {
        qDebug() << "Error: No record found -" << connectionQuery.lastError();
    }


    QSqlQuery q;
    q.prepare("SELECT * FROM Posts ORDER BY time DESC");
    if(!q.exec()){
        qDebug() << "Error: failed to execute query -" << q.lastError();
    }
    int postCounter=0;
    while(q.next()){
        if(q.value("time").toString() < getTime()){
            if(q.value("rePostId")=="empty"){

                Post post;
                post.id = q.value("id").toString();
                post.LCR_counter = q.value("LCR_counter").toString();
                post.rePosted=q.value("rePostId").toString();
                QSqlQuery q2;
                q2.prepare("SELECT * FROM Users WHERE id = :id");
                q2.bindValue(":id", q.value("id").toString());

                if(q2.exec()){
                    if(q2.next()){
                        QByteArray prof=q2.value("profilePhoto").toByteArray();
                        if(!prof.isEmpty()){

                            post.profilePhoto=prof;
                        }
                        else{
    //                            qDebug()<< "ame is empty"<<q2.lastError();
                        }
                    }
                    else{
                        qDebug()<< "ame is dead be mola "<<q2.value("id").toString()<< q2.lastError();
                    }
                } else{
                    qDebug()<< "error loading profile for id: "<< post.id<<" ERROR: "<<q2.lastError();
                }

                post.postId = q.value("postId").toString();
                post.text = q.value("text").toString();

                QByteArray media=q.value("media").toByteArray();
                        // Check if media is valid
                if (!media.isEmpty()) {
                    post.media = media;
                 } else {
    //                        qDebug() << "Warning: Post with ID" << post.id << "has empty media.";
                    }
                        // Handling media (BLOBs)
                post.mediaType = q.value("mediaType").toString();
                bool swAppended=false;
                for(int p=0;p<connectionList.size();p++){
                    if(connectionList[p] == post.id){
                        posts.append(post);
                        swAppended=true;
                        qDebug()<<"connectionPost for:"<< post.id;
                        postCounter++;
                        break;
                    }
                }
                if(q.value("tag").toString() == user_skill_occupation && !swAppended){
                    swAppended=true;
                    postCounter++;
                    if(q2.value("post").toString() == "Employer"){
                        post.suggested="by your occupation";
                    }
                    else{
                        post.suggested="by your skill";
                    }
                    qDebug()<<"SGPost for:"<< post.id;
                    SGposts.append(post);
                }
                else if(!swAppended){
                    post.suggested="by more liked post";
                    RNDposts.append(post);
                    postCounter++;
                    qDebug()<<"RNDPost for:"<< post.id;
                }



            }




        }
        if(postCounter>99) {
            break;
        }
    }
    posts+=SGposts;
    posts+=RNDposts;


    for(int q=0;q<posts.size();q++){
        qDebug()<<posts[q].id;
    }

    qDebug()<<"posts size"<<posts.size();


    for( int j=0  ; j<10 && posts.size()-1  ; i++ , j++){

        //post groupBox

        QGroupBox* post_groupBox = new QGroupBox;
        if(posts[i].suggested != NULL){
            post_groupBox->setTitle(QString ("suggested %1").arg(posts[i].suggested));
        }
        else if(posts[i].rePosted != "empty"){
            post_groupBox->setTitle(QString ("rePosted from %1").arg(posts[i].rePosted));
        }
        //post_groupBox->setObjectName(QString("post_groupBox_%1").arg(i));
        post_groupBox->setMinimumHeight(500);
        post_groupBox->setMaximumSize(500, 16777215);
        if(darkTheme){
           post_groupBox->setStyleSheet("background-color: rgb(110, 45, 190); border-radius:5px;");
        }
        QVBoxLayout* post_groupBoxLayout = new QVBoxLayout;
        post_groupBox->setLayout(post_groupBoxLayout);

        //Info groupBox

        QGroupBox* info_groupBox = new QGroupBox/*(QString("prof-%1" ).arg(i))*/;
        info_groupBox->setMaximumHeight(70);
        if(darkTheme){
            info_groupBox->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(0, 0, 0, 0)); border-radius:5px;");
        }
        QHBoxLayout* info_groupboxLayout = new QHBoxLayout;
        info_groupBox->setLayout(info_groupboxLayout);

        QLabel * profile_label = new QLabel;
        profile_label->setMinimumSize(50, 50);
        profile_label->setMaximumSize(50, 50);
        profile_label->setScaledContents(true);
        info_groupboxLayout->addWidget(profile_label);

        // Load pixmap from media data
            QPixmap pix;
            if (!pix.loadFromData(posts[i].profilePhoto)) {
                qDebug() << "Error: Failed to load pixmap from profPhoto for post ID" << posts[i].id;
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


        //  ID label

        QLabel* id_label = new QLabel(QString(""));
        id_label->setText(posts[i].id);
        info_groupboxLayout->addWidget(id_label);

        QSpacerItem* info_horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
        info_groupboxLayout->addSpacerItem(info_horizontalSpacer);

        //follow PushButton

        QPushButton* follow_pushButton = new QPushButton;
        follow_pushButton->setCursor(Qt::OpenHandCursor);
        follow_pushButton->setMinimumSize(0, 44);
        follow_pushButton->setMaximumSize(110, 16777215);
        QFont font("Pristina", 17);
        follow_pushButton->setFont(font);

        follow_pushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); color: rgb(41, 69, 255); border-radius: 20px;");
        info_groupboxLayout->addWidget(follow_pushButton);

        post_groupBoxLayout->addWidget(info_groupBox);

        //Media groupBox

        QGroupBox* media_groupBox = new QGroupBox;
        QVBoxLayout* media_groupBoxLayout = new QVBoxLayout;
        media_groupBox->setLayout(media_groupBoxLayout);

        // Post Image

        if(posts[i].mediaType =="image"){
            QLabel* postImage_label = new QLabel;
            //postImage_label->setMinimumHeight(450);
            postImage_label->setMaximumSize(650, 300);
            postImage_label->setScaledContents(true);

    //        QPixmap pix;
            if (!pix.loadFromData(posts[i].media)) {
                qDebug() << "Error: Failed to load pixmap from media for post ID" << posts[i].id;
            } else {
                        postImage_label->setPixmap(pix);
            }

            postImage_label->setStyleSheet("border-radius: 25px;");
            postImage_label->setStyleSheet("border-image: url(:/icon/icon-logo.png);");
            media_groupBoxLayout->addWidget(postImage_label);
        } else if(posts[i].mediaType == "video"){

        } else if(posts[i].mediaType == "gif"){ // media is gif

        }


        QLabel* text_label = new QLabel;
        text_label->setWordWrap(true);
        text_label->setText(posts[i].text);
        media_groupBoxLayout->addWidget(text_label);

        post_groupBoxLayout->addWidget(media_groupBox);

        //SeeMore groupBox

        QGroupBox* seeMore_groupBox = new QGroupBox;
        QHBoxLayout* seeMore_groupBoxLayout = new QHBoxLayout;
        seeMore_groupBox->setLayout(seeMore_groupBoxLayout);
        seeMore_groupBox->setMaximumHeight(30);

        QSpacerItem* left_horizontalSpacer = new QSpacerItem(347, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
        seeMore_groupBoxLayout->addSpacerItem(left_horizontalSpacer);

        QPushButton* seeMore_pushButton = new QPushButton;
        seeMore_pushButton->setText("see more");
        seeMore_pushButton->setMinimumSize(70, 0);
        seeMore_pushButton->setMaximumWidth(75);
        seeMore_pushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius:10px; color: rgb(161, 161, 161);");
        seeMore_groupBoxLayout->addWidget(seeMore_pushButton);

        post_groupBoxLayout->addWidget(seeMore_groupBox);

        //Button groupBox

        QGroupBox* button_groupBox = new QGroupBox;
        QVBoxLayout* button_groupBoxLayout = new QVBoxLayout;
        button_groupBox->setLayout(button_groupBoxLayout);
        button_groupBox->setMinimumHeight(124);
        button_groupBox->setMaximumHeight(130);

        QSpacerItem* button_horizontalSpacer = new QSpacerItem(20, 40, QSizePolicy::Fixed, QSizePolicy::Expanding);
        button_groupBoxLayout->addSpacerItem(button_horizontalSpacer);

        QGroupBox* counter_groupBox = new QGroupBox;
        QHBoxLayout* counter_groupBoxLayout = new QHBoxLayout;
        counter_groupBox->setLayout(counter_groupBoxLayout);

        QStringList lcr= posts[i].LCR_counter.split('/');

        QPushButton* whoLikedPushButton = new QPushButton;
        whoLikedPushButton->setText(QString("%1 like").arg(lcr[0]));
        whoLikedPushButton->setMinimumSize(110, 20);
        whoLikedPushButton->setMaximumSize(150, 30);
        whoLikedPushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius:10px;");
        counter_groupBoxLayout->addWidget(whoLikedPushButton);
        whoLikedPushButton->setObjectName(QString::number(i));
        QObject::connect(whoLikedPushButton, &QPushButton::clicked, [=]() mutable {
            int k=whoLikedPushButton->objectName().toInt();
            postSenderID = posts[k].id;
            postID = posts[k].postId;
            wholiked * window=new wholiked;
            window->show();
        });

        QSpacerItem* counter_horizontalSpacer = new QSpacerItem(180, 20, QSizePolicy::Preferred, QSizePolicy::Fixed);
        counter_groupBoxLayout->addSpacerItem(counter_horizontalSpacer);

        QLabel* commentAndRepostCounterLabel = new QLabel;
        commentAndRepostCounterLabel->setText(QString("%1 comment, %2 rePoste").arg(lcr[1]).arg(lcr[2]));
        commentAndRepostCounterLabel->setMinimumSize(110, 20);
        commentAndRepostCounterLabel->setMaximumSize(150, 30);
        counter_groupBoxLayout->addWidget(commentAndRepostCounterLabel);

        button_groupBoxLayout->addWidget(counter_groupBox);

        QGroupBox* react_groupBox = new QGroupBox;
        QHBoxLayout* react_groupBoxLayout = new QHBoxLayout;
        react_groupBox->setLayout(react_groupBoxLayout);

        QPushButton* likePushButton = new QPushButton;
        QFont font2("MS Shell Dlg 2", 23);
        likePushButton->setCursor(Qt::PointingHandCursor);
        likePushButton->setMaximumWidth(60);
        likePushButton->setFont(font2);
        react_groupBoxLayout->addWidget(likePushButton);

        // check post is liked
        QSqlQuery query;
        query.prepare("SELECT * FROM Likes WHERE id = :id AND senderId = :senderid AND postId = :postid");
        query.bindValue(":id",ID);
        query.bindValue(":senderid", posts[i].id);
        query.bindValue(":postid", posts[i].postId);

        if (!query.exec()) {
            qDebug() << "Query execution failed: " << query.lastError();
        }

        if(query.next()){
            likePushButton->setStyleSheet("image: url(:/icon/icon-liked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        } else{
            likePushButton->setStyleSheet("image: url(:/icon/icon-unliked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        }

        likePushButton->setObjectName(QString::number(i));
        QObject::connect(likePushButton, &QPushButton::clicked, [=]() mutable {
            int k=likePushButton->objectName().toInt();
            QSqlQuery query;
            query.prepare("SELECT * FROM Likes WHERE id = :id AND senderId = :senderid AND postId = :postid");
            query.bindValue(":id", ID);
            query.bindValue(":senderid", posts[k].id);
            query.bindValue(":postid", posts[k].postId);

            if (!query.exec()) {
                qDebug() << "Query execution failed: " << query.lastError();
            }

            if (query.next()) {
                // Record exists, delete it
                QSqlQuery deleteQuery;
                deleteQuery.prepare("DELETE FROM Likes WHERE id = :id AND senderId = :senderid AND postId = :postid");
                deleteQuery.bindValue(":id", ID);
                deleteQuery.bindValue(":senderid", posts[k].id);
                deleteQuery.bindValue(":postid", posts[k].postId);

                if (!deleteQuery.exec()) {
                    qDebug() << "Delete query execution failed: " << deleteQuery.lastError();
                }

                likePushButton->setStyleSheet("image: url(:/icon/icon-unliked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
            } else {
                QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO Likes (id, senderId, postId ,time) VALUES (:id, :senderid, :postid, :time)");
                insertQuery.bindValue(":id", ID);
                insertQuery.bindValue(":senderid", posts[k].id);
                insertQuery.bindValue(":postid", posts[k].postId);
                insertQuery.bindValue(":time", getTime());

                if (!insertQuery.exec()) {
                    qDebug() << "Insert query execution failed: " << insertQuery.lastError();
                }
                likePushButton->setStyleSheet("image: url(:/icon/icon-liked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
            }
        });

        QPushButton* commentPushButton = new QPushButton;
        //commentPushButton->setMinimumSize(0, 40);
        commentPushButton->setFont(font2);
        commentPushButton->setCursor(Qt::PointingHandCursor);
        commentPushButton->setStyleSheet("image: url(:/icon/icon-comment.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        react_groupBoxLayout->addWidget(commentPushButton);
        commentPushButton->setMaximumWidth(60);

        QPushButton* repostPushbutton = new QPushButton;
        repostPushbutton->setCursor(Qt::PointingHandCursor);
        repostPushbutton->setMaximumWidth(60);
        repostPushbutton->setFont(font2);
        repostPushbutton->setStyleSheet("image: url(:/icon/icon-repost.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");

        repostPushbutton->setObjectName(QString::number(i));
        QObject::connect(repostPushbutton, &QPushButton::clicked, [=]() mutable {
            int k=repostPushbutton->objectName().toInt();
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO Posts (id, postId, tag, text, media, mediaType, LCR_counter, rePostId, time) VALUES (:id, :postid, :tag, :text, :media, :mediaType, :lcr_counter, :repostid, :time)");
            insertQuery.bindValue(":id", posts[k].id);
            insertQuery.bindValue(":postid", posts[k].postId);
            insertQuery.bindValue(":tag", posts[k].tag);
            insertQuery.bindValue(":text", posts[k].text);
            insertQuery.bindValue(":media", posts[k].media);
            insertQuery.bindValue(":mediaType", posts[k].mediaType);
            insertQuery.bindValue(":lcr_counter", "0/0/0");
            insertQuery.bindValue(":repostid", ID);
            insertQuery.bindValue(":time", getTime());
            if(!insertQuery.exec()){
                qDebug()<<"hey mmd!<<"<<insertQuery.lastError();
            }
        });
        react_groupBoxLayout->addWidget(repostPushbutton);

        QPushButton* sendPushButton = new QPushButton;
        sendPushButton->setMaximumSize(50, 50);
        sendPushButton->setCursor(Qt::PointingHandCursor);
        sendPushButton->setFont(font2);
        sendPushButton->setStyleSheet("image: url(:/icon/icon-send-2.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        react_groupBoxLayout->addWidget(sendPushButton);

        button_groupBoxLayout->addWidget(react_groupBox);
        post_groupBoxLayout->addWidget(button_groupBox);

        scrollLayout->addWidget(post_groupBox);
    }
}

QString home::getTime()
{
    QDateTime dateTime = QDateTime::currentDateTime();
        int year = dateTime.date().year();
        int month = dateTime.date().month();
        int day = dateTime.date().day();
        int hour = dateTime.time().hour();
        int minute = dateTime.time().minute();
        int second = dateTime.time().second();
        QString timeString = QString("%1%2%3%4%5%6")
                .arg(year, 4, 10, QChar('0'))
                .arg(month, 2, 10, QChar('0'))
                .arg(day, 2, 10, QChar('0'))
                .arg(hour, 2, 10, QChar('0'))
                .arg(minute, 2, 10, QChar('0'))
                .arg(second, 2, 10, QChar('0'));
        return timeString;
}

void home::on_createPost_pushButton_clicked()
{
    createPost* pg10 = new createPost;
    pg10->show();

}


