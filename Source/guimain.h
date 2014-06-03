//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef GUIMAIN_H
#define GUIMAIN_H

#include <QMainWindow>
#include <QLineEdit>
#include <fstream>

#include "Parameters.h"
#include "Solution.h"
#include "Simulation.h"

namespace Ui {
class guimain;
}

class guimain : public QMainWindow
{
    Q_OBJECT

public:
    explicit guimain(QWidget *parent = 0);
    ~guimain();

    void setnames(Parameters parameters, char dropdown);
    void setresults(Solution solution);
    Parameters update();
    Ui::guimain *ui;


private slots:

    //Begins calculation with parameters read from GUI
    void on_Runbutton_clicked();

    //Following functions provide basic logic for check boxes
    //i.e. selecting one deselects the other
    void on_fs_clicked();
    void on_s4_clicked();
    void on_singlemode_clicked();
    void on_rangemode_clicked();

    //Saves results from
    void on_Save_clicked();

    //Selection of results table cell controls crack and results plots
    void on_Resultstable_cellClicked(int row, int column);

    //Selection of pipe from dropdown box determines parameters below
    void on_materialname_currentIndexChanged(int index);
    void on_pipename_currentIndexChanged(int index);

    //Loads caseInputData.txt
    void on_action_Load_triggered();

    //Loads caseInputData.txt
    void on_action_Save_triggered();

    //Shows about dialog
    void on_actionAbout_triggered();

    //Changes independent variable
    void on_parameter_currentIndexChanged(int index);

private:

    int i;
    int j;
    int k;
    string file_name;
    string path;
    int exists;
    int check;

    //Fills table with values from the solution
    void fillTable(Solution solution);

    //Depending on values in GUI, plot graphs against different independent variable
    void plotHandler(Solution solution);

    //Plot handlers for results or profiles with appropriate titles and ranges
    void plotResults(vector<double> x, vector<double> y, string title, string xtitle, string ytitle, char savestate);
    void plotProfiles(vector<double> x, vector<double> y, string title, string xtitle, string ytitle, char savestate, char valid);
};

#endif // GUIMAIN_H

