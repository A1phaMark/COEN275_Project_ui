#ifndef PARTICIPANTMODEL_H
#define PARTICIPANTMODEL_H

#include "participantobject.h"
#include "projectobject.h"
#include <QtSql>
#include "db.h"

using namespace std;

class participantModel
{
    public:
        participantModel();
        vector<participantObject> fetchObjectsBy(projectObject project);
        vector<participantObject> filterObjectsBy(projectObject project);
        vector<participantObject> fetchAllObjects();
        bool addParticipant(participantObject usr, projectObject project);
        bool removeParticipant(participantObject usr);
        vector<participantObject> objects;
};

#endif // PARTICIPANTMODEL_H
