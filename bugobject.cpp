#include "bugobject.h"
#include "db.h"

bugObject::bugObject(){}

bool bugObject::updateBug()
{
    QString qry_s = QString("UPDATE project_management.bug SET project_management.bug.name = '%1', project_management.bug.status = '%2', project_management.bug.update_date = NOW() WHERE project_management.bug.id = %3;").arg(name, status, QString::number(bugID));
    return DB::getInstance()->write(qry_s);
}
