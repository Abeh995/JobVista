#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class splash; }
QT_END_NAMESPACE

class splash : public QWidget
{
    Q_OBJECT

public:
    splash(QWidget *parent = nullptr);
    ~splash();

private slots:


    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_pushButton_6_pressed();

    void on_pushButton_2_pressed();

private:
    Ui::splash *ui;
};
#endif // SPLASH_H
