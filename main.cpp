#include <QApplication>
#include <cstdlib>
using namespace std;

#include "guiinput.h"
#include "guioutput.h"
#include "Filepath.h"
#include "Simulation.h"

double gG0;
string location;

int main(int argc, char *argv[])
{
    // Read the problem configuration file to provide parameter values where library data does not exist
    Filepath filePath;

    QApplication a(argc, argv);

    guiinput b;
    b.show();

    guioutput c;
    c.show();

//    Simulation simulation;
//    simulation.run();

    return a.exec();
}
