#ifndef HOME_H
#define HOME_H

#include "basicclasses.h"

#include <QWidget>
#include <QGridLayout>
#include<QGroupBox>
#include <QMediaPlayer>
namespace Ui {
class home;
}

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr);
//    void scrollEvent(QScrollEvent* event) override;

    ~home();

signals:
    //void postInView(int postId);

private slots:
    void on_createPost_pushButton_clicked();
   // void onPostInView(int postId);

public slots:
    void generatePost(QGridLayout *scrollLayout);

    QString getTime();
private:
    Ui::home *ui;
    bool  isLiked;

};

#endif // HOME_H
