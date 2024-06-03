QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BookManager
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           loginwindow.cpp

HEADERS += mainwindow.h \
           UserMemento.h \
           loginwindow.h

FORMS += mainwindow.ui \
         loginwindow.ui

RESOURCES +=

DISTFILES += \
    bookdatabase.json \
    userdatabase.json
