#include "directmessage.h"
#include "ui_directmessage.h"

directmessage::directmessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::directmessage)
{
    ui->setupUi(this);
}

directmessage::~directmessage()
{
    delete ui;
}
