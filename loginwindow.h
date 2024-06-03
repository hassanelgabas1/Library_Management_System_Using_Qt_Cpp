// loginwindow.h
#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

namespace Ui {
class LoginWindow;
}

class UserMemento;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    UserMemento *createMemento() const; // Create Memento
    void restoreMemento(UserMemento *memento); // Restore Memento

private slots:
    void on_loginButton_clicked();
    void on_saveUserButton_clicked();
    void on_removeUserButton_clicked();
    void on_restoreUserButton_clicked();

private:
    Ui::LoginWindow *ui;
    bool isAdmin(const QString &username, const QString &password);
    void saveUser(const QString &username, const QString &password);
    void removeUser(const QString &username);
    void restoreUser();
    QString getAbsolutePath(const QString &relativePath);
};

#endif
