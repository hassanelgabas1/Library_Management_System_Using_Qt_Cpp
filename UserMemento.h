// usermemento.h
#ifndef USERMEMENTO_H
#define USERMEMENTO_H

#include <QString>

class UserMemento
{
public:
    UserMemento(const QString &username, const QString &password)
        : m_username(username), m_password(password) {}

    QString getUsername() const { return m_username; }
    QString getPassword() const { return m_password; }

private:
    QString m_username;
    QString m_password;
};

#endif // USERMEMENTO_H
