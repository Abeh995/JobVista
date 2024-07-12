#include "profile.h"
#include "ui_profile.h"
#include "splash.h"
#include "verification.h"
#include "home.h"
#include "basicclasses.h"
#include "QTimer"
#include "QMessageBox"
#include "QDebug"
#include "QSqlError"
#include <QFileDialog>
#include <QBuffer>

#include <QSqlDatabase>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

QString filePath, imagePath ;
profile::profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);

    setWindowTitle("Set Profile");

    // check the user's information & get the window ready
    QSqlQuery q;
    q.prepare("SELECT profilePhoto FROM Users WHERE id = :id");
    q.bindValue(":id", ID);
    if(q.exec()){
        if(q.next()){
            QByteArray imageData = q.value(0).toByteArray();
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
                    // Save pixmap to a file
                    imagePath = QDir::homePath() + "/profilePhoto.png";
                    if(pixmap.save(imagePath)){
                        // Set the image on the button using styleSheet
                        ui->changeProfile_pushButton->setStyleSheet(QString("QPushButton {border-image: url(%1); border-radius:55px;}").arg(imagePath));
                    }
                    else{
                        // Handle error if saving failed
                        qDebug() << "Error saving image file";
                    }
                }
            }
            else{
                // Handle the error
                qDebug() << "Error retrieving profile photo:" << q.lastError().text();
            }

    q.exec("SELECT id FROM Users Where id=='"+ID+"'");
    if(q.first()) ui->id_label->setText(q.value(0).toString());

    q.exec("SELECT name FROM Users WHERE id='" +ID+"'");
    if(q.first()){
        if(q.value(0).toString() != NULL){
            ui->name_lineEdit->setText(q.value(0).toString());
        }
    }
    q.exec("SELECT lastName FROM Users WHERE id='"+ID+"'");
    if(q.first()){
        if(q.value(0).toString() != NULL){
            ui->lastName_lineEdit->setText(q.value(0).toString());
        }
    }
    q.exec("SELECT phoneNumber FROM Users WHERE id='"+ID+"'");
    if(q.first()){
        if(q.value(0).toString() == NULL){
            ui->phoneNumber_lineEdit->setEnabled(false);
        }
        else{
            QStringList parts = q.value(0).toString().split('-');
            ui->region_comboBox->setCurrentText(parts[0]);
            ui->phoneNumber_lineEdit->setText(parts[1]);
        }
    }

    ui->yearOfBirth_comboBox->addItem("");
    for(int comboYear = 1940; comboYear <= 2023; comboYear++){
        ui->yearOfBirth_comboBox->addItem(QString::number(comboYear));
    }
    q.exec("SELECT birthDate FROM Users WHERE id='"+ID+"'");
    if(q.first()){
        QStringList dateParts = q.value(0).toString().split('/');
        ui->monthOfBirth_comboBox->setCurrentText(dateParts[0]);
        ui->dayOfBirth_comboBox->setCurrentText(dateParts[1]);
        //ui->id_label->setText(dateParts[2]);
        // not Working correctly:
        ui->yearOfBirth_comboBox->setCurrentText(dateParts[2]);
        // can you fix that? :)
    }
    ui->liveAgeShower_label->setNum(2024-ui->yearOfBirth_comboBox->currentText().toInt());
    q.exec("SELECT post FROM Users WHERE id='"+ID+"'");
    if(q.first()){
        if(q.value(0).toString() == "Employer"){
            ui->jobSeekers_groupBox->setDisabled(true);
            ui->typeOfPost_comboBox->setCurrentText("Employer");
            ui->typeOfPost_comboBox->setEnabled(false);
            q.exec("SELECT CM_name FROM Users WHERE id='"+ID+"'");
            //qDebug() << "2Post value: " << q.value(0).toString();
            if(q.first()){
                ui->companyName_lineEdit->setText(q.value(0).toString());
            }
            q.exec("SELECT CM_address FROM Users WHERE id='"+ID+"'");
            if(q.first()){
                ui->companyAddress_lineEdit->setText(q.value(0).toString());
            }
            q.exec("SELECT CM_occupation FROM Users WHERE id='"+ID+"'");
            if(q.first()){
                ui->fieldOfOccupation_comboBox->setCurrentText(q.value(0).toString());
            }
        }
        else if(q.value(0).toString() =="JobSeeker"){
            ui->employers_groupBox->setDisabled(true);
            ui->typeOfPost_comboBox->setCurrentText("JobSeeker");
            ui->typeOfPost_comboBox->setEnabled(false);
            q.exec("SELECT JS_college FROM Users WHERE id='"+ID+"'");
            //qDebug() << "2=3Post value: " << q2.value(0).toString();
            if(q.first()){
                ui->nameOfCollege_lineEdit->setText(q.value(0).toString());
            }
            q.exec("SELECT JS_intended_J FROM Users WHERE id='"+ID+"'");
            if(q.first()){
                ui->intendedJob_comboBox->setCurrentText(q.value(0).toString());
            }
            q.exec("SELECT JS_intended_C FROM Users WHERE id='"+ID+"'");
            if(q.first()){
                ui->intendedCompany_comboBox->setCurrentText(q.value(0).toString());
            }
        }
        else {
            //ui->typeOfPost_comboBox->setEnabled(true);
            ui->employers_groupBox->setEnabled(false);
            ui->jobSeekers_groupBox->setEnabled(false);
        }
    }

    ui->phoneNumber_lineEdit->setValidator( new QIntValidator);
}

profile::~profile()
{
    delete ui;
}

void profile::on_region_comboBox_activated(int index)
{
    switch (index) {
    case 0:
        ui->phoneNumber_lineEdit->setPlaceholderText("Select your Region First!");
        ui->phoneNumber_lineEdit->setEnabled(false);
        break;
    case 1:
        ui->phoneNumber_lineEdit->setPlaceholderText("Iran");
        ui->phoneNumber_lineEdit->setEnabled(true);
        break;
    case 2:
        ui->phoneNumber_lineEdit->setPlaceholderText("United States");
        ui->phoneNumber_lineEdit->setEnabled(true);
        break;
    case 3:
        ui->phoneNumber_lineEdit->setPlaceholderText("India");
        ui->phoneNumber_lineEdit->setEnabled(true);
        break;
    case 4:
        ui->phoneNumber_lineEdit->setPlaceholderText("Germany");
        ui->phoneNumber_lineEdit->setEnabled(true);
        break;
    case 5:
        ui->phoneNumber_lineEdit->setPlaceholderText("France");
        ui->phoneNumber_lineEdit->setEnabled(true);
        break;
    case 6:
        ui->phoneNumber_lineEdit->setPlaceholderText("Colombia");
        ui->phoneNumber_lineEdit->setEnabled(true);
        break;
    case 7:
        ui->phoneNumber_lineEdit->setPlaceholderText("Brazil");
        ui->phoneNumber_lineEdit->setEnabled(true);
        break;
    case 8:
        ui->phoneNumber_lineEdit->setPlaceholderText("Australia");
        ui->phoneNumber_lineEdit->setEnabled(true);
        break;
    case 9:
        ui->phoneNumber_lineEdit->setPlaceholderText("Argentina");
        ui->phoneNumber_lineEdit->setEnabled(true);
        break;
    }
}



void profile::on_typeOfPost_comboBox_activated(const QString &arg1)
{
    if(arg1 != ""){
        if(arg1 =="Employer"){
            ui->employers_groupBox->setEnabled(true);
            ui->jobSeekers_groupBox->setEnabled(false);
        }
        else{
            ui->jobSeekers_groupBox->setEnabled(true);
            ui->employers_groupBox->setEnabled(false);
        }
    }
    else {
        ui->jobSeekers_groupBox->setEnabled(false);
        ui->employers_groupBox->setEnabled(false);
    }

}

void profile::on_changeProfile_pushButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, tr("Select Profile Photo"), QDir::homePath(), tr("Image Files (*.png *.jpg *.jpeg)"));
    if(!filePath.isEmpty()){
        ui->changeProfile_pushButton->setStyleSheet( QString("QPushButton {border-image: url(%1); border-radius:55px;}").arg(filePath));
        //ui->changeProfile_pushButton->setStyleSheet("QPushButton:hover {image: url(:/icon/icon-change-profile-photo.png);border-radius:55px;}");
    }

    QSqlQuery q;
    q.prepare("UPDATE Users SET profilePhoto =  :photo WHERE id = :id");
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray imageData = file.readAll();
        q.bindValue(":photo", imageData);
        q.bindValue(":id", ID);
        if(!q.exec()){
            // Handle the error
            qDebug() << "Error updating profile photo:" << q.lastError().text();
        }
    }
    else{
        // Handle the error if the file can't be opened
        qDebug() << "Error opening image file:" << file.errorString();
    }
}

void profile::afterSleep()
{
    ui->save_pushButton->setMaximumWidth(55);
    ui->save_pushButton->setStyleSheet("QPushButton:hover{ font-size:30px; color: rgb(255, 0, 0); }"
                                       "QPushButton { color: rgb(0, 0, 255); background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(0, 0, 0, 0)); border-radius:20px;}");
    ui->save_pushButton->setText("Save!");
}

void profile::on_save_pushButton_clicked()
{
    //check empty fields
    bool empty=false;
    if(ui->name_lineEdit->text()=="" || ui->lastName_lineEdit->text()=="" || ui->phoneNumber_lineEdit->text()=="" || ui->typeOfPost_comboBox->currentText()== "" ||
            ui->dayOfBirth_comboBox->currentText()=="" || ui->monthOfBirth_comboBox->currentText() == "" || ui->yearOfBirth_comboBox->currentText() == "" ||
            ui->typeOfPost_comboBox->currentText() == "" || ui->region_comboBox->currentText() == "" ) empty=true;
            //else empty=false;
    if(ui->typeOfPost_comboBox->currentText() == "Employer"){
        if(ui->companyName_lineEdit->text()=="" || ui->companyAddress_lineEdit->text()=="" || ui->fieldOfOccupation_comboBox->currentText() == "") empty=true;
        //else empty =false;
    }
    else if(ui->typeOfPost_comboBox->currentText() == "JobSeeker"){
        if(ui->nameOfCollege_lineEdit->text()=="" || ui->intendedJob_comboBox ->currentText() == "" ||ui->intendedCompany_comboBox->currentText() == "") empty=true;
        //else empty=false;
    }
    else empty = true;
    if(empty){
        QMessageBox::warning(this, "Empty Fields!", "please fill empty fields!");
        empty=false;
    }
    else{
        //save to DB
        QSqlQuery q;
        q.exec("UPDATE Users SET name= '"+ui->name_lineEdit->text()+"' WHERE id='"+ID+"'");
        q.exec("UPDATE Users SET lastName='"+ui->lastName_lineEdit->text()+"' WHERE id='"+ID+"'");
        q.exec("UPDATE Users SET phoneNumber='"+ui->region_comboBox->currentText()+"-"+ui->phoneNumber_lineEdit->text()+"' WHERE id='"+ID+"'");
        q.exec("UPDATE Users SET birthDate='"+ui->monthOfBirth_comboBox->currentText()+"/"+ui->dayOfBirth_comboBox->currentText()+"/"+ui->yearOfBirth_comboBox->currentText()+"' WHERE id='"+ID+"'");
        q.exec("UPDATE Users SET post='"+ui->typeOfPost_comboBox->currentText()+"' WHERE id='"+ID+"'");
        if(ui->typeOfPost_comboBox->currentText() == "Employer"){
            CM_name = ui->companyName_lineEdit->text();
            postType = "Employer";
            q.exec("UPDATE Users SET CM_name='"+ui->companyName_lineEdit->text()+"' WHERE id='"+ID+"'");
            q.exec("UPDATE Users SET CM_address='"+ui->companyAddress_lineEdit->text()+"' WHERE id='"+ID+"'");
            q.exec("UPDATE Users SET CM_occupation='"+ui->fieldOfOccupation_comboBox->currentText()+"' WHERE id='"+ID+"'");
        }
        else{// Job Seeker
            postType = "Job seeker";
            q.exec("UPDATE Users SET JS_college='"+ui->nameOfCollege_lineEdit->text()+"' WHERE id='"+ID+"'");
            q.exec("UPDATE Users SET JS_intended_J='"+ui->intendedJob_comboBox->currentText()+"' WHERE id='"+ID+"'");
            q.exec("UPDATE Users SET JS_intended_C='"+ui->intendedCompany_comboBox->currentText()+"' WHERE id='"+ID+"'");
        }
        ui->save_pushButton->setMaximumWidth(70);
        ui->save_pushButton->setStyleSheet("color: rgb(255, 0, 0);");
        ui->save_pushButton->setText("Saved!");
        QTimer::singleShot(1500, this, SLOT(afterSleep()));
    }
}

void profile::on_yearOfBirth_comboBox_currentTextChanged(const QString &arg1)
{
    ui->liveAgeShower_label->setNum(2024-arg1.toInt());
}

void profile::closeEvent(QCloseEvent *event)
{
    QString imagePath = QDir::homePath() + "/profilePhoto.png";
    if(QFile::exists(imagePath)){
        if(!QFile::remove(imagePath)){
            // Handle error if deletion failed
            qDebug() << "Error deleting image file";
        }
    }
    // Call the base class implementation of closeEvent
    QWidget::closeEvent(event);
}

