#include "projectobject.h"
#include "db.h"

projectObject::projectObject(){}

bool projectObject::updateProject()
{
    QString qry_s = QString("UPDATE project_management.project SET project_management.project.status = '%1', project_management.project.update_date = NOW() WHERE project_management.project.id = %2;").arg(status, QString::number(projectID));
    return DB::getInstance()->write(qry_s);
}
