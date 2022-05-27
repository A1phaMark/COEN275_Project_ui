#ifndef TIMELINEOBJECT_H
#define TIMELINEOBJECT_H

#include <QString>
#include <QDateTime>

class timelineObject
{
    public:
        timelineObject();
        int timelineID;
        QString name;
        QString status;
        QDateTime startDate;
        QDateTime endDate;
};

#endif // TIMELINEOBJECT_H
