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

    QGroupBox* groupBox = new QGroupBox();
//    QLabel *label = new QLabel("hiii");
    QVBoxLayout *layout = new QVBoxLayout;
//    layout->addWidget(label);
    groupBox->setLayout(layout);

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(groupBox);
    ui->scrollArea->setLayout(layout2);
    ui->scrollArea->setMinimumHeight(1000);

    //generate post

    for(int i=0; i<20; i++){
       QGroupBox* groupBox = new QGroupBox("First Group Box");
       groupBox->setMinimumHeight(200);
       groupBox->setMaximumHeight(500);
       ui->scrollArea->layout()->addWidget(groupBox);
    }








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

