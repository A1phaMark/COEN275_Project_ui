#ifndef PARTICIPANTMODEL_H
#define PARTICIPANTMODEL_H

#include "user.h"
#include "projectobject.h"
#include <QtSql>
#include "db.h"

using namespace std;

class participantModel
{
    public:
        participantModel();
        vector<user> fetchObjectsBy(projectObject project);
        vector<user> filterObjectsBy(projectObject project);
        vector<user> fetchAllObjects();
        bool addParticipant(user usr, projectObject project);
        vector<user> objects;
};

#endif // PARTICIPANTMODEL_H
