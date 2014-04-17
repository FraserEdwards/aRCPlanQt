#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
using namespace std;

#include "guimain.h"
#include "ui_guimain.h"
#include "Simulation.h"

double gG0;


int main(int argc, char *argv[])
{

    Filepath filepath;

    ConfigFile config("caseInputData.txt");
    Parameters initial;

    initial.collect(config);
    QApplication a(argc, argv);

    guimain b;
    b.setnames(initial, filepath);
    b.showMaximized();

    return a.exec();

}
