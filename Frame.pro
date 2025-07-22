QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    centerwidget.cpp \
    configmanager.cpp \
    databasemanager.cpp \
    framework.cpp \
    main.cpp \
    mainwidget.cpp \
    mouseevent.cpp \
    registermanager.cpp \
    serialport.cpp \
    statusbar.cpp \
    titlebar.cpp \
    widget.cpp

HEADERS += \
    centerwidget.h \
    configmanager.h \
    databasemanager.h \
    framework.h \
    mainwidget.h \
    mouseevent.h \
    registermanager.h \
    serialport.h \
    statusShelper.h \
    statusbar.h \
    titlebar.h \
    widget.h

FORMS += \
    centerwidget.ui \
    framework.ui \
    mainwidget.ui \
    registermanager.ui \
    serialport.ui \
    statusbar.ui \
    titlebar.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    img.qrc
