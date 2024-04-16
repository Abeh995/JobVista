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
private slots:
    void on_pushButton_continue_clicked();
    void handleKeyPress(QKeyEvent *event);
private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
