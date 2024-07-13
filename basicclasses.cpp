#include"basicclasses.h"

bool darkTheme = true;
QString ID = "Abeh", PhoneNumber = "123";
QString postSenderID = "Abeh";
QString postID = "22";
QString viewProfileID = "Abeh";

QString getTime(){

    QDateTime dateTime = QDateTime::currentDateTime();

        int year = dateTime.date().year();
        int month = dateTime.date().month();
        int day = dateTime.date().day();
        int hour = dateTime.time().hour();
        int minute = dateTime.time().minute();
        int second = dateTime.time().second();

        QString timeString = QString("%1%2%3%4%5%6")
                .arg(year, 4, 10, QChar('0'))   // Year with 4 digits
                .arg(month, 2, 10, QChar('0'))  // Month with 2 digits
                .arg(day, 2, 10, QChar('0'))    // Day with 2 digits
                .arg(hour, 2, 10, QChar('0'))   // Hour with 2 digits
                .arg(minute, 2, 10, QChar('0')) // Minute with 2 digits
                .arg(second, 2, 10, QChar('0'));// Second with 2 digits
        return timeString;

}
