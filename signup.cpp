#include "signup.h"
#include "ui_signup.h"
#include "splash.h"
#include "login.h"

#include <QLineEdit>
#include <QRandomGenerator>
#include <QThread>
#include <QValidator>
#include <QMessageBox>
#include "QTimer"
#include "QFocusEvent"
#include "QPalette"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>

//QString ID;
//QString PhoneNumber;
int swReCaptcha=0,swDatabase = 1, swCaptcha, swPhone = 1;

signup::signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);

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

        ui->comboBox->addItem("");
        ui->comboBox->addItem("54");
        ui->comboBox->addItem("61");
        ui->comboBox->addItem("55");
        ui->comboBox->addItem("57");
        ui->comboBox->addItem("33");
        ui->comboBox->addItem("49");
        ui->comboBox->addItem("91");
        ui->comboBox->addItem("98");
        ui->comboBox->addItem("1");

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
    bool num=true,letter=true, shape=false;
//    for(int i=0;Password!='\0';i++){
//        if(Password[i]>=48&&Password[i]<=57) num= true;
//                else if((Password[i]>='A'&& Password[i]<='Z') || (Password[i]>='a'&& Password[i]<='z')) letter= true;
//                            else if(Password[i]=='!' || Password[i]=='@' || Password[i]=='#' || Password[i]== '$' ) shape =true;
//    }
    if(num && letter ){
        q.exec("INSERT INTO jobSeekers(id, password, phoneNumber) VALUES ('"+ID+"', '"+Password+"','"+PhoneNumber+"')");
        if(shape ){
           return 0;
        }
        else return 3;
    }
    else return 4;
}

void signup::on_pushButton_continue_clicked()
{
    if(ui->lineEdit_username->text() == NULL ){
        QMessageBox::warning(this,"Empty Form","Please Fill username form first!");
    }
    else if(ui->lineEdit_password->text()==NULL){
        QMessageBox::warning(this,"Empty Form","Please Fill password form first!");
    }
    else if(ui->lineEdit_phonenumber->text()==NULL){
        QMessageBox::warning(this,"Empty Form","Please Enter your PhoneNumber first!");
    }
    else if(ui->comboBox->currentText()== " "){
        QMessageBox::warning(this,"Empty Form","Please Select your country code aslo!");
    }
    else if(1==2){ /////////                  check captcha!
        QMessageBox::warning(this,"Wrong captcha","Please Enter captcha code correctly!");
        // change captcha  again
    }
    else{
        int CI = CheckInformation();
        if(CI==0) {
            //show a message not in box
//            Verification *vr = new Verificitaion;
//            vr->show();
//            this->close();
        }
            else if(CI==3){
                QMessageBox::information(this, "simple password", "your password is not really safe, you can change it later!");
            }
                else if(CI==1){
            QMessageBox::warning(this,
                                 "Taken Username!",
                                 "<ul>"
                                 "<li>"
                                 "The Entered UserName Already Taken!"
                                 "</li>"
                                 "</ul>");
                }
                    else if(CI==2) {
                        QMessageBox::warning(this,
                                             "Taken PhoneNumber!",
                                             "<ul>"
                                             "<li>"
                                             "The Entered PhoneNumber Already Exist!"
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

