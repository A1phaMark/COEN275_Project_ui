#include "participantmodel.h"

participantModel::participantModel(){}

vector<participantObject> participantModel::fetchObjectsBy(projectObject project)
{
    objects = vector<participantObject>();
    QString qry_s =  QString("SELECT * FROM project_management.participant LEFT JOIN project_management.position ON project_management.participant.position_id = project_management.position.id LEFT JOIN project_management.auth ON project_management.position.user_id = project_management.auth.id WHERE project_management.participant.project_id = %1;").arg(project.projectID);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        participantObject newObject = participantObject();
        newObject.partID = qry.value(0).toInt();
        newObject.posID = qry.value(1).toInt();
        newObject.position = qry.value(4).toString();
        newObject.userName = qry.value(7).toString();
        objects.push_back(newObject);
    }
    return objects;
}

vector<participantObject> participantModel::filterObjectsBy(projectObject project)
{
    objects = vector<participantObject>();
    QString qry_s =  QString("SELECT * FROM project_management.participant LEFT JOIN project_management.position ON project_management.participant.position_id = project_management.position.id LEFT JOIN project_management.auth ON project_management.position.user_id = project_management.auth.id WHERE project_management.participant.project_id != %1;").arg(project.projectID);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        participantObject newObject = participantObject();
        newObject.partID = qry.value(0).toInt();
        newObject.posID = qry.value(1).toInt();
        newObject.position = qry.value(4).toString();
        newObject.userName = qry.value(7).toString();
        objects.push_back(newObject);
    }
    return objects;
}

vector<participantObject> participantModel::fetchAllObjects()
{
    objects = vector<participantObject>();
    QString qry_s =  "SELECT * FROM project_management.participant LEFT JOIN project_management.position ON project_management.participant.position_id = project_management.position.id LEFT JOIN project_management.auth ON project_management.position.user_id = project_management.auth.id;";
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        participantObject newObject = participantObject();
        newObject.posID = qry.value(1).toInt();
        newObject.position = qry.value(4).toString();
        newObject.userName = qry.value(7).toString();
        objects.push_back(newObject);
    }
    return objects;
}

bool participantModel::addParticipant(participantObject usr, projectObject project)
{
    QString qry_s =  QString("INSERT INTO `project_management`.`participant` (`position_id`, `project_id`) VALUES (%1, %2);").arg(QString::number(usr.posID), QString::number(project.projectID));
    return DB::getInstance()->write(qry_s);
}

bool participantModel::removeParticipant(participantObject usr)
{
    QString qry_s = QString("DELETE FROM `project_management`.`participant` WHERE (`id` = %1);").arg(usr.partID);
    qDebug()<<qry_s;
    return DB::getInstance()->write(qry_s);
}


