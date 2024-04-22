#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

namespace Ui {
class signup;
}

class signup : public QWidget
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();
protected:
    void keyPressEvent(QKeyEvent *event);
public slots:
    int CheckInformation();
    void GenCaptcha();
private slots:
    void on_pushButton_continue_clicked();
    void handleKeyPress(QKeyEvent *event);
    void on_pushButton_Recaptcha_clicked();

private:
    Ui::signup *ui;
    QPixmap makeImg(QString);
    QPixmap distortImg(QPixmap);
};

#endif // SIGNUP_H
