#ifndef TIMELINEMODEL_H
#define TIMELINEMODEL_H

#include <QtSql>
#include "db.h"
#include "timelineobject.h"
#include "projectobject.h"

using namespace std;

class timelineModel
{
    public:
        timelineModel();
        vector<timelineObject> fetchObjectsBy(projectObject project);
        bool addTimeline(projectObject project, QString content);
        bool removeTimeline(timelineObject timeline);
        vector<timelineObject> objects;
};

#endif // TIMELINEMODEL_H
