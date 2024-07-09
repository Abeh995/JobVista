#include "home.h"
#include "ui_home.h"
#include"splash.h"
#include"basicclasses.h"
#include <createpost.h>
#include<ui_createpost.h>
#include "createpost.h"

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

#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QByteArray>

QVector<Post> posts;

int i=0;
//my net:

bool isLiked2= false;

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
    QSqlQuery q;
    q.prepare("SELECT * FROM Posts ORDER BY time DESC");
    if(!q.exec()){
        qDebug() << "Error: failed to execute query -" << q.lastError();
    }

    while(q.next()){
        Post post;
        post.id = q.value("id").toString();

        QSqlQuery q2;
        q2.prepare("SELECT profilePhoto FROM Users WHERE id = :id");
        q2.bindValue(":id", q.value("id").toString());
        if(q2.exec()){
            if(q2.next()){
                QByteArray prof=q2.value("profilePhoto").toByteArray();
                if(!prof.isEmpty()){

                    post.profilePhoto=prof;
                }
                else{
                    qDebug()<< "ame is empty"<<q2.lastError();
                }

            }
            else{
                qDebug()<< "ame is dead be mola "<< q2.lastError();
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
                qDebug() << "Warning: Post with ID" << post.id << "has empty media.";
            }
                // Handling media (BLOBs)
        QString mediaType = q.value("mediaType").toString();
        posts.append(post);
    }

    //    for (const Post &post : posts) {
    //            qDebug() << "Post ID:" << post.id << ", Time:" << post.time;
    //        }

    for( int j=0  ; j<10  ; i++ , j++){

        //post groupBox

        QGroupBox* post_groupBox = new QGroupBox(QString("Suggested-%1").arg(i));
        //post_groupBox->setObjectName(QString("post_groupBox_%1").arg(i));
        post_groupBox->setMinimumHeight(500);
        post_groupBox->setMaximumSize(500, 16777215);
        QVBoxLayout* post_groupBoxLayout = new QVBoxLayout;
        post_groupBox->setLayout(post_groupBoxLayout);

        //Info groupBox

        QGroupBox* info_groupBox = new QGroupBox/*(QString("prof-%1" ).arg(i))*/;
        info_groupBox->setMaximumHeight(70);
        QHBoxLayout* info_groupboxLayout = new QHBoxLayout;
        info_groupBox->setLayout(info_groupboxLayout);

        QLabel * profile_label = new QLabel;
        profile_label->setMinimumSize(50, 50);
        profile_label->setMaximumSize(50, 50);
        profile_label->setScaledContents(true);
        info_groupboxLayout->addWidget(profile_label);
        // for example:

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
        follow_pushButton->setText("+follow");
        follow_pushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); color: rgb(41, 69, 255); border-radius: 20px;");
        info_groupboxLayout->addWidget(follow_pushButton);

        post_groupBoxLayout->addWidget(info_groupBox);

        //Media groupBox

        QGroupBox* media_groupBox = new QGroupBox;
        QVBoxLayout* media_groupBoxLayout = new QVBoxLayout;
        media_groupBox->setLayout(media_groupBoxLayout);

        // Post Image

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
        whoLikedPushButton->setText(QString("Ame Sekine And %1 other liked").arg(lcr[0]));
        whoLikedPushButton->setMinimumSize(110, 20);
        whoLikedPushButton->setMaximumSize(150, 30);
        whoLikedPushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius:10px;");
        counter_groupBoxLayout->addWidget(whoLikedPushButton);

        QSpacerItem* counter_horizontalSpacer = new QSpacerItem(180, 20, QSizePolicy::Preferred, QSizePolicy::Fixed);
        counter_groupBoxLayout->addSpacerItem(counter_horizontalSpacer);

        QLabel* commentAndRepostCounterLabel = new QLabel;
        commentAndRepostCounterLabel->setText("?comment ? repost");
        commentAndRepostCounterLabel->setMinimumSize(110, 20);
        commentAndRepostCounterLabel->setMaximumSize(150, 30);
        counter_groupBoxLayout->addWidget(commentAndRepostCounterLabel);

        button_groupBoxLayout->addWidget(counter_groupBox);

        QGroupBox* react_groupBox = new QGroupBox;
        QHBoxLayout* react_groupBoxLayout = new QHBoxLayout;
        react_groupBox->setLayout(react_groupBoxLayout);

        QPushButton* likePushButton = new QPushButton;
        likePushButton->setObjectName(QString("likePushButton-%1").arg(i));
        QFont font2("MS Shell Dlg 2", 23);
        likePushButton->setMaximumWidth(60);
        //likePushButton->setMinimumSize(0, 40);
        likePushButton->setFont(font2);
        likePushButton->setStyleSheet("image: url(:/icon/icon-unliked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        react_groupBoxLayout->addWidget(likePushButton);
        likePushButton->setObjectName(QString::number(i));

        QObject::connect(likePushButton, &QPushButton::clicked, [=](){
            int k=likePushButton->objectName().toInt();
            isLiked2=!isLiked2;
            //unique ...
            if(isLiked2){
                qDebug()<< "after posts are generated, the -i- variable is 10 and it is not what i want  ! HELP ME!"<<getTime()<<"---"<<posts[k].id;
                likePushButton->setStyleSheet("image: url(:/icon/icon-liked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
            }
            else{
                QSqlQuery q2;

                            qDebug() << "Preparing the INSERT query...";
                            if (!q2.prepare("INSERT INTO Likes (id, senderId, postId, time) VALUES (:id, :senderId, :postId, :time)")) {
                                qDebug() << "Failed to prepare insert query:" << q2.lastError().text();
                                return;
                            }
                            q2.bindValue(":id",ID);
                            q2.bindValue(":senderId", posts[k].id);
                            q2.bindValue(":postId", posts[k].postId);
                            q2.bindValue(":time", getTime());


                            qDebug() << "Executing the INSERT query...";
                            if (!q2.exec()) {
                                qDebug() << "Failed to insert like:" << q2.lastError().text();
                                return;
                            }



                likePushButton->setStyleSheet("image: url(:/icon/icon-unliked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
            }

        });

        QPushButton* commentPushButton = new QPushButton;
        //commentPushButton->setMinimumSize(0, 40);
        commentPushButton->setFont(font2);
        commentPushButton->setStyleSheet("image: url(:/icon/icon-comment.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        react_groupBoxLayout->addWidget(commentPushButton);
        commentPushButton->setMaximumWidth(60);

        QPushButton* repostPushbutton = new QPushButton;
        //repostPushbutton->setMinimumSize(0, 50);
        repostPushbutton->setFont(font2);
        repostPushbutton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        repostPushbutton->setText("🔁");
        react_groupBoxLayout->addWidget(repostPushbutton);
        repostPushbutton->setMaximumWidth(60);

        QPushButton* sendPushButton = new QPushButton;
        //sendPushButton->setMinimumSize(0, 50);
        sendPushButton->setFont(font2);
        sendPushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        sendPushButton->setText("📤");
        react_groupBoxLayout->addWidget(sendPushButton);
        sendPushButton->setMaximumWidth(60);

        button_groupBoxLayout->addWidget(react_groupBox);
        post_groupBoxLayout->addWidget(button_groupBox);

        scrollLayout->addWidget(post_groupBox);
    }
}

QString home::getTime()
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

void home::on_createPost_pushButton_clicked()
{
    createPost* pg10 = new createPost;
    pg10->show();

}


