QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    home.cpp \
    login.cpp \
    main.cpp \
    profile.cpp \
    signup.cpp \
    splash.cpp \
    verification.cpp

HEADERS += \
    home.h \
    login.h \
    profile.h \
    signup.h \
    splash.h \
    verification.h

FORMS += \
    home.ui \
    login.ui \
    profile.ui \
    signup.ui \
    splash.ui \
    verification.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images/Images.qrc
