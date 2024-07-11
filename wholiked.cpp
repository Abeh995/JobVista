#include "wholiked.h"
#include "ui_wholiked.h"
#include"splash.h"
#include "basicclasses.h"

#include <QGroupBox>
#include<QHBoxLayout>
#include<QLabel>
#include <QPainter>
#include<QPixmap>
#include<QPushButton>
#include <QDebug>

#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QByteArray>

wholiked::wholiked(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wholiked)
{
    ui->setupUi(this);

    QVector<Like> likers;

    QWidget* scrollWidget = new QWidget;
    QGridLayout* scrollLayout = new QGridLayout(scrollWidget);
    scrollWidget->setLayout(scrollLayout);
    ui->scrollArea->setWidget(scrollWidget);

    QSqlQuery q;
    q.prepare("SELECT * FROM Likes WHERE senderId = :senderid AND postId = :postid  ORDER BY time DESC");
    q.bindValue(":senderid", postSenderID);
    q.bindValue(":postid", postID);
    if(!q.exec()){
        qDebug() << "Error: failed to execute query -" << q.lastError();
    }

    while(q.next()){
        Like like;
        like.id = q.value("id").toString();

        // Get ProfilePhoto
        QSqlQuery q2;
        q2.prepare("SELECT profilePhoto FROM Users WHERE id = :id");
        q2.bindValue(":id", q.value("id").toString());
        if(q2.exec()){
            if(q2.next()){
                QByteArray prof=q2.value("profilePhoto").toByteArray();
                if(!prof.isEmpty()){

                    like.profilePhoto=prof;
                }
                else{
                    qDebug()<< "ame is empty"<<q2.lastError();
                }

            }
            else{
                qDebug()<< "ame is dead be mola "<< q2.lastError();
            }
        } else{
            qDebug()<< "error loading profile for id: "<< like.id<<" ERROR: "<<q2.lastError();
        }

        likers.append(like);
    }

    int size=likers.size();

    for(int i=0  ; i<  size ; i++){

        QGroupBox* info_groupBox = new QGroupBox/*(QString("prof-%1" ).arg(i))*/;
        info_groupBox->setMaximumHeight(70);
        QHBoxLayout* info_groupboxLayout = new QHBoxLayout;
        info_groupBox->setLayout(info_groupboxLayout);

        QLabel * profile_label = new QLabel;
        profile_label->setMinimumSize(50, 50);
        profile_label->setMaximumSize(50, 50);
        profile_label->setScaledContents(true);
        profile_label->setStyleSheet("border-radius: 25px;");
        info_groupboxLayout->addWidget(profile_label);

        QPixmap pix;
        if (!pix.loadFromData(likers[i].profilePhoto)) {
            qDebug() << "Error: Failed to load pixmap from profPhoto for post ID" << likers[i].id;
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

        //  ID push button

        QPushButton* id_pushButton= new QPushButton;
        QFont font("Segoe UI Emoji", 13);
//        likePushButton->setMaximumWidth(60);
        id_pushButton->setMinimumSize(50, 30);
        id_pushButton->setFont(font);
        id_pushButton->setText(likers[i].id);
        id_pushButton->setCursor(Qt::OpenHandCursor);
        id_pushButton->setStyleSheet("QPushButton{ border-radius:25px;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));} QPushButton:hover{	color: rgb(212, 8, 255);} ");

        info_groupboxLayout->addWidget(id_pushButton);

        id_pushButton->setObjectName(QString::number(i));
        QObject::connect(id_pushButton, &QPushButton::clicked, [=]() mutable {
            int k=id_pushButton->objectName().toInt();
            viewProfileID=likers[k].id;
            //////////////////////////////////////////////////////////////////////////// show VIEW PROFILE ///////////////////////////////////
//            this->close();
        });

        QSpacerItem* info_horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
        info_groupboxLayout->addSpacerItem(info_horizontalSpacer);

        QLabel* liked_label = new QLabel;
        liked_label->setMinimumSize(30, 30);
        liked_label->setStyleSheet("image: url(:/icon/icon-liked.png);background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        info_groupboxLayout->addWidget(liked_label);

        scrollLayout->addWidget(info_groupBox);
    }

}

wholiked::~wholiked()
{
    delete ui;
}
