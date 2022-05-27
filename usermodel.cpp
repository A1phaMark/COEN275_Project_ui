#include "usermodel.h"

userModel::userModel(){}

vector<user> userModel::fetchObjectsBy(QString title)
{
    objects = vector<user>();
    QString qry_s =  QString("SELECT * FROM project_management.position JOIN project_management.auth ON project_management.position.user_id = project_management.auth.id AND project_management.position.name = '%1';").arg(title);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        user newObject = user();
        newObject.posID = qry.value(0).toInt();
        newObject.position = qry.value(1).toString();
        newObject.userName = qry.value(4).toString();
        objects.push_back(newObject);
    }
    return objects;
}

vector<user> userModel::fetchAllObjects()
{
    objects = vector<user>();
    QString qry_s =  "SELECT * FROM project_management.position JOIN project_management.auth ON project_management.position.user_id = project_management.auth.id;";
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        user newObject = user();
        newObject.posID = qry.value(0).toInt();
        newObject.position = qry.value(1).toString();
        newObject.userName = qry.value(4).toString();
        objects.push_back(newObject);
    }
    return objects;
}

bool userModel::addPosition(auth username, QString new_position)
{
    QString qry_s =  QString("INSERT INTO `project_management`.`position` (`name`, `user_id`) VALUES ('%1', %2);").arg(new_position, QString::number(username.userID));
    return DB::getInstance()->write(qry_s);
}
