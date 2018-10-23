#-------------------------------------------------
#
# Project created by QtCreator 2018-08-21T09:10:57
#
#-------------------------------------------------

QT       += core gui widgets
QT       += network
CONFIG +=console
TARGET = analysis
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    custombuttongroup.cpp \
    simulation_moudle.cpp \
    custommenu.cpp \
    moudel_group.cpp \
    paramdialog.cpp \
    paramdialog.cpp \
    line_group.cpp \
    custombuttongroup.cpp \
    custommenu.cpp \
    line_group.cpp \
    main.cpp \
    mainwindow.cpp \
    moudel_group.cpp \
    paramdialog.cpp \
    simulation_moudle.cpp \
    interface.cpp \
    custombutton.cpp \
    analysis.cpp \
    ui.cpp \
    copygroup.cpp \
    run_simu.cpp \
    button.cpp \
    customtreewidget.cpp \
    data_dialog.cpp \
    fault_dialog.cpp \
    algorithm.cpp

HEADERS += \
        mainwindow.h \
    custombuttongroup.h \
    system_flag.h \
    simulation_moudle.h \
    custommenu.h \
    moudel_group.h \
    paramdialog.h \
    line_group.h \
    custombuttongroup.h \
    custommenu.h \
    line_group.h \
    mainwindow.h \
    moudel_group.h \
    paramdialog.h \
    simulation_modle.h \
    simulation_moudle.h \
    system_flag.h \
    interface.h \
    custombutton.h \
    analysis.h \
    ui.h \
    copygroup.h \
    run_simu.h \
    button.h \
    customtreewidget.h \
    data_dialog.h \
    fault_dialog.h \
    algorithm.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icon/1.png \
    icon/10.png \
    icon/10a.png \
    icon/11.png \
    icon/11a.png \
    icon/12.png \
    icon/12a.png \
    icon/13.png \
    icon/13a.png \
    icon/14.png \
    icon/14a.png \
    icon/15.png \
    icon/15a.png \
    icon/16.png \
    icon/16a.png \
    icon/17.png \
    icon/17a.png \
    icon/18.png \
    icon/18a.png \
    icon/19.png \
    icon/19a.png \
    icon/1a.png \
    icon/2.png \
    icon/20.png \
    icon/20a.png \
    icon/21a.png \
    icon/22a.png \
    icon/23a.png \
    icon/24a.png \
    icon/25a.png \
    icon/26a.png \
    icon/27.png \
    icon/27a.png \
    icon/28.png \
    icon/28a.png \
    icon/29.png \
    icon/29a.png \
    icon/2a.png \
    icon/3.png \
    icon/30.png \
    icon/30a.png \
    icon/31.png \
    icon/31a.png \
    icon/32.png \
    icon/32a.png \
    icon/33.png \
    icon/33a.png \
    icon/34.png \
    icon/34a.png \
    icon/35.png \
    icon/35a.png \
    icon/36.png \
    icon/36a.png \
    icon/37.png \
    icon/37a.png \
    icon/38.png \
    icon/38a.png \
    icon/39.png \
    icon/39a.png \
    icon/3a.png \
    icon/4.png \
    icon/40.png \
    icon/40a.png \
    icon/41.png \
    icon/41a.png \
    icon/42.png \
    icon/42a.png \
    icon/43.png \
    icon/43a.png \
    icon/44.png \
    icon/44a.png \
    icon/45.png \
    icon/45a.png \
    icon/46.png \
    icon/46a.png \
    icon/47a.png \
    icon/48a.png \
    icon/49a.png \
    icon/4a.png \
    icon/5.png \
    icon/50a.png \
    icon/51a.png \
    icon/52a.png \
    icon/53a.png \
    icon/54a.png \
    icon/55a.png \
    icon/56a.png \
    icon/57a.png \
    icon/58a.png \
    icon/59a.png \
    icon/5a.png \
    icon/6.png \
    icon/60a.png \
    icon/61a.png \
    icon/62a.png \
    icon/63a.png \
    icon/64a.png \
    icon/65a.png \
    icon/66a.png \
    icon/67a.png \
    icon/6a.png \
    icon/7.png \
    icon/7a.png \
    icon/8.png \
    icon/8a.png \
    icon/9.png \
    icon/9a.png \
    1.txt

RESOURCES += \
    icon.qrc
