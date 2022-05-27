#include "projectobject.h"
#include "db.h"

projectObject::projectObject(){}

bool projectObject::updateProject(QString new_status)
{
    QString qry_s = QString("UPDATE project_management.project SET project_management.project.status = '%1', project_management.project.update_date = NOW() WHERE project_management.project.id = %2;").arg(new_status, QString::number(projectID));
    return DB::getInstance()->write(qry_s);
}
