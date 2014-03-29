#include <QString>
#include <iostream>

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

    Parameters edited;
    edited = update();
    cout << endl << "Backfilled: " << edited.isBackfilled << endl;

    Simulation simulation;
    Solution solution;

    solution = simulation.run(edited);

    setresults(solution);

}

Parameters guimain::update()
{

    Parameters temp;

    temp.fullScale = ui -> fs -> checkState();
    temp.isBackfilled = ui -> backfill -> checkState();
    temp.outflowModelOn = ui -> fixedlength -> checkState();

    temp.density = ui -> density -> text().toDouble();
    temp.eDyn0degC = ui -> dynamicmodulus -> text().toDouble();
    temp.dEdyndT = ui -> deltadynamicmodulus -> text().toDouble();
    temp.creepModulus = ui -> creepmodulus -> text().toDouble();
    temp.poisson = ui -> dynpoissonratio -> text().toDouble();
    temp.eDyn0degC = ui -> dynamicmodulus -> text().toDouble();

    temp.diameter = ui -> outsidediameter -> text().toDouble();
    temp.sdr = ui -> sdr -> text().toDouble();
    temp.notchDepth = ui -> groovedepth -> text().toDouble();
    temp.diameterCreepRatio = ui -> relativediameter -> text().toDouble();
    temp.tempDegC = ui -> testtemperature -> text().toDouble();
    temp.backfillDepth = ui -> backfilldepth -> text().toDouble();
    temp.backfillDensity = ui -> backfilldensity -> text().toDouble();
    temp.solidInsidePipe = ui -> solidfraction -> text().toDouble();
    temp.waterInsidePipe = ui -> waterfraction -> text().toDouble();

    temp.lambda = ui -> initiallength -> text().toDouble();
    temp.aDotc0 = ui -> crackspeed -> text().toDouble();
    temp.elementsInL = ui -> fdnumber -> text().toDouble();

    return temp;
}






