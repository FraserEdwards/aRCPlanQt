#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
using namespace std;

#include "guimain.h"
#include "ui_guimain.h"
#include "Simulation.h"
#include "Filepath.h"

Filepath filepath;

int main(int argc, char *argv[])
{
    // Read the problem configuration file to provide parameter values where library data does not exist
//    Filepath filePath;

    ConfigFile config("caseInputData.txt");
    Parameters initial;
    initial.collect(config);

    QApplication a(argc, argv);
    filepath.directory = a.applicationDirPath().toStdString();
    filepath.correct();

    guimain b;
    b.setnames(initial);
    b.showMaximized();

    return a.exec();

}
