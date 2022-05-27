#ifndef BUGOBJECT_H
#define BUGOBJECT_H

#include <QString>
#include <QDateTime>

class bugObject
{
    public:
        bugObject();
        int bugID;
        QString name;
        QString status;
        QString description;
        QDateTime createDate;
        QDateTime updateDate;
        bool updateBug();
};

#endif // BUGOBJECT_H
