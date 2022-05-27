#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.h"
#include <QtSql>
#include "db.h"

using namespace std;

class userModel
{
    public:
        userModel();
        vector<user> fetchObjectsBy(QString title);
        vector<user> fetchAllObjects();
        bool addPosition(auth username, QString new_position);
        vector<user> objects;

};

#endif // USERMODEL_H
