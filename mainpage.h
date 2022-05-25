#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>

namespace Ui {
class mainPage;
}

class mainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainPage(QWidget *parent = nullptr);
    ~mainPage();

private:
    Ui::mainPage *ui;
};

#endif // MAINPAGE_H
