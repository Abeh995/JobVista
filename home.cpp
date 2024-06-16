#include "home.h"
#include "ui_home.h"
#include <QApplication>
#include <QTabWidget>
#include <QTabBar>
#include <QStyleOptionTab>
#include <QToolBar>
#include <QMainWindow>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>



/* home:
#include <QtWidgets>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    QMainWindow mainWindow;
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainWindow.setCentralWidget(centralWidget);

    // Create a scroll area
    QScrollArea *scrollArea = new QScrollArea;
    QWidget *containerWidget = new QWidget;
    QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);
    scrollArea->setWidget(containerWidget);

    // Create and add 10 QGroupBox widgets
    for (int i = 1; i <= 10; ++i) {
        QGroupBox *groupBox = new QGroupBox(QString("Group Box %1").arg(i));
        QVBoxLayout *groupBoxLayout = new QVBoxLayout(groupBox);
        QLabel *label = new QLabel(QString("Content for Group Box %1").arg(i));
        groupBoxLayout->addWidget(label);
        containerLayout->addWidget(groupBox);
    }

    // Add the scroll area to the main layout
    mainLayout->addWidget(scrollArea);

    // Show the main window
    mainWindow.show();

    return app.exec();
}
*/





//my net:



home::home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home)
{
    ui->setupUi(this);



    // home:

    // Create a Widget to contain the group boxes
    QWidget* scrollWidget = new QWidget;
    QGridLayout* scrollLayout = new QGridLayout(scrollWidget);



    for(int i=0; i<10; i++){
        //post groupBox

        QGroupBox* post_groupBox = new QGroupBox("suggested");
        post_groupBox->setMinimumHeight(500);
        post_groupBox->setMaximumSize(700, 16777215);
        QVBoxLayout* post_groupBoxLayout = new QVBoxLayout;
        post_groupBox->setLayout(post_groupBoxLayout);

        //Info groupBox

        QGroupBox* info_groupBox = new QGroupBox;
        info_groupBox->setMaximumHeight(70);
        QHBoxLayout* info_groupboxLayout = new QHBoxLayout;
        info_groupBox->setLayout(info_groupboxLayout);

        QFrame* profile_frame = new QFrame;
        profile_frame->setMinimumSize(50, 50);
        profile_frame->setMaximumSize(50, 50);
        info_groupboxLayout->addWidget(profile_frame);
        profile_frame->setStyleSheet("border-image: url(:/icon/icon-logo.png); border-radius: 25px;");

        QLabel* id_label = new QLabel;
        id_label->setText("hiiii");
        info_groupboxLayout->addWidget(id_label);

        QSpacerItem* info_horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
        info_groupboxLayout->addSpacerItem(info_horizontalSpacer);

        QPushButton* follow_pushButton = new QPushButton;
        follow_pushButton->setMinimumSize(0, 44);
        follow_pushButton->setMaximumSize(110, 16777215);
        QFont font("Pristina", 17);
        follow_pushButton->setFont(font);
        follow_pushButton->setText("+follow");
        follow_pushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); color: rgb(41, 69, 255); border-radius: 20px;");
        info_groupboxLayout->addWidget(follow_pushButton);

        post_groupBoxLayout->addWidget(info_groupBox);

        //Media groupBox

        QGroupBox* media_groupBox = new QGroupBox;
        QVBoxLayout* media_groupBoxLayout = new QVBoxLayout;
        media_groupBox->setLayout(media_groupBoxLayout);

        QLabel* postImage_label = new QLabel;
        postImage_label->setMinimumHeight(450);
        postImage_label->setMaximumSize(750, 1000);

        postImage_label->setStyleSheet("border-image: url(:/icon/icon-logo.png);");
        media_groupBoxLayout->addWidget(postImage_label);

        QLabel* text_label = new QLabel;
        text_label->setWordWrap(true);
        text_label->setText("hiii plz like comment and subscribe meeeeee");
        media_groupBoxLayout->addWidget(text_label);

        post_groupBoxLayout->addWidget(media_groupBox);

        //SeeMore groupBox

        QGroupBox* seeMore_groupBox = new QGroupBox;
        QHBoxLayout* seeMore_groupBoxLayout = new QHBoxLayout;
        seeMore_groupBox->setLayout(seeMore_groupBoxLayout);


        QSpacerItem* left_horizontalSpacer = new QSpacerItem(347, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
        seeMore_groupBoxLayout->addSpacerItem(left_horizontalSpacer);

        QPushButton* seeMore_pushButton = new QPushButton;
        seeMore_pushButton->setText("see more");
        seeMore_pushButton->setMinimumSize(70, 0);
        seeMore_pushButton->setMaximumWidth(75);
        seeMore_pushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius:10px; color: rgb(161, 161, 161);");
        seeMore_groupBoxLayout->addWidget(seeMore_pushButton);

        post_groupBoxLayout->addWidget(seeMore_groupBox);

        //Button groupBox

        QGroupBox* button_groupBox = new QGroupBox;
        QVBoxLayout* button_groupBoxLayout = new QVBoxLayout;
        button_groupBox->setLayout(button_groupBoxLayout);

        QSpacerItem* button_horizontalSpacer = new QSpacerItem(20, 40, QSizePolicy::Fixed, QSizePolicy::Expanding);
        button_groupBoxLayout->addSpacerItem(button_horizontalSpacer);

        QGroupBox* counter_groupBox = new QGroupBox;
        QHBoxLayout* counter_groupBoxLayout = new QHBoxLayout;
        counter_groupBox->setLayout(counter_groupBoxLayout);

        QPushButton* whoLikedPushButton = new QPushButton;
        whoLikedPushButton->setText("? and 30 more liked");
        whoLikedPushButton->setMinimumSize(110, 20);
        whoLikedPushButton->setMaximumSize(150, 30);
        whoLikedPushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius:10px;");
        counter_groupBoxLayout->addWidget(whoLikedPushButton);

        QSpacerItem* counter_horizontalSpacer = new QSpacerItem(220, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
        counter_groupBoxLayout->addSpacerItem(counter_horizontalSpacer);

        QLabel* commentAndRepostCounterLabel = new QLabel;
        commentAndRepostCounterLabel->setText("?comment ? repost");
        commentAndRepostCounterLabel->setMinimumSize(110, 20);
        commentAndRepostCounterLabel->setMaximumSize(150, 30);
        counter_groupBoxLayout->addWidget(commentAndRepostCounterLabel);

        button_groupBoxLayout->addWidget(counter_groupBox);

        QGroupBox* react_groupBox = new QGroupBox;
        QHBoxLayout* react_groupBoxLayout = new QHBoxLayout;
        react_groupBox->setLayout(react_groupBoxLayout);

        QPushButton* likePushButton = new QPushButton;
        QFont font2("MS Shell Dlg 2", 23);
        likePushButton->setMinimumSize(0, 50);
        likePushButton->setFont(font2);
        likePushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        likePushButton->setText("🩷");
        react_groupBoxLayout->addWidget(likePushButton);

        QPushButton* commentPushButton = new QPushButton;
        commentPushButton->setMinimumSize(0, 50);
        commentPushButton->setFont(font2);
        commentPushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        commentPushButton->setText("🗨️");
        react_groupBoxLayout->addWidget(commentPushButton);

        QPushButton* repostPushbutton = new QPushButton;
        repostPushbutton->setMinimumSize(0, 50);
        repostPushbutton->setFont(font2);
        repostPushbutton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        repostPushbutton->setText("🔁");
        react_groupBoxLayout->addWidget(repostPushbutton);

        QPushButton* sendPushButton = new QPushButton;
        sendPushButton->setMinimumSize(0, 50);
        sendPushButton->setFont(font2);
        sendPushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
        sendPushButton->setText("📤");
        react_groupBoxLayout->addWidget(sendPushButton);

        button_groupBoxLayout->addWidget(react_groupBox);
        post_groupBoxLayout->addWidget(button_groupBox);

        //Comment pushButton
//
//        //???????????????
//        groupBoxLayout->addWidget(commentPushButton, 5, 0);

        //Like pushButton
//
//        likePushButton->setFont(font);
//        likePushButton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
//        likePushButton->setText("🩷");
//        //????????????????
//        groupBoxLayout->addWidget(likePushButton, 3, 0, -1, 4);

        //Repost pushButton
//        QPushButton* repostPushbutton = new QPushButton;
//        repostPushbutton->setMinimumSize(0, 50);
//        repostPushbutton->setFont(font);
//        repostPushbutton->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0)); border-radius: 20px;");
//        repostPushbutton->setText("🔁");
//        //?????????????????
//        groupBoxLayout->addWidget(repostPushbutton, 0, 0, -1, 4);

        //Send pushButton
//
//        //??????????????????
//        groupBoxLayout->addWidget(sendPushButton, 5, 2);

        //Who liked pushButton
//        QPushButton* whoLikedPushButton = new QPushButton;
//        whoLikedPushButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
//        //???????: horstrech, verstrech
//        whoLikedPushButton->setText("who liked");
//        groupBoxLayout->addWidget(whoLikedPushButton, 1, 0, 2, 4);

        //CmtAndRepo counter label
//        QLabel* cmtAndRepoCounterLabel = new QLabel;
//        cmtAndRepoCounterLabel->setText("comments & reposts counter");
//        cmtAndRepoCounterLabel->setWordWrap(false);
//        groupBoxLayout->addWidget(cmtAndRepoCounterLabel, 5, 3);

//        //Text label
//        QLabel* textLabel = new QLabel;
//        textLabel->setText("test");
//        groupBoxLayout->addWidget(textLabel, 4, 3);

//        //Media label
//        QLabel* mediaLabel = new QLabel;
//        mediaLabel->setMinimumSize(0, 300);
//        mediaLabel->setStyleSheet("border-image: url(:/icon/icon-logo.png);");



        scrollLayout->addWidget(post_groupBox);
    }


    // Set the layout of the scroll widget
    scrollWidget->setLayout(scrollLayout);

    // Set the scroll widget as the widget for the scroll area
    ui->scrollArea->setWidget(scrollWidget);








    //mynetwork:
//    QWidget *mainWidget = new QWidget;

//    QTabWidget *tabWidget = new QTabWidget;
//    tabWidget->addTab(new QWidget, "Home");
//    tabWidget->addTab(new QWidget, "Work");
//    // ... Add other tabs as needed

//    QLineEdit *searchLineEdit = new QLineEdit;
//    searchLineEdit->setPlaceholderText("Search");

//    QHBoxLayout *hBoxLayout = new QHBoxLayout;
//    hBoxLayout->addWidget(tabWidget);
//    hBoxLayout->addWidget(searchLineEdit);


//    mainWidget->setLayout(hBoxLayout);

//    QMainWindow *window = new QMainWindow;
//    window->setCentralWidget(mainWidget);


//    QMainWindow *window = new QMainWindow;
//        QWidget *mainWidget = new QWidget(window);

//        QTabWidget *tabWidget = new QTabWidget;
//        tabWidget->addTab(new QWidget, "Home");
//        tabWidget->addTab(new QWidget, "Work");
//        // ... Add other tabs as needed

//        QLineEdit *searchLineEdit = new QLineEdit;
//        searchLineEdit->setPlaceholderText("Search");

//        QHBoxLayout *hBoxLayout = new QHBoxLayout;
//        hBoxLayout->addWidget(tabWidget);
//        hBoxLayout->addWidget(searchLineEdit);

//        mainWidget->setLayout(hBoxLayout);
//        window->setCentralWidget(mainWidget);

//        window->show();


}
home::~home()
{
    delete ui;
}



//

//


//


//

