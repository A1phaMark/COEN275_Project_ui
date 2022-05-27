#ifndef BUGMODEL_H
#define BUGMODEL_H

#include <QtSql>
#include "db.h"
#include "bugobject.h"
#include "projectobject.h"

using namespace std;

class bugModel
{
    public:
        bugModel();
        vector<bugObject> fetchObjectsBy(projectObject project);
        vector<bugObject> objects;
        bool addBug(projectObject project, QString name, QString description);
        bool removeBug(bugObject bug);
};

#endif // BUGMODEL_H
