#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class verification;
}

class verification : public QWidget
{
    Q_OBJECT

public:
    explicit verification(QWidget *parent = nullptr);
    ~verification();
public slots:
    void verify();
protected:
     void keyPressEvent(QKeyEvent *event);
private slots:
     void on_lineEdit_textChanged(const QString &arg1);

     void on_lineEdit_2_textChanged(const QString &arg1);

     void on_lineEdit_3_textChanged(const QString &arg1);

     void on_lineEdit_4_textChanged(const QString &arg1);

    void handleKeyPress(QKeyEvent *event);
    void handleKeyPress_2(QKeyEvent *event);
    void handleKeyPress_3(QKeyEvent *event);

    void on_pushButton_verify_clicked();

private:
    Ui::verification *ui;
    QPropertyAnimation *animation;

};
#endif // VERIFICATION_H
