QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    categorychoice.cpp \
    changestaggering.cpp \
    dbmanager.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow_charts.cpp \
    mainwindow_initTable.cpp \
    mainwindow_methods.cpp \
    newstaggering.cpp \
    newstudent.cpp \
    studentdetails.cpp \
    updatestudent.cpp \
    utility.cpp

HEADERS += \
    categorychoice.h \
    changestaggering.h \
    dbmanager.h \
    login.h \
    mainwindow.h \
    newstaggering.h \
    newstudent.h \
    studentdetails.h \
    updatestudent.h \
    utility.h

FORMS += \
    categorychoice.ui \
    changestaggering.ui \
    login.ui \
    mainwindow.ui \
    newstaggering.ui \
    newstudent.ui \
    studentdetails.ui \
    updatestudent.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

QMAKE_CXXFLAGS += -std=gnu++11

DISTFILES +=
