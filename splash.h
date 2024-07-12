#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>

extern QString ID;
extern QString PhoneNumber;
extern QString postSenderID;
extern QString postID;

QT_BEGIN_NAMESPACE
namespace Ui { class splash; }
QT_END_NAMESPACE

class splash : public QWidget
{
    Q_OBJECT

public:
    splash(QWidget *parent = nullptr);
    ~splash();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:

    void handleKeyPress(QKeyEvent *event);

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_pushButton_6_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_clicked();

private:
    Ui::splash *ui;
};
#endif // SPLASH_H
