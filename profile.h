#ifndef PROFILE_H
#define PROFILE_H

#include <QCloseEvent>
#include <QWidget>

namespace Ui {
class profile;
}

class profile : public QWidget
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();

private slots:
    void on_region_comboBox_activated(int index);

    void on_typeOfPost_comboBox_activated(const QString &arg1);

    void on_changeProfile_pushButton_clicked();

    void on_save_pushButton_clicked();

    void on_yearOfBirth_comboBox_currentTextChanged(const QString &arg1);

    void handleKeyPress(QKeyEvent *event);

public slots:
    void afterSleep();

private:

    QString profilePhotoPath;

    Ui::profile *ui;


protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event);


};

#endif // PROFILE_H
