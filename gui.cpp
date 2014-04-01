#include <QApplication>
#include <QDesktopWidget>

#include "gui.h"
#include "guimain.h"
#include "ui_guimain.h"

#include "Simulation.h"
#include <iostream>
using namespace std;

GUI::GUI()
{


}

int GUI::run(int argc, char *argv[]){

    ConfigFile config("caseInputData.txt");
    Parameters initial;
    initial.collect(config);
    QApplication a(argc, argv);

    guimain b;
    b.setnames(initial);
    b.showMaximized();

    return a.exec();

}
