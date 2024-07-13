#include "viewprofile.h"
#include "ui_viewprofile.h"
#include "basicclasses.h"
#include"wholiked.h"


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

viewprofile::viewprofile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewprofile)
{
    ui->setupUi(this);

    QVector<Post> posts;
    QByteArray prof;
    QPixmap postCircularPixmap(50, 50);

    QWidget* scrollWidget = new QWidget;
    QGridLayout* scrollLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(scrollLayout);
    ui->posts_scrollArea->setWidget(scrollWidget);

    QSqlQuery q;
    q.prepare("SELECT * FROM Users WHERE id = :id");
    q.bindValue(":id", viewProfileID);

    if (!q.exec()) {
            qDebug() << "Error executing query:" << q.lastError().text();
    }
    Account viewAccount;
    Person person;
    Company company;

        if (q.next()) {
            ui->id_label->setText(viewProfileID);

            // setting up the profilePhoto :

            ui->profilePhoto_label->setScaledContents(true);
            prof = q.value("profilePhoto").toByteArray();
            if(!prof.isEmpty()){
                person.profilePhoto=prof;
            }
            else{
                qDebug()<<"prof is empty!"<<q.lastError();
            }

            QPixmap Postpix;
            if (!Postpix.loadFromData(prof)) {
                qDebug() << "Error: Failed to load pixmap from profPhoto for post ID";
            } else {

                        postCircularPixmap.fill(Qt::transparent);

                        QPainterPath path;
                        path.addEllipse(0, 0, 50, 50);

                        QPainter painter(&postCircularPixmap);
                        painter.setClipPath(path);
                        painter.drawPixmap(0, 0, Postpix.scaled(50, 50, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
            }

            QPixmap pix;
            QPixmap circularPixmap(70, 70);
            if (!pix.loadFromData(prof)) {
                qDebug() << "Error: Failed to load pixmap " ;
            } else {

                        circularPixmap.fill(Qt::transparent);

                        QPainterPath path;
                        path.addEllipse(0, 0, 70, 70);

                        QPainter painter(&circularPixmap);
                        painter.setClipPath(path);
                        painter.drawPixmap(0, 0, pix.scaled(70, 70, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

                        ui->profilePhoto_label->setPixmap(circularPixmap);
            }

            ui->profilePhoto_label->setStyleSheet("border-radius: 35px;");



            QSqlQuery qPost;
                qPost.prepare("SELECT * FROM Posts WHERE id = :id ORDER BY time DESC");
                qPost.bindValue(":id", viewProfileID);
                if(!qPost.exec()){
                    qDebug()<< "error execute qPost";
                }
                while(qPost.next()){
                    Post post;

                    post.id = qPost.value("id").toString();
                    post.rePosted = qPost.value("rePostId").toString();
//                    qDebug()<<"rePost Error ! "<<q
/*
//                    QSqlQuery q2;
//                    q2.prepare("SELECT profilePhoto FROM Users WHERE id = :id");
//                    q2.bindValue(":id", q.value("id").toString());
//                    if(q2.exec()){
//                        if(q2.next()){
//                            QByteArray prof=q2.value("profilePhoto").toByteArray();
//                            if(!prof.isEmpty()){

//                                post.profilePhoto=prof;
//                            }
//                            else{
//                                qDebug()<< "ame is empty"<<q2.lastError();
//                            }

//                        }
//                        else{
//                            qDebug()<< "ame is dead be mola "<< q2.lastError();
//                        }
//                    } else{
//                        qDebug()<< "error loading profile for id: "<< post.id<<" ERROR: "<<q2.lastError();
//                    } */

                    post.postId = qPost.value("postId").toString();
                    post.text = qPost.value("text").toString();
                    post.LCR_counter = qPost.value("LCR_counter").toString();
                    QByteArray media=qPost.value("media").toByteArray();
                            // Check if media is valid
                    if (!media.isEmpty()) {
                        post.media = media;
                     } else {
                            qDebug() << "Warning: Post with ID" << post.id << "has empty media.";
                        }
                            // Handling media (BLOBs)
                    QString mediaType = qPost.value("mediaType").toString();
                    posts.append(post);
                }
            QStringList  followersList;
            QStringList connectionsList ;
            if(q.value("post") == "JobSeeker" ){

                person.Skill =(q.value("JS_intended_J").toString());
                person.name =q.value("name").toString();
                person.lastName = q.value("lastName").toString();
                person.email = q.value("email").toString();
                person.college = q.value("JS_college").toString();
                connectionsList = q.value("connections").toString().split('/');
                person.connection_counter = connectionsList.size();
                person.UsersPosts = posts;

                // set labels:

                ui->skill_occupation_label->setText(person.Skill);
                ui->name_label->setText(person.name +'-'+person.lastName);
                ui->email_label->setText(person.email);
                ui->college_PNumber_label->setText(person.college);
                ui->address_label->hide();
                ui->followers_connections_label->setText(QString("%1 followers").arg(person.connection_counter));
                // for debuging:
                ui->email_label->setNum(posts.size());

                // end of debug.
                for(int i = 0 ; i<connectionsList.size() ; i++){
                    if(connectionsList[i] == ID){
                        ui->follow_pushButton->setText("Connected");
                        break;
                    }
                }
            }
            else if(q.value("post") == "Employer" ){
                company.occupation = q.value("CM_occupation").toString();
                company.Company_Name = q.value("CM_name").toString();
                company.email = q.value("email").toString();
                company.PhoneNumber = q.value("phoneNumber").toString();
                company.address = q.value("CM_address").toString();
                followersList = q.value("CM_followers").toString().split('/');
                company.connection_counter = followersList.size();
                company.UsersPosts = posts;

                //set Labels
                ui->skill_occupation_label->setText(company.occupation);
                ui->name_label->setText(company.Company_Name);
                ui->email_label->setText(company.email);
                ui->college_PNumber_label->setText(company.PhoneNumber);
                ui->address_label->setText(company.address);
                ui->followers_connections_label->setText(QString("%1 followers").arg(company.connection_counter));

                for(int i = 0 ; i<followersList.size() ; i++){
                    if(followersList[i] == ID){
                        ui->follow_pushButton->setText("Following");
                        break;
                    }
                }
            }
        }

        for( int i=0  ; i<posts.size()  ; i++){

            //post groupBox

            QGroupBox* post_groupBox = new QGroupBox;
            if(posts[i].rePosted != "empty"){
                post_groupBox->setTitle(QString (" from ' %1 'Reposted").arg(posts[i].rePosted));
            }
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
            profile_label->setPixmap(postCircularPixmap);
            profile_label->setStyleSheet("border-radius: 25px;");
            info_groupboxLayout->addWidget(profile_label);

            //  ID label

            QLabel* id_label = new QLabel(QString(""));
            id_label->setText(posts[i].id);
            info_groupboxLayout->addWidget(id_label);

            QSpacerItem* info_horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
            info_groupboxLayout->addSpacerItem(info_horizontalSpacer);

//            //follow PushButton

//            QPushButton* follow_pushButton = new QPushButton;
//            follow_pushButton->setCursor(Qt::OpenHandCursor);
//            follow_pushButton->setMinimumSize(0, 44);
//            follow_pushButton->setMaximumSize(110, 16777215);
//            QFont font("Pristina", 17);
//            follow_pushButton->setFont(font);
//            follow_pushButton->setText("+follow");
//            follow_pushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); color: rgb(41, 69, 255); border-radius: 20px;");
//            info_groupboxLayout->addWidget(follow_pushButton);

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

            QPixmap pix;

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
            commentAndRepostCounterLabel->setText("?comment ? repost");
            commentAndRepostCounterLabel->setMinimumSize(110, 20);
            commentAndRepostCounterLabel->setMaximumSize(150, 30);
            counter_groupBoxLayout->addWidget(commentAndRepostCounterLabel);

            button_groupBoxLayout->addWidget(counter_groupBox);

            QGroupBox* react_groupBox = new QGroupBox;
            QHBoxLayout* react_groupBoxLayout = new QHBoxLayout;
            react_groupBox->setLayout(react_groupBoxLayout);

            QPushButton* likePushButton = new QPushButton;
    //        likePushButton->setObjectName(QString("likePushButton-%1").arg(i));
            QFont font2("MS Shell Dlg 2", 23);
            likePushButton->setMaximumWidth(60);
            //likePushButton->setMinimumSize(0, 40);
            likePushButton->setFont(font2);
    //        likePushButton->setStyleSheet("image: url(:/icon/icon-unliked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
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

                // Execute the query
                if (!query.exec()) {
                    qDebug() << "Query execution failed: " << query.lastError();
                }

                // Check if any results were returned
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

                    // Update the button style to "unliked"
                    likePushButton->setStyleSheet("image: url(:/icon/icon-unliked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
                } else {
                    // Record does not exist, insert it
                    QSqlQuery insertQuery;
                    insertQuery.prepare("INSERT INTO Likes (id, senderId, postId ,time) VALUES (:id, :senderid, :postid, :time)");
                    insertQuery.bindValue(":id", ID);
                    insertQuery.bindValue(":senderid", posts[k].id);
                    insertQuery.bindValue(":postid", posts[k].postId);
                    insertQuery.bindValue(":time", getTime());

                    if (!insertQuery.exec()) {
                        qDebug() << "Insert query execution failed: " << insertQuery.lastError();
                    }

                    // Update the button style to "liked"
                    likePushButton->setStyleSheet("image: url(:/icon/icon-liked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
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

viewprofile::~viewprofile()
{
    delete ui;
}
