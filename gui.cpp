#include <QApplication>

#include "gui.h"
#include "guiinput.h"
#include "guioutput.h"
#include "Simulation.h"

GUI::GUI()
{


}

int GUI::run(int argc, char *argv[]){

    QApplication a(argc, argv);

    guiinput b;
    b.show();

    guioutput c;
    c.show();

    Simulation simulation;
    simulation.run();

    return a.exec();

}
