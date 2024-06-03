/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *addBookButton;
    QPushButton *searchBookButton;
    QPushButton *filterCategoryButton;
    QPushButton *removeBookButton;
    QListWidget *bookList;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 300);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        addBookButton = new QPushButton(centralwidget);
        addBookButton->setObjectName("addBookButton");
        addBookButton->setGeometry(QRect(30, 20, 100, 30));
        searchBookButton = new QPushButton(centralwidget);
        searchBookButton->setObjectName("searchBookButton");
        searchBookButton->setGeometry(QRect(150, 20, 100, 30));
        filterCategoryButton = new QPushButton(centralwidget);
        filterCategoryButton->setObjectName("filterCategoryButton");
        filterCategoryButton->setGeometry(QRect(270, 20, 100, 30));
        removeBookButton = new QPushButton(centralwidget);
        removeBookButton->setObjectName("removeBookButton");
        removeBookButton->setGeometry(QRect(30, 70, 100, 30));
        bookList = new QListWidget(centralwidget);
        bookList->setObjectName("bookList");
        bookList->setGeometry(QRect(30, 110, 340, 140));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Book Manager", nullptr));
        addBookButton->setText(QCoreApplication::translate("MainWindow", "Add Book", nullptr));
        searchBookButton->setText(QCoreApplication::translate("MainWindow", "Search Book", nullptr));
        filterCategoryButton->setText(QCoreApplication::translate("MainWindow", "Filter by Category", nullptr));
        removeBookButton->setText(QCoreApplication::translate("MainWindow", "Remove Book", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
