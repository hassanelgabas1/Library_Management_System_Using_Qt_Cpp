#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUserType(QString userType);

private slots:
    void on_addBookButton_clicked();
    void on_searchBookButton_clicked();
    void on_filterCategoryButton_clicked();
    void on_removeBookButton_clicked();

private:
    Ui::MainWindow *ui;
    QString userType;
    QJsonArray loadBooks();
    void saveBooks(const QJsonArray &books);
    void updateBookList(const QJsonArray &books);
};

#endif // MAINWINDOW_H
