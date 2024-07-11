#ifndef VIEWPROFILE_H
#define VIEWPROFILE_H

#include <QWidget>

namespace Ui {
class viewprofile;
}

class viewprofile : public QWidget
{
    Q_OBJECT

public:
    explicit viewprofile(QWidget *parent = nullptr);
    ~viewprofile();

private:
    Ui::viewprofile *ui;
};

#endif // VIEWPROFILE_H
