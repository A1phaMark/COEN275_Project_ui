#ifndef COMMENTOBJECT_H
#define COMMENTOBJECT_H

#include <QString>
#include <QDateTime>

class commentObject
{
    public:
        commentObject();
        int commentID;
        QString content;
        QDateTime createDate;
};

#endif // COMMENTOBJECT_H
