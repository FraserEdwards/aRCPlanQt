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

    void on_Runbutton_clicked();

    void on_fs_clicked();

    void on_s4_clicked();

    void on_singlemode_clicked();

    void on_rangemode_clicked();

    void on_Save_clicked();

    void on_Resultstable_cellClicked(int row, int column);

    void on_materialname_currentIndexChanged(int index);

    void on_pipename_currentIndexChanged(int index);

    void on_action_Load_triggered();

    void on_action_Save_triggered();

    void on_actionAbout_triggered();

private:

    int i;
    int j;
    int k;
    string filename;
    string path;
    int exists;

    ofstream results;

    void filltable(Solution solution);
    void plothandler(Solution solution);
    void plotresults(vector<double> x, vector<double> y, string title, string xtitle, string ytitle, char savestate);
    void plotprofiles(vector<double> x, vector<double> y, string title, string xtitle, string ytitle, char savestate);
};

#endif // GUIMAIN_H

