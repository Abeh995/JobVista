#include "signup.h"
#include "ui_signup.h"
#include "splash.h"
#include "login.h"
#include "verification.h"

#include <QLineEdit>
#include <QRandomGenerator>
#include <QThread>
#include <QValidator>
#include <QMessageBox>
#include "QTimer"
#include "QFocusEvent"
#include "QPalette"
#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QtCore/qmath.h>
#include <QFile>
#include <QDir>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>

//QString ID;
//QString PhoneNumber;
int swReCaptcha=0,swDatabase = 1, swCaptcha, swPhone = 1;
QString inText;

signup::signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);

    setWindowTitle("Signup");
    GenCaptcha();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(700);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
//    ui->pushButton_2->setFocus();
//    ui->pushButton_2->setDefault(true);
//    ui->pushButton_2->setAutoDefault(false);
    ui->lineEdit_username->setFocus();
    ui->lineEdit_phonenumber->setValidator(new QIntValidator);



//        QPalette pal = ui->comboBox->palette();
//        pal.setColor(ui->comboBox->backgroundRole(), Qt::red); // Set the desired background color
//        ui->comboBox->setPalette(pal);
}

signup::~signup()
{
    delete ui;
}

void signup::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
       {
           handleKeyPress(event);
       }
       else
       {
           QWidget::keyPressEvent(event);
       }
}

int signup::CheckInformation()
{
    swCaptcha=swDatabase=1;
    QSqlQuery q;
    ID = ui->lineEdit_username->text();
    PhoneNumber = ui->comboBox->currentText() + "-" + ui->lineEdit_phonenumber->text();
    q.exec("SELECT password FROM jobSeekers WHERE id = '"+ID+"'");
    if(q.first()){
        return 1; // THE USERNAME ALREDY EXIST
    }
    q.exec("SELECT password FROM jobSeekers WHERE phoneNumber = '"+PhoneNumber+"'");
    if(q.first()){
        return 2; // THE PHONE NUMBER ALREDY EXIST
    }
    QString Password=ui->lineEdit_password->text();
    bool num=true, letter=true, shape=true;
//    for(int i=0; Password[i] != "\0";i++){
//        if(Password[i]>=48&&Password[i]<=57) num= true;
//                else if((Password[i]>='A'&& Password[i]<='Z') || (Password[i]>='a'&& Password[i]<='z')) letter= true;
//                            else if(Password[i]=='!' || Password[i]=='@' || Password[i]=='#' || Password[i]== '$' ) shape =true;
//    }
    if(num && letter ){
        q.exec("INSERT INTO jobSeekers(id, password, phoneNumber) VALUES ('"+ID+"', '"+Password+"','"+PhoneNumber+"')");
        if(shape){
           return 0;
        }
        else return 3;
    }
    else return 4;
}

void signup::GenCaptcha()
{
    inText = "\0";
    srand(time(0));
    char cap;
    int sw = rand() % 2;

    for(int i = 0; i < 5 ; i++){
        if(sw){
            cap = rand()%26 + 65;
            inText += cap;
            sw = rand() % 2;
        }
        else{
            cap = rand()%10 + 48;
            inText += cap;
            sw = rand() % 2;
        }

    }
    //ui->label_captcha->setText(inText);
    QFile newpic("pics/"+inText+".png");
    newpic.open(QIODevice::WriteOnly);
    qDebug() << "pics/"+inText+".png";
    distortImg(makeImg(inText)).save(&newpic,"PNG");
}

void signup::on_pushButton_continue_clicked()
{
    QString enteredPass = ui->lineEdit_captch->text();


    if(ui->lineEdit_username->text() == NULL ){
        QMessageBox::warning(this,"Empty Form","Please Fill username form first!");
        ui->lineEdit_captch->setText("\0");
        GenCaptcha();
    }
    else if(ui->lineEdit_password->text()==NULL){
        QMessageBox::warning(this,"Empty Form","Please Fill password form first!");
        ui->lineEdit_captch->setText("\0");
        GenCaptcha();
    }
    else if(ui->lineEdit_phonenumber->text()==NULL){
        QMessageBox::warning(this,"Empty Form","Please Enter your PhoneNumber first!");
        ui->lineEdit_captch->setText("\0");
        GenCaptcha();
    }
    else if(ui->comboBox->currentText()== " "){
        QMessageBox::warning(this,"Empty Form","Please Select your country code aslo!");
        ui->lineEdit_captch->setText("\0");
        GenCaptcha();
    }
    else if(enteredPass != inText){ /////////                  check captcha!
        QMessageBox::warning(this,"Wrong captcha","Please Enter captcha code correctly!");
        ui->lineEdit_captch->setText("\0");
        GenCaptcha();
        // change captcha  again
    }
    else{
        int CI = CheckInformation();
        if(CI==0) {
            //show a message not in box
            QMessageBox::information(this, "Registered","You have successfully registered");
            verification *vr = new verification;
            vr->show();
            this->close();
        }
            else if(CI==3){
                QMessageBox::information(this, "simple password", "your password is not really safe, you can change it later!");
            }
            else if(CI==1){
                QMessageBox::warning(this,
                                 "Taken Username!",
                                 "<ul>"
                                 "<li>"
                                 "UserName already exist!"
                                 "</li>"
                                 "</ul>");
            }
            else if(CI==2) {
                QMessageBox::warning(this,
                                  "Taken PhoneNumber!",
                                  "<ul>"
                                  "<li>"
                                  "PhoneNumber already exist!"
                                  "</li>"
                                  "</ul>");
            }
            else {
                 QMessageBox::warning(this,"Really simple Password!", "<ul>""<li>" "What's That ???""</li>""</ul>""<ul>""<li>""What's that BRother" "</li>" "</ul>");
            }
    }

}

void signup::handleKeyPress(QKeyEvent *event)
{
    // Show the previous window
        // For example:
        login *lg = new login();
        lg->show();
        this->close();
}
///////////////////////////////////////////////////
QPixmap signup::makeImg(QString inText)
{
    QPixmap pixmap(300,50);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial Black",26));
    painter.drawText(50,40,inText);
    //ui->label->setPixmap(pixmap);

    return pixmap;
}

QPixmap signup::distortImg(QPixmap pixmap)
{
    QImage pixmapImg = pixmap.toImage();
    QPixmap pixmap2(pixmap.width(),pixmap.height());
    QPainter painter2(&pixmap2);

    // Distort text
    for(int x = 0; x < pixmap.width(); x++){
        for(int y = 0; y < pixmap.height(); y++){
            qsrand(x);
            float rand1 = qrand()%5;
            qsrand(y);
            float rand2 = qrand()%5;
            float sinx = sin(x/10+1)*5;
            float siny = qSin(y/10)*5;
            int newx = x+rand1+sinx;
            int newy = y+rand2+siny;
            if(newx < pixmap.width() && newy < pixmap.height()){
                if(rand1+rand2 > 1) {
                    painter2.setPen(pixmapImg.pixel(newx,newy));
                } else {
                    painter2.setPen(Qt::white);
                    //painter2.drawRect(x,y,10,10);
                }
                painter2.drawRect(x,y,1,1);

            }
        }
    }

    ui->label_captcha->setPixmap(pixmap2);

    return pixmap2;
}
//////////////////////////////////////////////


void signup::on_pushButton_Recaptcha_clicked()
{
    GenCaptcha();
}

