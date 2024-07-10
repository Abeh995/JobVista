#ifndef WHOLIKED_H
#define WHOLIKED_H

#include <QWidget>

namespace Ui {
class wholiked;
}

class wholiked : public QWidget
{
    Q_OBJECT

public:
    explicit wholiked(QWidget *parent = nullptr);
    ~wholiked();

private:
    Ui::wholiked *ui;
};

#endif // WHOLIKED_H
