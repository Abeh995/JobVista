#include "splash.h"
#include "home.h"
#include"basicclasses.h"
#include "createpost.h"

#include "wholiked.h"
#include"viewprofile.h"
#include "comments.h"
#include <QApplication>
#include "createjob.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/icon-logo.png"));

    QSqlDatabase databse;
    databse = QSqlDatabase::addDatabase("QSQLITE");
    databse.setDatabaseName("d:\\JobVista\\Users.db");
    databse.open();
    home w;
    w.show();
    return a.exec();
}
