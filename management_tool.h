#ifndef MANAGEMENT_TOOL_H
#define MANAGEMENT_TOOL_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class management_tool; }
QT_END_NAMESPACE

class management_tool : public QMainWindow
{
    Q_OBJECT

public:
    management_tool(QWidget *parent = nullptr);
    ~management_tool();
    void setMainPage();
    void setProjectPage(std::string p);
    void setNewProjectPage();
    void setParticipantPage(std::string p);

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

private:
    Ui::management_tool *ui;
    std::string userid;
    std::string projectName;
    std::vector<std::string> projects;
    std::vector<std::string> tasks;
    std::vector<std::string> bugs;
    std::vector<std::string> task_comment;
    std::vector<std::string> bug_comment;
};
#endif // MANAGEMENT_TOOL_H
