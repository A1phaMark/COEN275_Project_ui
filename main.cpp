#include "management_tool.h"
#include <iostream>
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    management_tool w;
    w.setLoginPage();
    w.show();
    return a.exec();
}

