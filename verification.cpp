#include "verification.h"
#include "ui_verification.h"
#include"basicclasses.h"
#include "signup.h"
#include "splash.h"
#include "home.h"
#include "profile.h"

#include <QPropertyAnimation>
#include <QValidator>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QThread>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>


int random2;
bool swVerify=true, swEnter = false;

verification::verification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::verification)
{
    ui->setupUi(this);
    setWindowTitle("Verify");

    ui->label_code->hide();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(700);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    ui->lineEdit->setValidator(new QIntValidator);
    ui->lineEdit_2->setValidator(new QIntValidator);
    ui->lineEdit_3->setValidator(new QIntValidator);
    ui->lineEdit_4->setValidator(new QIntValidator);

    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->setEnabled(false);

    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit_2->setAlignment(Qt::AlignCenter);
    ui->lineEdit_3->setAlignment(Qt::AlignCenter);
    ui->lineEdit_4->setAlignment(Qt::AlignCenter);
}

verification::~verification()
{
    delete ui;
}

void verification::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
       {
           handleKeyPress(event);
       }
    else if(event->key() == Qt::Key_Escape)
       {
           handleKeyPress_2(event);
       }
    else if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace || (event->modifiers() & Qt::KeypadModifier && event->key() == Qt::Key_Delete)){
        handleKeyPress_3(event);
    }
    else{
        QWidget::keyPressEvent(event);
    }
}

void verification::handleKeyPress(QKeyEvent *event)
{
        if(ui->lineEdit_4->text().length()==0){

            QThread::sleep(2);
            //create 4digit random Num
            int min = 1000;
            int max = 9999;
            random2 = QRandomGenerator::global()->bounded(min, max + 1);

            ui->lineEdit->setEnabled(true);
            ui->lineEdit_2->setEnabled(true);
            ui->lineEdit_3->setEnabled(true);
            ui->lineEdit_4->setEnabled(true);

            ui->lineEdit->setFocus();

            //Sleep for label
            QString text = QString("<div align='center'>%1</div>").arg(random2);
            ui->label_code->setText(text);
            ui->label_code->show();

            animation = new QPropertyAnimation(ui->label_code, "pos");
            animation->setDuration(1000);
            animation->setStartValue(ui->label_code->pos());
            animation->setEndValue(QPoint(250, 60));
            animation->start();

            swEnter = true;
        }
        else{
            on_pushButton_verify_clicked();
        }
}


void verification::handleKeyPress_2(QKeyEvent *event)
{
    signup *SP =new signup;
    SP->show();
    this->close();
}


void verification::verify()
{
    if(swVerify){
//        ui->label->setText("YOU'RE VERIFIED!");

//        mainPage *pg5 = new mainPage;
//        pg5->show();
//        this->close();

    }
    else{
        QMessageBox::warning(this,"wrong code","Wrong Code! try again","OK!");
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);
        ui->label_code->hide();
        ui->lineEdit->setText(NULL);
        ui->lineEdit_2->setText(NULL);
        ui->lineEdit_3->setText(NULL);
        ui->lineEdit_4->setText(NULL);

    }
}

void verification::handleKeyPress_3(QKeyEvent *event)
{
    ui->label_code->setText("HOJAST");
    ui->lineEdit->setText(NULL);
    ui->lineEdit_2->setText(NULL);
    ui->lineEdit_3->setText(NULL);
    ui->lineEdit_4->setText(NULL);
}

void verification::on_pushButton_verify_clicked()
{
    int thousand = random2 / 1000;
    int hundred = random2 / 100 - (thousand * 10);
    int ten = random2 / 10 - (thousand * 100 + hundred * 10);
    int one = random2 - (thousand * 1000 + hundred * 100 + ten * 10);
    if(ui->lineEdit->text().toInt() != thousand){
        swVerify=false;
    }
    else if(ui->lineEdit_2->text().toInt() != hundred){
        swVerify=false;
    }
    else if(ui->lineEdit_3->text().toInt() != ten){
        swVerify=false;
    }
    else if(ui->lineEdit_4->text().toInt() != one){
        swVerify=false;
    }

    verify();
    if(swVerify){
        QSqlQuery q;
         q.exec("UPDATE jobSeekers SET phoneNumber = '"+PhoneNumber+"' WHERE id = '"+ID+"' " ) ;
         profile* window = new profile;
         window->show();
         this->close();
    }
    else{
        swVerify=true;
    }

}

void verification::on_lineEdit_textChanged(const QString &text)
{
    if (text.length() > 1)
    {
        ui->lineEdit->setText(text.left(1));
        return;
    }
    ui->lineEdit_2->setEnabled(true);
    ui->lineEdit_2->setFocus();
}


void verification::on_lineEdit_2_textChanged(const QString &text)
{
    if (text.length() > 1)
    {
        ui->lineEdit_2->setText(text.left(1));
        return;
    }
    if(text.length()==0){
        ui->lineEdit->setFocus();
        return;
    }
    ui->lineEdit_3->setFocus();
}


void verification::on_lineEdit_3_textChanged(const QString &text)
{
    if (text.length() > 1)
    {
        ui->lineEdit_3->setText(text.left(1));
        return;
    }
    if(text.length()==0){
        ui->lineEdit_2->setFocus();
        return;
    }
    ui->lineEdit_4->setFocus();
}


void verification::on_lineEdit_4_textChanged(const QString &text)
{
    if (text.length() > 1)
    {
        ui->lineEdit_4->setText(text.left(1));
        return;
    }
    if(text.length()==0){
        ui->lineEdit_3->setFocus();
        return;
    }

}


