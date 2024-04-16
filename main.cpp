#include "splash.h"

#include <QApplication>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase databse;
    databse = QSqlDatabase::addDatabase("QSQLITE");
    databse.setDatabaseName("d:\\JobVista\\Users.db");
    databse.open();
    splash w;
    w.show();
    return a.exec();
}
