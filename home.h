#ifndef HOME_H
#define HOME_H

#include "basicclasses.h"

#include <QWidget>
#include <QGridLayout>

namespace Ui {
class home;
}

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr);
    ~home();

private slots:
    void on_createPost_pushButton_clicked();

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
};

#endif // HOME_H
