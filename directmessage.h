#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H

#include <QWidget>

namespace Ui {
class directmessage;
}

class directmessage : public QWidget
{
    Q_OBJECT

public:
    explicit directmessage(QWidget *parent = nullptr);
    ~directmessage();

private:
    Ui::directmessage *ui;
};

#endif // DIRECTMESSAGE_H
