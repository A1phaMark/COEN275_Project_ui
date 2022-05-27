#ifndef USER_H
#define USER_H

#include "auth.h"


class user: public auth
{
    private:
        static user* instance;

    public:
        user();
        QString position;
        int posID;
        static user* getInstance();
        bool initUserWithAuth(QString userName, QString password);
};

#endif // USER_H
