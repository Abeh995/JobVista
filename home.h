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

public slots:
    void generatePost(QGridLayout *scrollLayout);

    QString getTime();
private:
    Ui::home *ui;
    bool  isLiked;
};

#endif // HOME_H
