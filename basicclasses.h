#ifndef BASICCLASSES_H
#define BASICCLASSES_H

#include <QString>
#include <QDateTime>
#include <QList>

extern QString ID;
extern QString PhoneNumber;
extern QString postSenderID;
extern QString postID;
extern QString viewProfileID;
extern QString intendedJob;

QString getTime();

extern QString postType;
extern QString CM_name;

class Time;
class Post;
class Comment;
class Like;
class DirectMessage;
class Content;
class Account;
class Person;
class Job;
class Company;

class Time {
public:
    QString second;
    QString minute;
    QString hour;
    QString day;
    QString month;
    QString year;
};

class Content {
public:
    QString id;
    Time time2;
    QString text;
    QByteArray media;
    QString mediaType;
};

class Post : public Content {
public:
    QByteArray profilePhoto;
    QString postId;
    QString LCR_counter;
    QString tag;
    QString suggested;
    QString seen;
    QString rePosted;
    QList<Like> likes;
    QList<Comment> comments;
};

class Comment : public Content {
public:
    QByteArray profilePhoto;
    QString postId;
    QString commentId;
};

class Like {
public:
    QString id;
    QByteArray profilePhoto;
    QString likeId;
    QString senderId;
    QString postId;
    Time time;
};

class DirectMessage : public Content {
public:
    QString messageId;
    QString recieverId ;
};

class Job;
class Person;

class Account {
public:
    QString id;
    QByteArray profilePhoto;
    QString PhoneNumber;
    QString email;
    int connection_counter;
    QStringList Connection;
    QStringList requests;
    QStringList suggests;
    QString Following;
    QVector<Post> UsersPosts;
    QVector<QString> DirectMessage;
};

class Person : public Account {
public:

    QString name;
    QString lastName;
    QString Skill;
    QString college;
};

class Job {
public:
    Job(const QString& jobName, const QString& companyName, const QString& skillsRequired, const QString& workplaceType, const QString& location, const QString& type, QString salary)
        : Job_Name(jobName), Company_Name(companyName), Skills_Required(skillsRequired), WorkPlace_Type(workplaceType), Location(location), Type(type), Salary(salary) {}
    Job(){}

    QString id;
    QString jobId;
    QString requests;
    QString req_results;
    QString Job_Name;
    QString Company_Name;
    QString Skills_Required;
    QString WorkPlace_Type;
    QString Location;
    QString Type;
    QString Salary;
};

class Company : public Account {
public:

    Job* Create_Job(const QString& jobName, const QString& skillsRequired, const QString& workplaceType, const QString& location, const QString& type, QString salary) {
        Job* job = new Job(jobName, Company_Name, skillsRequired, workplaceType, location, type, salary);
        Company_Jobs.append(job);
        return job;
    }
    QString Company_Name;
    QString occupation;
    QString address;
    QString Followers;
    QVector<Job*> Company_Jobs;
    QVector<Person*> Employee;
};

#endif // BASICCLASSES_H
