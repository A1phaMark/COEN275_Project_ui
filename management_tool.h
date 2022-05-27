#ifndef MANAGEMENT_TOOL_H
#define MANAGEMENT_TOOL_H
#include <QMainWindow>
#include <QListWidget>
#include "user.h"
#include "projectmodel.h"
#include "taskmodel.h"
#include "bugmodel.h"
#include "usermodel.h"
#include "commentmodel.h"
#include "participantmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class management_tool; }
QT_END_NAMESPACE

class management_tool : public QMainWindow
{
    Q_OBJECT

public:
    management_tool(QWidget *parent = nullptr);
    ~management_tool();
    void setLoginPage();
    void setMainPage();
    void setProjectPage();
    void setNewProjectPage();
    void setParticipantPage();
    void setTaskPage();
    void setNewTaskPage();
    bool checkDateFormat(std::string date);
    taskObject getTask();
    void refreshTasks();
    void refreshTasksByUser();

private slots:

    void on_login_2_clicked();

    void on_logout_clicked();

    void on_viewDetail_clicked();

    void on_backToMain_clicked();

    void on_cancelNewProject_clicked();

    void on_confirmNewProject_clicked();

    void on_createNew_clicked();

    void on_backToMain_2_clicked();

    void on_viewParticipants_clicked();

    void on_addParticipantsButton_clicked();

    void on_removeParticipants_clicked();

    void on_deleteProject_clicked();

    void on_pushButton_4_clicked();

    void on_viewBug_clicked();

    void on_backToProject_clicked();

    void on_cancelNewTask_clicked();

    void on_newTaskButton_clicked();

    void on_projectStatusBox_currentIndexChanged(int index);


    void on_deleteTaskButton_clicked();

    void on_deleteBug_clicked();

    void on_confirmNewTask_clicked();

    void on_createBug_clicked();

    void on_pushButton_7_clicked();

    void on_reassignButton_clicked();

    void on_taskStatusBox_currentIndexChanged(int index);

    void on_viewAllTask_clicked();

    void on_viewOwnTask_clicked();

private:
    Ui::management_tool *ui;
    std::string userid;
    std::string projectName;
    std::vector<std::string> tasks;
    std::vector<std::string> task_comment;
    std::vector<std::string> bug_comment;

    user* usr;
    vector<projectObject> projects;
    vector<bugObject> bugs;
    vector<taskObject> newTasks;
    vector<taskObject> progressTasks;
    vector<taskObject> completedTasks;
    vector<user> users;
    vector<user> newParticipants;
    vector<participantObject> curParticipants;
};
#endif // MANAGEMENT_TOOL_H
