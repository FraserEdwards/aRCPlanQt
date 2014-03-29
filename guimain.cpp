#include <QString>

#include "guimain.h"
#include "ui_guimain.h"

guimain::guimain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::guimain)
{
    ui->setupUi(this);
}

guimain::~guimain()
{
    delete ui;
}

void guimain::setnames(Parameters parameters)
{

ui -> singlemode -> setCheckState(Qt::Checked);

if(parameters.fullScale)
{
    ui->fs->setCheckState(Qt::Checked);
    ui->s4->setCheckState(Qt::Unchecked);
}
else
{
    ui->fs->setCheckState(Qt::Unchecked);
    ui->s4->setCheckState(Qt::Checked);
}

if(parameters.isBackfilled)
   {ui->backfill->setCheckState(Qt::Checked);}
else
   {ui->backfill->setCheckState(Qt::Unchecked);}

if(parameters.outflowModelOn)
   {ui->fixedlength->setCheckState(Qt::Checked);}
else
   {ui->fixedlength->setCheckState(Qt::Unchecked);}


ui -> materialname -> setAlignment(Qt::AlignRight);
ui ->materialname->setText(QString::fromStdString(parameters.matID));

ui -> density -> setAlignment(Qt::AlignRight);
ui -> density->setText(QString::number(parameters.density));

ui -> dynamicmodulus -> setAlignment(Qt::AlignRight);
ui -> dynamicmodulus ->setText(QString::number(parameters.eDyn0degC));

ui -> deltadynamicmodulus -> setAlignment(Qt::AlignRight);
ui -> deltadynamicmodulus ->setText(QString::number(parameters.dEdyndT));

ui -> creepmodulus -> setAlignment(Qt::AlignRight);
ui -> creepmodulus -> setText(QString::number(parameters.creepModulus));

ui -> dynpoissonratio -> setAlignment(Qt::AlignRight);
ui -> dynpoissonratio -> setText(QString::number(parameters.poisson));

ui -> from -> setAlignment(Qt::AlignRight);
ui -> from -> setText(QString::number(0));

ui -> to -> setAlignment(Qt::AlignRight);
ui -> to -> setText(QString::number(1));

ui -> noofpoints -> setAlignment(Qt::AlignRight);
ui -> noofpoints -> setText(QString::number(50));

ui -> pipename -> setAlignment(Qt::AlignRight);
ui -> pipename->setText(QString::fromStdString(parameters.pipeID));

ui -> outsidediameter -> setAlignment(Qt::AlignRight);
ui -> outsidediameter -> setText(QString::number(parameters.diameter));

ui -> sdr -> setAlignment(Qt::AlignRight);
ui -> sdr -> setText(QString::number(parameters.sdr));

ui -> groovedepth -> setAlignment(Qt::AlignRight);
ui -> groovedepth -> setText(QString::number(parameters.notchDepth));

ui -> relativediameter -> setAlignment(Qt::AlignRight);
ui -> relativediameter -> setText(QString::number(parameters.diameterCreepRatio));

ui -> testtemperature -> setAlignment(Qt::AlignRight);
ui -> testtemperature -> setText(QString::number(parameters.tempDegC));

ui -> initialpressure -> setAlignment(Qt::AlignRight);
ui -> initialpressure -> setText(QString::number(parameters.p0bar));

ui -> backfilldepth -> setAlignment(Qt::AlignRight);
ui -> backfilldepth -> setText(QString::number(parameters.backfillDepth));

ui -> backfilldensity -> setAlignment(Qt::AlignRight);
ui -> backfilldensity -> setText(QString::number(parameters.backfillDensity));

ui -> solidfraction -> setAlignment(Qt::AlignRight);
ui -> solidfraction -> setText(QString::number(parameters.solidInsidePipe));

ui -> waterfraction -> setAlignment(Qt::AlignRight);
ui -> waterfraction -> setText(QString::number(parameters.waterInsidePipe));

ui -> initiallength -> setAlignment(Qt::AlignRight);
ui -> initiallength -> setText(QString::number(parameters.lambda));

ui -> crackspeed -> setAlignment(Qt::AlignRight);
ui -> crackspeed -> setText(QString::number(parameters.aDotc0));

ui -> fdnumber -> setAlignment(Qt::AlignRight);
ui -> fdnumber -> setText(QString::number(parameters.elementsInL));

ui -> parameter -> setEditable(true);
ui -> parameter -> lineEdit() -> setReadOnly(true);
ui -> parameter -> lineEdit() -> setAlignment(Qt::AlignRight);
ui -> parameter ->insertItems(0, QStringList() << "Normalised Crack Speed" << "Initial Pressure" << "Test Temperaure");

}

void guimain::setresults(Solution solution)
{

    ui -> outflowresult -> setAlignment(Qt::AlignRight);
    ui -> outflowresult ->setText(QString::number(solution.outflowLength[2]));

    ui -> cortendriving -> setAlignment(Qt::AlignRight);
    ui -> cortendriving ->setText(QString::number(solution.g0[2]));

    ui -> normalisedforce -> setAlignment(Qt::AlignRight);
    ui -> normalisedforce ->setText(QString::number(solution.gG0[2]));

}


void guimain::on_Runbutton_clicked()
{

    Parameters::update(guimain b);

}

void guimain::on_rangemode_stateChanged(int arg1)
{

}

void guimain::on_singlemode_stateChanged(int arg1)
{

}

void guimain::on_parameter_currentTextChanged(const QString &arg1)
{

}

void guimain::on_from_textChanged(const QString &arg1)
{

}

void guimain::on_to_textChanged(const QString &arg1)
{

}

void guimain::on_noofpoints_textChanged(const QString &arg1)
{

}

void guimain::on_materialname_textChanged(const QString &arg1)
{

}

void guimain::on_outsidediameter_textChanged(const QString &arg1)
{

}

void guimain::on_density_textChanged(const QString &arg1)
{

}

void guimain::on_dynamicmodulus_textChanged(const QString &arg1)
{

}

void guimain::on_Tabs_tabBarClicked(int index)
{

}

void guimain::on_deltadynamicmodulus_textChanged(const QString &arg1)
{

}

void guimain::on_creepmodulus_textChanged(const QString &arg1)
{

}

void guimain::on_dynpoissonratio_textChanged(const QString &arg1)
{

}

void guimain::on_pipename_textChanged(const QString &arg1)
{

}

void guimain::on_sdr_textChanged(const QString &arg1)
{

}

void guimain::on_groovedepth_textChanged(const QString &arg1)
{

}

void guimain::on_relativediameter_textChanged(const QString &arg1)
{

}

void guimain::on_fs_stateChanged(int arg1)
{

}

void guimain::on_s4_stateChanged(int arg1)
{

}

void guimain::on_backfill_stateChanged(int arg1)
{

}

void guimain::on_testtemperature_textChanged(const QString &arg1)
{

}

void guimain::on_initialpressure_textChanged(const QString &arg1)
{

}

void guimain::on_backfilldepth_textChanged(const QString &arg1)
{

}

void guimain::on_backfilldensity_textChanged(const QString &arg1)
{

}

void guimain::on_solidfraction_textChanged(const QString &arg1)
{

}

void guimain::on_waterfraction_textChanged(const QString &arg1)
{

}

void guimain::on_fixedlength_stateChanged(int arg1)
{

}

void guimain::on_initiallength_textChanged(const QString &arg1)
{

}

void guimain::on_crackspeed_textChanged(const QString &arg1)
{

}

void guimain::on_fdnumber_textChanged(const QString &arg1)
{

}

void guimain::on_plotcrack_stateChanged(int arg1)
{

}

void guimain::on_Resultscombo_currentTextChanged(const QString &arg1)
{

}

void guimain::on_Crackspeedcombo_currentTextChanged(const QString &arg1)
{

}

void guimain::on_outflowresult_textChanged(const QString &arg1)
{

}

void guimain::on_cortendriving_textChanged(const QString &arg1)
{

}

void guimain::on_normalisedforce_textChanged(const QString &arg1)
{

}


void guimain::on_Runbutton_clicked(bool checked)
{

}
