#include <QApplication>

#include "gui.h"
#include "guiinput.h"
#include "ui_guiinput.h"

#include "guioutput.h"
#include "ui_guioutput.h"
#include "Simulation.h"

GUI::GUI()
{


}

int GUI::run(int argc, char *argv[]){

    ConfigFile config("caseInputData.txt");
    Parameters parameters;
    parameters.collect(config);
    QApplication a(argc, argv);

    guiinput b;
    b.setnames(parameters);
    b.show();

//    Simulation simulation;
//    simulation.run(parameters);

    guioutput c;
    c.show();



    return a.exec();

}
