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

QString getTime();

// Forward Declarations
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

// Time class
class Time {
public:
    QString second;
    QString minute;
    QString hour;
    QString day;
    QString month;
    QString year;
};

// Content class
class Content {
public:
    QString id;
    Time time2;
    QString text;
    QByteArray media; // Assuming picture is stored as QByteArray
    QString mediaType; // Assuming video is stored as QByteArray
};

// Post class
class Post : public Content {
public:
    QByteArray profilePhoto;
    QString postId;
    QString LCR_counter;
    QString tag;
    QString seen;
    QString rePosted;
    QList<Like> likes;
    QList<Comment> comments;
};

// Comment class
class Comment : public Content {
public:
    QString postId;
    QString commentId;
};

// Like class
class Like {
public:
    QString id;
    QByteArray profilePhoto;
    QString likeId;
    QString senderId;
    QString postId;
    Time time;
};

// DirectMessage class
class DirectMessage : public Content {
public:
    QString messageId;
    QString recieverId ;
};




// Forward declarations
class Job;
class Person;

class Account {
public:
    // Other member functions here...
    QString id;
    QByteArray profilePhoto;
    QString PhoneNumber;
    QString email;
    int connection_counter;
    QVector<Account*> Connection;
    QString Following;
    QVector<Post> UsersPosts; // Assuming post is represented as QString for simplicity
    QVector<QString> DirectMessage;    // Assuming message is represented as QString for simplicity
};

class Person : public Account {
public:


    //void Take_Job(Job* job);

    // Other member functions here...

    QString name;
    QString lastName;
    QString Skill;
    QString college;
};

class Job {
public:
    Job(const QString& jobName, const QString& companyName, const QVector<QString>& skillsRequired, const QString& workplaceType, const QString& location, const QString& type, QString salary)
        : Job_Name(jobName), Company_Name(companyName), Skills_Required(skillsRequired), WorkPlace_Type(workplaceType), Location(location), Type(type), Salary(salary) {}

    // Other member functions here...

    QString Job_Name;
    QString Company_Name;
    QVector<QString> Skills_Required;
    QString WorkPlace_Type;
    QString Location;
    QString Type;
    QString Salary;
};

class Company : public Account {
public:

    Job* Create_Job(const QString& jobName, const QVector<QString>& skillsRequired, const QString& workplaceType, const QString& location, const QString& type, QString salary) {
        Job* job = new Job(jobName, Company_Name, skillsRequired, workplaceType, location, type, salary);
        Company_Jobs.append(job);
        return job;
    }

    // Other member functions here...
    QString Company_Name;
    QString occupation;
    QString address;
    QString Followers;
    QVector<Job*> Company_Jobs;
    QVector<Person*> Employee;
};

//void Person::Take_Job(Job* job) {
//    // Implement the logic for a person taking a job
//}

#endif // BASICCLASSES_H
