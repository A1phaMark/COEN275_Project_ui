#include "taskobject.h"
#include "db.h"

taskObject::taskObject(){}

bool taskObject::updateTask()
{
    QString qry_s = QString("UPDATE project_management.task SET project_management.task.name = '%1', project_management.task.status = '%2', project_management.task.update_date = NOW() WHERE project_management.task.id = %3;").arg(name, status, QString::number(taskID));
    qDebug()<<qry_s<<"\n";
    return DB::getInstance()->write(qry_s);
}

bool taskObject::assignTask(user usr)
{
    QString qry_s = QString("UPDATE project_management.task SET project_management.task.position_id = %1 WHERE project_management.task.id = %2;").arg(QString::number(usr.posID), QString::number(taskID));
    return DB::getInstance()->write(qry_s);
}
