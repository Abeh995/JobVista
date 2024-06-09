#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void handleKeyPress(QKeyEvent *event);

    void on_pushButton_3_pressed();

    void on_pushButton_3_released();

private:
    Ui::login *ui;
    QPropertyAnimation *animation;
};

#endif // LOGIN_H
