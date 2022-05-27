#include "taskmodel.h"

taskModel::taskModel(){}

vector<taskObject> taskModel::fetchAllObjects()
{
    objects = vector<taskObject>();
    QString qry_s = "SELECT * FROM project_management.task LEFT JOIN project_management.position ON project_management.task.position_id = project_management.position.id LEFT JOIN project_management.auth ON project_management.position.user_id = project_management.auth.id;";
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        taskObject newObject = taskObject();
        newObject.taskID = qry.value(0).toInt();
        newObject.name = qry.value(1).toString();
        newObject.status = qry.value(2).toString();
        newObject.createDate = qry.value(3).toDateTime();
        newObject.updateDate = qry.value(4).toDateTime();
        newObject.owner = qry.value(13).toString();
        objects.push_back(newObject);
    }
    return objects;
}

vector<taskObject> taskModel::fetchObjectsBy(projectObject project)
{
    objects = vector<taskObject>();
    QString qry_s =  QString("SELECT * FROM project_management.task JOIN project_management.project ON project_management.task.project_id = project_management.project.id AND project_management.task.project_id = %1 LEFT JOIN project_management.position ON project_management.task.position_id = project_management.position.id LEFT JOIN project_management.auth ON project_management.position.user_id = project_management.auth.id ORDER BY project_management.project.id;").arg(project.projectID);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        taskObject newObject = taskObject();
        newObject.taskID = qry.value(0).toInt();
        newObject.name = qry.value(1).toString();
        newObject.status = qry.value(2).toString();
        newObject.createDate = qry.value(3).toDateTime();
        newObject.updateDate = qry.value(4).toDateTime();
        newObject.owner = qry.value(18).toString();
        newObject.projectID = qry.value(8).toInt();
        newObject.projectObject::name = qry.value(9).toString();
        newObject.projectObject::status = qry.value(10).toString();
        newObject.projectObject::createDate = qry.value(11).toDateTime();
        newObject.projectObject::updateDate = qry.value(12).toDateTime();
        objects.push_back(newObject);
    }
    return objects;
}

vector<taskObject> taskModel::fetchObjectsBy(user usr)
{
    objects = vector<taskObject>();
    QString qry_s =  QString("SELECT * FROM project_management.task JOIN project_management.project ON project_management.task.project_id = project_management.project.id AND project_management.task.position_id = %1 ORDER BY project_management.project.id;").arg(usr.posID);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        taskObject newObject = taskObject();
        newObject.taskID = qry.value(0).toInt();
        newObject.name = qry.value(1).toString();
        newObject.status = qry.value(2).toString();
        newObject.createDate = qry.value(3).toDateTime();
        newObject.updateDate = qry.value(4).toDateTime();
        newObject.projectID = qry.value(8).toInt();
        newObject.projectObject::name = qry.value(9).toString();
        newObject.projectObject::status = qry.value(10).toString();
        newObject.projectObject::createDate = qry.value(11).toDateTime();
        newObject.projectObject::updateDate = qry.value(12).toDateTime();
        objects.push_back(newObject);
    }
    return objects;
}

vector<taskObject> taskModel::fetchObjectsBy(user usr, projectObject project, QString curStatus)
{
    objects = vector<taskObject>();
    QString qry_s =  QString("SELECT * FROM project_management.task JOIN project_management.project ON project_management.task.project_id = project_management.project.id AND project_management.task.position_id = %1 AND project_management.task.status='%2' AND project_management.project.id = %3;").arg(QString::number(usr.posID), curStatus, QString::number(project.projectID));
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        taskObject newObject = taskObject();
        newObject.taskID = qry.value(0).toInt();
        newObject.name = qry.value(1).toString();
        newObject.status = qry.value(2).toString();
        newObject.createDate = qry.value(3).toDateTime();
        newObject.updateDate = qry.value(4).toDateTime();
        newObject.projectID = qry.value(8).toInt();
        newObject.projectObject::name = qry.value(9).toString();
        newObject.projectObject::status = qry.value(10).toString();
        newObject.projectObject::createDate = qry.value(11).toDateTime();
        newObject.projectObject::updateDate = qry.value(12).toDateTime();
        objects.push_back(newObject);
    }
    return objects;
}

vector<taskObject> taskModel::fetchObjectsBy(projectObject project, QString curStatus)
{
    objects = vector<taskObject>();
    QString qry_s =  QString("SELECT * FROM project_management.task JOIN project_management.project ON project_management.task.project_id = project_management.project.id AND project_management.task.project_id = %1 AND project_management.task.status = '%2' LEFT JOIN project_management.position ON project_management.task.position_id = project_management.position.id LEFT JOIN project_management.auth ON project_management.position.user_id = project_management.auth.id ORDER BY project_management.project.id;").arg(QString::number(project.projectID), curStatus);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        taskObject newObject = taskObject();
        newObject.taskID = qry.value(0).toInt();
        newObject.name = qry.value(1).toString();
        newObject.status = qry.value(2).toString();
        newObject.createDate = qry.value(3).toDateTime();
        newObject.updateDate = qry.value(4).toDateTime();
        newObject.description = qry.value(7).toString();
        newObject.projectID = qry.value(8).toInt();
        newObject.owner = qry.value(18).toString();
        newObject.projectObject::name = qry.value(9).toString();
        newObject.projectObject::status = qry.value(10).toString();
        newObject.projectObject::createDate = qry.value(11).toDateTime();
        newObject.projectObject::updateDate = qry.value(12).toDateTime();
        objects.push_back(newObject);
    }
    return objects;
}

bool taskModel::addTask(projectObject project, QString name, QString description, QString updateDate, user usr)
{
     QString qry_s =  QString("INSERT INTO `project_management`.`task` (`name`, `description`, `update_date`, `project_id`, `position_id`) VALUES ('%1', '%2', '%3', %4, %5);").arg(name, description, updateDate, QString::number(project.projectID), QString::number(usr.posID));
     return DB::getInstance()->write(qry_s);
}

bool taskModel::removeTask(taskObject task)
{
    QString qry_s =  QString("DELETE FROM `project_management`.`task` WHERE (`id` = %1);").arg(task.taskID);
    return DB::getInstance()->write(qry_s);
}
