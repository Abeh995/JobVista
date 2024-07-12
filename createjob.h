#ifndef CREATEJOB_H
#define CREATEJOB_H

#include <QWidget>

namespace Ui {
class createJob;
}

class createJob : public QWidget
{
    Q_OBJECT

public:
    explicit createJob(QWidget *parent = nullptr);
    ~createJob();


private slots:
    void on_create_pushButton_clicked();

private:
    Ui::createJob *ui;
};

#endif // CREATEJOB_H
