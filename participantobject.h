#ifndef PARTICIPANTOBJECT_H
#define PARTICIPANTOBJECT_H

#include "user.h"


class participantObject: public user
{
    public:
        participantObject();
        int partID;
};

#endif // PARTICIPANTOBJECT_H
