#include "login.h"
#include "ui_login.h"
#include "splash.h"
#include "signup.h"
#include "home.h"


#include <QMessageBox>
#include <QKeyEvent>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>



login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    setWindowTitle("Login");
    animation = new QPropertyAnimation(ui->groupBox, "geometry");
    animation->setDuration(550);
    animation->setStartValue(ui->groupBox->geometry());
    animation->setEndValue(QRect(400, 10, 450, 600));
    animation->start();
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}

void login::keyPressEvent(QKeyEvent *event)
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

void login::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text( ) != NULL && ui->lineEdit_2->text() != NULL ){
            QSqlQuery q;
            ID = ui->lineEdit->text();
            q.exec("SELECT password FROM jobSeekers WHERE id = '"+ID+"'");
            if(q.first()){
               QString  Password = q.value(0).toString();
               QString enterdPass = ui->lineEdit_2->text();
                if(Password == enterdPass){
                    home *pg4 = new home;
                    pg4->show();
                    this->close();
                }
                else{
                        QMessageBox msgBox;
                        msgBox.setIcon(QMessageBox::Warning);
                        msgBox.setWindowTitle("Error");
                        msgBox.setText("Wrong information!");
                        msgBox.setStandardButtons(QMessageBox::Ok);

                        msgBox.setStyleSheet("QMessageBox { background-color: #333333; }"
                                             "QMessageBox QLabel { color: #aaa; }"
                                             "QMessageBox QPushButton { background-color: #555555; color: #fff; }");
                        int ret = msgBox.exec();

                            // Handle the response
                            switch (ret) {
                              case QMessageBox::Ok:
                                  // Ok was clicked
                                  break;}
                        //QMessageBox::warning(this, "Error", "Wrong information!");
                }
            }
            else{
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Error");
                msgBox.setText("Wrong information!");
                msgBox.setStandardButtons(QMessageBox::Ok);

                msgBox.setStyleSheet("QMessageBox { background-color: #333333; }"
                                     "QMessageBox QLabel { color: #aaa; }"
                                     "QMessageBox QPushButton { background-color: #555555; color: #fff; }");
                int ret = msgBox.exec();

                    // Handle the response
                    switch (ret) {
                      case QMessageBox::Ok:
                          // Ok was clicked
                          break;}
            }
        }
        else{
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Empty Form!");
        msgBox.setText("Please<b> fill </b>all fields!");
        msgBox.setStandardButtons(QMessageBox::Ok);

        msgBox.setStyleSheet("QMessageBox { background-color: #333333; }"
                             "QMessageBox QLabel { color: #aaa; }"
                             "QMessageBox QPushButton { background-color: #555555; color: #fff; }");
        int ret = msgBox.exec();

            // Handle the response
            switch (ret) {
              case QMessageBox::Ok:
                  // Ok was clicked
                  break;}

        }
}


void login::on_pushButton_clicked()
{
    signup *SP =new signup;
    SP->show();
    this->close();
}

void login::handleKeyPress(QKeyEvent *event)
{
    splash *sp=new splash;
    sp->show();
    this->close();
}


void login::on_pushButton_3_pressed()
{
    ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
}


void login::on_pushButton_3_released()
{
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

