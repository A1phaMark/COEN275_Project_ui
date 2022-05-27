#include "commentmodel.h"

commentModel::commentModel(){}

vector<commentObject> commentModel::fetchObjectsBy(taskObject task)
{
    objects = vector<commentObject>();
    QString qry_s = QString("SELECT * FROM project_management.comment WHERE project_management.comment.task_id = %1").arg(task.taskID);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        commentObject newObject = commentObject();
        newObject.commentID = qry.value(0).toInt();
        int contentNo = qry.record().indexOf("content");
        newObject.content = qry.value(contentNo).toString();
        int createDateNo = qry.record().indexOf("create_date");
        newObject.createDate = qry.value(createDateNo).toDateTime();
        objects.push_back(newObject);
    }
    return objects;
}

bool commentModel::addComment(QString content, taskObject task)
{
    QString qry_s = QString("INSERT INTO `project_management`.`comment` (`content`, `task_id`) VALUES ('%1', %2);").arg(content, QString::number(task.taskID));
    qDebug() << qry_s;
    return DB::getInstance()->write(qry_s);
}
