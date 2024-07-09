#include "splash.h"
#include "ui_splash.h"
#include "login.h"
#include "verification.h"
#include "home.h"

#include "QPushButton"
#include "QKeyEvent"

QString ID = "Abeh", PhoneNumber = "123";

bool swText1 = true ,swText2 = true ,swText3 = true;

splash::splash(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::splash)
{
    ui->setupUi(this);

    setWindowTitle("Splash");
    ui->pushButton_3->setFocus();
    ui->pushButton_3->setDefault(true);
    ui->pushButton_3->setAutoDefault(false);

    ui->textBrowser->hide();
    ui->textBrowser_2->hide();
    ui->textBrowser_3->hide();
    ui->pushButton_4->resize(150, 25);
    ui->label_5->hide();
    ui->label_6->hide();

}

splash::~splash()
{
    delete ui;
}

void splash::keyPressEvent(QKeyEvent *event)
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

void splash::handleKeyPress(QKeyEvent *event)
{
    this->close();
}





void splash::on_pushButton_4_pressed()
{
    if(swText1 == false){
        ui->textBrowser->hide();
        swText1 = true;
    }
    else{
        ui->textBrowser->show();
        swText1 = false;
    }
}


void splash::on_pushButton_5_pressed()
{
    if(swText2 == false){
        ui->textBrowser_2->hide();
        swText2 = true;
    }
    else{
        ui->textBrowser_2->show();
        swText2 = false;
    }
}


void splash::on_pushButton_6_pressed()
{
    if(swText3 == false){
        ui->textBrowser_3->hide();
        swText3 = true;
    }
    else{
        ui->textBrowser_3->show();
        swText3 = false;
    }
}


void splash::on_pushButton_2_pressed()
{

}


void splash::on_pushButton_3_clicked()
{
    login *pg2 = new login;
    pg2->show();
    this->close();
}

