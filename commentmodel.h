#ifndef COMMENTMODEL_H
#define COMMENTMODEL_H

#include "commentobject.h"
#include "taskobject.h"

using namespace std;

class commentModel
{
    public:
        commentModel();
        vector<commentObject> fetchObjectsBy(taskObject task);
        bool addComment(QString content, taskObject task);
        vector<commentObject> objects;
};

#endif // COMMENTMODEL_H
