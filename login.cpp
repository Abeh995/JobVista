#include "login.h"
#include "ui_login.h"
#include "splash.h"
#include "signup.h"

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

    setWindowTitle("login");
    animation = new QPropertyAnimation(ui->groupBox, "geometry");
    animation->setDuration(550);
    animation->setStartValue(ui->groupBox->geometry());
    animation->setEndValue(QRect(400, 10, 450, 600));
    animation->start();
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
//                    mainPage *pg4 = new mainPage;
//                    pg4->show();
//                    this->close();
                }
                else{
                    QMessageBox::warning(this, "Error", "Wrong information!");
                }
            }
            else{
                QMessageBox::warning(this, "Error", "Wrong information!");
            }
        }
        else{
            QMessageBox::information(this,"Fill Form","Please FILL FORM and try again!");
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

