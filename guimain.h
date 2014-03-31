#ifndef GUIMAIN_H
#define GUIMAIN_H

#include <QMainWindow>
#include <QLineEdit>
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

    void setnames(Parameters parameters);
    void setresults(Solution solution);
    Parameters update();

private slots:

    void on_Runbutton_clicked();

    void on_fs_clicked();

    void on_s4_clicked();

    void on_singlemode_clicked();

    void on_rangemode_clicked();


private:
    int i;
    Ui::guimain *ui;
    void filltable(Solution solution);
};

#endif // GUIMAIN_H
