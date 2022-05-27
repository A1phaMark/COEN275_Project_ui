#include "bugmodel.h"

bugModel::bugModel(){}

vector<bugObject> bugModel::fetchObjectsBy(projectObject project)
{
    objects = vector<bugObject>();
    QString qry_s =  QString("SELECT * FROM project_management.bug WHERE project_management.bug.project_id = %1;").arg(project.projectID);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        bugObject newObject = bugObject();
        newObject.bugID = qry.value(0).toInt();
        int nameFieldNo = qry.record().indexOf("name");
        newObject.name = qry.value(nameFieldNo).toString();
        int statusNo = qry.record().indexOf("status");
        newObject.status = qry.value(statusNo).toString();
        int descriptionNo = qry.record().indexOf("description");
        newObject.description = qry.value(descriptionNo).toString();
        int createDateNo = qry.record().indexOf("create_date");
        newObject.createDate = qry.value(createDateNo).toDateTime();
        int updateDateNo = qry.record().indexOf("update_date");
        newObject.updateDate = qry.value(updateDateNo).toDateTime();
        objects.push_back(newObject);
    }
    return objects;
}

bool bugModel::addBug(projectObject project, QString name, QString description)
{
     QString qry_s = QString("INSERT INTO `project_management`.`bug` (`name`, `description`, `project_id`) VALUES ('%1', '%2', %3);").arg(name, description, QString::number(project.projectID));
     return DB::getInstance()->write(qry_s);
}

bool bugModel::removeBug(bugObject bug)
{
    QString qry_s = QString("DELETE FROM `project_management`.`bug` WHERE (`id` = %1);").arg(bug.bugID);
    return DB::getInstance()->write(qry_s);
}
