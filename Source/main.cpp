//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
using namespace std;

#include "guimain.h"
#include "ui_guimain.h"
#include "Simulation.h"
#include "File.h"
#include "Solution.h"

File file;
Solution solution;

int main(int argc, char *argv[])
{
    // Read the problem configuration file to provide parameter values where library data does not exist
//    Filepath filePath;

    QApplication a(argc, argv);

    file.directory = a.applicationDirPath().toStdString();
    file.correct();

    ConfigFile config(file.directory + "caseInputData.txt");
    Parameters initial;

    guimain b;
    b.setnames(initial,0);
    b.setWindowTitle("");
    b.show();

    return a.exec();

}
