#ifndef GUIMAIN_H
#define GUIMAIN_H

#include <QMainWindow>
#include <QLineEdit>
#include "Parameters.h"
#include "Solution.h"


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
    friend class Parameters;

private slots:

    void on_Runbutton_clicked();

    void on_Tabs_tabBarClicked(int index);

    void on_rangemode_stateChanged(int arg1);

    void on_singlemode_stateChanged(int arg1);

    void on_parameter_currentTextChanged(const QString &arg1);

    void on_from_textChanged(const QString &arg1);

    void on_to_textChanged(const QString &arg1);

    void on_noofpoints_textChanged(const QString &arg1);

    void on_materialname_textChanged(const QString &arg1);

    void on_outsidediameter_textChanged(const QString &arg1);

    void on_density_textChanged(const QString &arg1);

    void on_dynamicmodulus_textChanged(const QString &arg1);

    void on_deltadynamicmodulus_textChanged(const QString &arg1);

    void on_creepmodulus_textChanged(const QString &arg1);

    void on_dynpoissonratio_textChanged(const QString &arg1);

    void on_pipename_textChanged(const QString &arg1);

    void on_sdr_textChanged(const QString &arg1);

    void on_groovedepth_textChanged(const QString &arg1);

    void on_relativediameter_textChanged(const QString &arg1);

    void on_fs_stateChanged(int arg1);

    void on_s4_stateChanged(int arg1);

    void on_backfill_stateChanged(int arg1);

    void on_testtemperature_textChanged(const QString &arg1);

    void on_initialpressure_textChanged(const QString &arg1);

    void on_backfilldepth_textChanged(const QString &arg1);

    void on_backfilldensity_textChanged(const QString &arg1);

    void on_solidfraction_textChanged(const QString &arg1);

    void on_waterfraction_textChanged(const QString &arg1);

    void on_fixedlength_stateChanged(int arg1);

    void on_initiallength_textChanged(const QString &arg1);

    void on_crackspeed_textChanged(const QString &arg1);

    void on_fdnumber_textChanged(const QString &arg1);

    void on_plotcrack_stateChanged(int arg1);

    void on_Resultscombo_currentTextChanged(const QString &arg1);

    void on_Crackspeedcombo_currentTextChanged(const QString &arg1);

    void on_outflowresult_textChanged(const QString &arg1);

    void on_cortendriving_textChanged(const QString &arg1);

    void on_normalisedforce_textChanged(const QString &arg1);

private:
    Ui::guimain *ui;
};

#endif // GUIMAIN_H
