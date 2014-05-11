#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
using namespace std;

#include "guimain.h"
#include "ui_guimain.h"
#include "Simulation.h"
#include "File.h"

File file;

int main(int argc, char *argv[])
{
    // Read the problem configuration file to provide parameter values where library data does not exist
//    Filepath filePath;

    QApplication a(argc, argv);
    file.directory = a.applicationDirPath().toStdString();
    file.correct();

    ConfigFile config(file.directory + "caseInputData.txt");
    Parameters initial;
    initial.collect(config);    

    guimain b;
    b.setnames(initial,0);
    b.showMaximized();

    return a.exec();

}
