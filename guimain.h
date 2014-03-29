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

private:
    Ui::guimain *ui;
};

#endif // GUIMAIN_H
