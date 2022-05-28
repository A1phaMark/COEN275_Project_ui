#include "projectmodel.h"

projectModel::projectModel(){}

vector<projectObject> projectModel::fetchAllObjects()
{
    objects = vector<projectObject>();
    QString qry_s = "SELECT * FROM project_management.project";
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        projectObject newObject = projectObject();
//        int rowNum = qry.at();
//        int columnNum = qry.record().count();
        newObject.projectID = qry.value(0).toInt();
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

vector<projectObject> projectModel::fetchOwnObjects(int userid)
{
    objects = vector<projectObject>();
    QString qry_s = "SELECT DISTINCT pro.id, pro.name, pro.status, pro.create_date, pro.update_date, pro.description"
            " FROM project_management.project pro, project_management.participant par WHERE pro.id = par.project_id and par.position_id = "
            + QString::fromStdString(std::to_string(userid));
    qDebug()<< qry_s;
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        projectObject newObject = projectObject();
//        int rowNum = qry.at();
//        int columnNum = qry.record().count();
        newObject.projectID = qry.value(0).toInt();
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


bool projectModel::addProject(QString name, QString description, QString updateDate)
{
     QString qry_s =  QString("INSERT INTO `project_management`.`project` (`name`, `description`, `status`, `update_date`) VALUES ('%1', '%2', '%3', '%4');").arg(name, description, "New", updateDate);
     return DB::getInstance()->write(qry_s);
}

bool projectModel::removeProject(projectObject project)
{
    QString qry_s =  QString("DELETE FROM `project_management`.`project` WHERE (`id` = %1);").arg(project.projectID);
    return DB::getInstance()->write(qry_s);
}

