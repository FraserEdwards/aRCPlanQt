#include <QApplication>
#include <QDesktopWidget>

#include "gui.h"
#include "guimain.h"
#include "ui_guimain.h"

#include "guioutput.h"
#include "ui_guioutput.h"
#include "Simulation.h"
#include <iostream>
using namespace std;

GUI::GUI()
{


}

int GUI::run(int argc, char *argv[]){

    ConfigFile config("caseInputData.txt");
    Parameters parameters;
    parameters.collect(config);
    QApplication a(argc, argv);

    guimain b;
    b.setnames(parameters);
    b.showMaximized();

    Simulation simulation;
    Solution solution;

    solution = simulation.run(parameters);

    guioutput c;
    c.setresults(solution);
    c.show();

    return a.exec();

}
