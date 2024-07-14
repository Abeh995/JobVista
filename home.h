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

    void handleKeyPress(QKeyEvent *event);

    void on_createPost_pushButton_clicked();
   // void onPostInView(int postId);

    void on_createJob_pushButton_clicked();


public slots:
    void generatePost(QGridLayout *scrollLayout);
    void generateJob(QGridLayout *job_scrollLayout);
    void generateNetwork1(QGridLayout *network1_scrollLayout);
    void generateNetwork2(QGridLayout *network2_scrollLayout);
    void changeTheme();
    void onTabChanged(int index);
    QString getTime();
private:
    Ui::home *ui;
    bool  isLiked;
protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // HOME_H
