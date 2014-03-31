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
   {ui->backfill->setCheckState(Qt::Unchecked);}
else
   {ui->backfill->setCheckState(Qt::Checked);}

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
ui -> fdnumber -> setText(QString::number(parameters.elementsinl));

ui -> parameter -> setEditable(true);
ui -> parameter -> lineEdit() -> setReadOnly(true);
ui -> parameter -> lineEdit() -> setAlignment(Qt::AlignRight);
ui -> parameter ->insertItems(0, QStringList() << "Normalised Crack Speed" << "Initial Pressure" << "Test Temperaure");

}

void guimain::setresults(Solution solution)
{
    ui -> Resultstable ->clear();
    ui -> Resultstable ->setColumnCount(9);
    ui ->Resultstable ->setRowCount(solution.soln);
    ui -> Resultstable ->show();
    ui -> Resultstable->setHorizontalHeaderLabels(QStringList() << "Variable" << "Decomp. Factor" << "Speed Factor"
                                                  << "Support Factor" << "Outflow Length" << "Flaring" << "Irwin Corten Crack Driving Force"
                                                  << "Crack driving force components" << "Normalised Total");

    for (i = 0; i < solution.soln; i++){
    ui ->Resultstable ->setItem(i,0,new QTableWidgetItem(QString::number(solution.aDotc0[i+1])));
    ui ->Resultstable ->setItem(i,1,new QTableWidgetItem(QString::number(solution.decompression[i+1])));
    ui ->Resultstable ->setItem(i,2,new QTableWidgetItem(QString::number(solution.alpha[i+1])));
    ui ->Resultstable ->setItem(i,3,new QTableWidgetItem(QString::number(solution.m[i+1])));
    ui ->Resultstable ->setItem(i,4,new QTableWidgetItem(QString::number(solution.outflowLength[i+1])));
    ui ->Resultstable ->setItem(i,5,new QTableWidgetItem(QString::fromStdString("   ")));
    ui ->Resultstable ->setItem(i,6,new QTableWidgetItem(QString::number(solution.g0[i+1])));
    ui ->Resultstable ->setItem(i,7,new QTableWidgetItem(QString::number(solution.gG0[i+1])));
    ui ->Resultstable ->setItem(i,8,new QTableWidgetItem(QString::number(solution.gTotal[i+1])));
    }

}


void guimain::on_Runbutton_clicked()
{

    Parameters edited;
    Simulation simulation;
    Solution solution;

    edited = update();
//    cout << endl << "OutflowModelOn: " << edited.outflowModelOn << endl;
//    cout << endl << "Lambda: " << edited.lambda << endl;
//    cout << endl << "AnalyticalSolutionMode: " << edited.analyticalSolutionMode << endl;
//    cout << endl << "Mode: " << edited.mode << endl;
//    cout << endl << "Range number: " << edited.rangenumber << endl;
//    cout << endl << "aDotc0: " << edited.aDotc0 << endl;
//    cout << endl << "elementsinl: " << edited.elementsinl << endl;
//    cout << endl << "fullScale: " << edited.fullScale << endl;
//    cout << endl << "tempDegC: " << edited.tempDegC << endl;
//    cout << endl << "p0bar: " << edited.p0bar << endl;
//    cout << endl << "isBackfilled: " << edited.isBackfilled << endl;
//    cout << endl << "backfillDepth: " << edited.backfillDepth << endl;
//    cout << endl << "backfillDensity: " << edited.backfillDensity << endl;
//    cout << endl << "solidInsidePipe: " << edited.solidInsidePipe << endl;
//    cout << endl << "waterInsidePipe: " << edited.waterInsidePipe << endl;
//    cout << endl << "Diameter: " << edited.diameter << endl;
//    cout << endl << "sdr: " << edited.sdr << endl;
//    cout << endl << "notchDepth: " << edited.notchDepth << endl;
//    cout << endl << "diameterCreepRatio: " << edited.diameterCreepRatio << endl;
//    cout << endl << "h: " << edited.h << endl;
//    cout << endl << "crackWidth: " << edited.crackWidth << endl;
//    cout << endl << "hOverR: " << edited.hOverR << endl;
//    cout << endl << "radius: " << edited.radius << endl;
//    cout << endl << "density: " << edited.density << endl;
//    cout << endl << "eDyn0degC: " << edited.eDyn0degC << endl;
//    cout << endl << "dEdyndT: " << edited.dEdyndT << endl;
//    cout << endl << "creepModulus: " << edited.creepModulus << endl;
//    cout << endl << "poisson: " << edited.poisson << endl;

    solution = simulation.run(edited);

    setresults(solution);

}

Parameters guimain::update()
{

    Parameters temp;

    temp.fullScale = ui -> fs -> checkState();
    temp.isBackfilled = ui -> backfill -> checkState();
    temp.outflowModelOn = ui -> fixedlength -> checkState();

    temp.rangenumber = ui -> noofpoints -> text().toDouble();
    temp.density = ui -> density -> text().toDouble();    
    temp.eDyn0degC = ui -> dynamicmodulus -> text().toDouble();    
    temp.dEdyndT = ui -> deltadynamicmodulus -> text().toDouble();    
    temp.creepModulus = ui -> creepmodulus -> text().toDouble();    
    temp.poisson = ui -> dynpoissonratio -> text().toDouble();
    temp.eDyn0degC = ui -> dynamicmodulus -> text().toDouble();
    temp.p0bar = ui ->initialpressure -> text().toDouble();

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
    temp.elementsinl = ui -> fdnumber -> text().toDouble();

    temp.h = temp.diameter/temp.sdr/Constants::kilo; // (m)
    temp.hOverR = 2.0/ (temp.sdr-1);
    temp.radius = temp.h / temp.hOverR;

    temp.crackWidth = temp.diameter / temp.sdr - temp.notchDepth; //(mm, giving kJ/m2 for G; not necessarily equal to h)

    temp.dynamicModulus = temp.eDyn0degC + temp.tempDegC * temp.dEdyndT;

    return temp;
}



void guimain::on_fs_clicked()
{
    if(ui -> fs -> checkState())
    {
    ui -> s4 -> setCheckState(Qt::Unchecked);

    }
    else
    {
    ui -> s4 -> setCheckState(Qt::Checked);
    }
}


void guimain::on_s4_clicked()
{
    if(ui-> s4 -> checkState())
    {
    ui -> fs -> setCheckState(Qt::Unchecked);

    }
    else
    {
    ui -> fs -> setCheckState(Qt::Checked);
    }
}

void guimain::on_singlemode_clicked()
{
    if(ui->singlemode -> checkState())
    {
    ui -> rangemode -> setCheckState(Qt::Unchecked);

    }
    else
    {
    ui -> rangemode -> setCheckState(Qt::Checked);
    }
}

void guimain::on_rangemode_clicked()
{
    if(ui->rangemode -> checkState())
    {
    ui -> singlemode -> setCheckState(Qt::Unchecked);
    }
    else
    {
    ui -> singlemode -> setCheckState(Qt::Checked);
    }
}

void guimain::filltable(Solution solution)
{


}
