#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "usermemento.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QDebug>
#include <QDir>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

QString LoginWindow::getAbsolutePath(const QString &relativePath) {
    return QDir::currentPath() + "/" + relativePath;
}

bool LoginWindow::isAdmin(const QString &username, const QString &password)
{
    QString filePath = getAbsolutePath("userdatabase.json");
    qDebug() << "Opening file at path:" << filePath;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open userdatabase.json for reading";
        return false;
    }

    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonArray users = doc.array();

    for (const QJsonValue &val : users) {
        QJsonObject user = val.toObject();
        if (user["username"].toString() == username && user["password"].toString() == password) {
            return user["role"].toString() == "admin";
        }
    }
    return false;
}

// Create Memento
UserMemento *LoginWindow::createMemento() const
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    return new UserMemento(username, password);
}

// Restore Memento
void LoginWindow::restoreMemento(UserMemento *memento)
{
    ui->usernameInput->setText(memento->getUsername());
    ui->passwordInput->setText(memento->getPassword());
    delete memento; // Clean up after restoration
}

void LoginWindow::saveUser(const QString &username, const QString &password)
{
    QString filePath = getAbsolutePath("lastuser.json");
    qDebug() << "Opening file at path:" << filePath;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Unable to open lastuser.json for writing";
        return;
    }

    QJsonObject user;
    user["username"] = username;
    user["password"] = password;
    QJsonDocument doc(user);
    file.write(doc.toJson());
    file.close();
}

void LoginWindow::removeUser(const QString &username)
{
    QString filePath = getAbsolutePath("userdatabase.json");
    qDebug() << "Opening file at path:" << filePath;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open userdatabase.json for reading";
        return;
    }

    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonArray users = doc.array();
    QJsonArray updatedUsers;

    for (const QJsonValue &val : users) {
        QJsonObject user = val.toObject();
        if (user["username"].toString() != username) {
            updatedUsers.append(user);
        }
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Unable to open userdatabase.json for writing";
        return;
    }

    QJsonDocument updatedDoc(updatedUsers);
    file.write(updatedDoc.toJson());
    file.close();
}

void LoginWindow::restoreUser()
{
    QString filePath = getAbsolutePath("lastuser.json");
    qDebug() << "Opening file at path:" << filePath;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open lastuser.json for reading";
        return;
    }

    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject user = doc.object();
    UserMemento *memento = new UserMemento(user["username"].toString(), user["password"].toString());
    restoreMemento(memento);
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    qDebug() << "Attempting login with username:" << username << "and password:" << password;

    if (isAdmin(username, password)) {
        qDebug() << "User is admin";
        MainWindow *mainWindow = new MainWindow;
        mainWindow->setUserType("admin");
        mainWindow->show();
        this->close();
    } else {
        QString filePath = getAbsolutePath("userdatabase.json");
        qDebug() << "Opening file at path:" << filePath;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Unable to open userdatabase.json for reading";
            return;
        }

        QByteArray data = file.readAll();
        file.close();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonArray users = doc.array();

        for (const QJsonValue &val : users) {
            QJsonObject user = val.toObject();
            if (user["username"].toString() == username && user["password"].toString() == password) {
                qDebug() << "User is regular user";
                MainWindow *mainWindow = new MainWindow;
                mainWindow->setUserType("user");
                mainWindow->show();
                this->close();
                return;
            }
        }

        qDebug() << "Invalid username or password";
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}

void LoginWindow::on_saveUserButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    saveUser(username, password);
    QMessageBox::information(this, "Save User", "User saved successfully");
}

void LoginWindow::on_removeUserButton_clicked()
{
    QString username = ui->usernameInput->text();
    removeUser(username);
    QMessageBox::information(this, "Remove User", "User removed successfully");
}

void LoginWindow::on_restoreUserButton_clicked()
{
    restoreUser();
    QMessageBox::information(this, "Restore User", "Last saved user restored");
}
