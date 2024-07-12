#include "createjob.h"
#include "ui_createjob.h"
#include "basicclasses.h"
#include "splash.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QByteArray>


createJob::createJob(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createJob)
{
    ui->setupUi(this);
    setWindowTitle("Create post");
}

createJob::~createJob()
{
    delete ui;
}




void createJob::on_create_pushButton_clicked()
{
    //line edits
    QString jobName = ui->jobName_lineEdit->text();
    QString salary = ui->salary_lineEdit->text() + '$';
    QString location = ui->location_lineEdit->text();
    //combo boxes
    QString skill = ui->skill_comboBox->currentText();
    QString workPlaceType = ui->workPlaceType_comboBox->currentText();
    QString type = ui->type_comboBox->currentText();
    int jobCounter;
    QSqlQuery q, q2;

    q2.exec("SELECT CM_jobCounter FROM Users WHERE id = '"+ID+"'");
    if (q2.next()) {
         jobCounter = q2.value(0).toInt() + 1;
    }
/////////////////////////////////skills miss
    q2.exec("UPDATE Users SET CM_jobCounter='"+QString::number(jobCounter)+"' WHERE id='"+ID+"'");
    q.exec("INSERT INTO Jobs (id, jobId, jobName, CM_name, skill, salary, workPlaceType, location, type) VALUES ('"+ID+"', '"+QString::number(jobCounter)+"', '"+jobName+"', '"+CM_name+"', '"+skill+"', '"+salary+"', '"+workPlaceType+"', '"+location+"', '"+type+"')");
    qDebug() << jobCounter;
    this->close();
}

