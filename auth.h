#ifndef AUTH_H
#define AUTH_H

#include <QtSql>
#include <QString>
#include "db.h"

class auth
{   

    public:
        auth();
        bool login(QString userName, QString password);
        bool signUp(QString userName, QString password);
        QString userName;
        int userID;
};

#endif // AUTH_H
