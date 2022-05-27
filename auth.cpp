#include "auth.h"
#include "db.h"

auth::auth(){}

bool auth::login(QString userName, QString password)
{
    QString qry_s = QString("SELECT * FROM project_management.auth WHERE user_name='%1' AND pwd='%2';").arg(userName, password);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);

    if(qry.next())
    {
        this->userID = qry.value(0).toInt();
        this->userName = userName;
        return true;
    }

    return false;
}

bool auth::signUp(QString userName, QString password)
{
    QString qry_s =  QString("INSERT INTO `project_management`.`auth` (`user_name`, `pwd`) VALUES ('%1', '%2');").arg(userName, password);
    return DB::getInstance()->write(qry_s);
}
