#include <QApplication>
//#include <QDesktopWidget>

#include "guimain.h"
#include "ui_guimain.h"
#include "Filepath.h"

#include <cstdlib>
#include <iostream>
using namespace std;

double gG0;
string location;

int main(int argc, char *argv[])
{
    // Read the problem configuration file to provide parameter values where library data does not exist
    Filepath filePath;

    ConfigFile config("caseInputData.txt");
    Parameters initial;
    initial.collect(config);
    QApplication a(argc, argv);

    guimain b;
    b.setnames(initial);
    b.showMaximized();

    return a.exec();

}
