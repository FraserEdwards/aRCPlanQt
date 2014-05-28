#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <ios>


#include "guimain.h"
#include "ui_guimain.h"
#include "about.h"
#include "dialog.h"
#include "qcustomplot.h"
#include "File.h"
#include "Constants.h"

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

void guimain::setnames(Parameters parameters, char dropdown)
{

extern File file;

ui -> path -> setText(QString::fromStdString(file.directory));

ui -> singlemode -> setCheckState(Qt::Unchecked);
ui -> rangemode -> setCheckState(Qt::Checked);

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

ui -> materialname -> setEditable(true);
ui -> materialname -> lineEdit() -> setReadOnly(false);
ui -> materialname -> lineEdit() -> setAlignment(Qt::AlignRight);

ui -> pipename -> setEditable(true);
ui -> pipename -> lineEdit() -> setReadOnly(false);
ui -> pipename -> lineEdit() -> setAlignment(Qt::AlignRight);

ui -> parameter -> setEditable(true);
ui -> parameter -> lineEdit() -> setReadOnly(true);
ui -> parameter -> lineEdit() -> setAlignment(Qt::AlignRight);

if(dropdown==0)
{
    ui -> materialname ->insertItems(0, QStringList() << "Soft PE80" << "Generic PE100" << "Soft PE100" << "Generic PE1" << "Generic PE2");
    ui -> pipename ->insertItems(0, QStringList() << "250mm_SDR11" << "250mm_SDR17" << "110mm_SDR11" << "110mm_SDR17" << "63mm_SDR11");
    ui -> parameter ->insertItems(0, QStringList() << "Normalised Crack Speed" << "Initial Pressure" << "Test Temperature");
}
else
{
    ui -> materialname ->lineEdit()->setText(QString::fromStdString(parameters.matID));
    ui -> pipename ->lineEdit()->setText(QString::fromStdString(parameters.pipeID));
}


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

}

void guimain::setresults(Solution solution)
{
    ui -> Resultstable ->clear();
    ui -> Resultstable ->setColumnCount(9);
    ui -> Resultstable ->setRowCount(solution.soln);
    ui -> Resultstable ->show();
    ui -> Resultstable->setHorizontalHeaderLabels(QStringList() << ui -> parameter -> currentText()  << "Decomp. Factor" << "Speed Factor"
                                                  << "Support Factor" << "Outflow Length" << "Flaring" << "Irwin Corten Crack Driving Force"
                                                  << "Crack driving force components" << "Normalised Total");

    for (i = 0; i < solution.soln; i++){
        switch(ui -> parameter -> currentIndex())
        {
            case 0:
                ui ->Resultstable ->setItem(i,0,new QTableWidgetItem(QString::number(solution.aDotc0[i+1])));
                break;
            case 1:
                ui ->Resultstable ->setItem(i,0,new QTableWidgetItem(QString::number(solution.p0bar[i+1])));
                break;
            case 2:
                ui ->Resultstable ->setItem(i,0,new QTableWidgetItem(QString::number(solution.tempDegC[i+1])));
                break;
        }

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

    extern File file;
    Parameters edited;
    edited = update();

    exists = file.check();

    if(!exists)
    {
        Simulation simulation;
        Solution solution;

        solution = simulation.run(edited);

        setresults(solution);

        if(edited.singlemode==2)
        {
            plothandler(solution);
        }
        else
        {
            plothandler(solution);
        }
    }
    else
    {
        dialog *e = new dialog;
        switch(exists)
        {
            case 1:
                e->Warning("Results folder couldn't be found, new folder created");
                break;
            case 2:
                e->Warning("Profile folder couldn't be found, new folder created");
                break;
            case 3:
                e->Warning("Log folder couldn't be found, new folder created");
                break;
            case 4:
                e->Warning("Please enter a valid directory");
                break;
        }
        e->show();
    }
}

void guimain::plothandler(Solution solution)
{
    switch(ui->parameter ->currentIndex())
    {
        case 0:
        {
            plotresults(solution.aDotc0, solution.decompression, "Decompression factor vs non-dimensional speed", "Non-dimensional speed", "Decompression factor",0);
            plotresults(solution.aDotc0, solution.outflowLength, "Outflow length vs non-dimensional speed", "Non-dimensional speed", "Outflow length",0);
            plotresults(solution.aDotc0, solution.m, "Support factor vs non-dimensional speed", "Non-dimensional speed", "Support factor",0);
            plotresults(solution.aDotc0, solution.alpha, "Speed factor vs non-dimensional speed", "Non-dimensional speed", "Speed factor",0);
            plotresults(solution.aDotc0, solution.gG0, "Non-dimensional crack driving force vs non-dimensional speed", "Non-dimensional speed", "Non-dimensional crack driving force",0);
            plotresults(solution.aDotc0, solution.gTotal, "Crack driving force vs non-dimensional speed", "Non-dimensional speed", "Crack driving force",0);
            break;
        }
        case 1:
        {
            plotresults(solution.p0bar, solution.decompression, "Decompression factor vs initial pressure", "Initial pressure", "Decompression factor",0);
            plotresults(solution.p0bar, solution.outflowLength, "Outflow length vs initial pressure", "Initial pressure", "Outflow length",0);
            plotresults(solution.p0bar, solution.m, "Support factor vs initial pressure", "Initial pressure", "Support factor",0);
            plotresults(solution.p0bar, solution.alpha, "Speed factor vs initial pressure", "Initial pressure", "Speed factor",0);
            plotresults(solution.p0bar, solution.gG0, "Non-dimensional crack driving force vs initial pressure", "Initial pressure", "Non-dimensional crack driving force",0);
            plotresults(solution.p0bar, solution.gTotal, "Crack driving force vs initial pressure", "Initial pressure", "Crack driving force",0);
            break;
        }
        case 2:
        {
            plotresults(solution.tempDegC, solution.decompression, "Decompression factor vs temperature", "Temperature", "Decompression factor",0);
            plotresults(solution.tempDegC, solution.outflowLength, "Outflow length vs temperature", "Temperature", "Outflow length",0);
            plotresults(solution.tempDegC, solution.m, "Support factor vs temperature", "Temperature", "Support factor",0);
            plotresults(solution.tempDegC, solution.alpha, "Speed factor vs temperature", "Temperature", "Speed factor",0);
            plotresults(solution.tempDegC, solution.gG0, "Non-dimensional crack driving force vs temperature", "Temperature", "Non-dimensional crack driving force",0);
            plotresults(solution.tempDegC, solution.gTotal, "Crack driving force vs temperature", "Temperature", "Crack driving force",0);
            break;
        }
    }
    if(solution.k==0)
    {

    }
    else
    {

        plotprofiles(solution.z, solution.w[solution.k], "Crack displacement profile", "Distance behind crack tip(mm)", "Crack opening displacement (m)",0);

    }
}

void guimain::plotprofiles(vector<double> x, vector<double> y, string title, string xtitle, string ytitle, char savestate)
{

    extern File file;

    path = (ui -> path -> text().toStdString()) + "Profiles/" + title;
    ui -> Crackplot -> addGraph();
    ui -> Crackplot -> graph(0) ->setPen(QPen(Qt::green));
    ui -> Crackplot -> graph(0)->setLineStyle(QCPGraph::lsNone);
    ui -> Crackplot -> graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));

    QVector<double> Qx = QVector<double>::fromStdVector(x);

    QVector<double> Qy = QVector<double>::fromStdVector(y);

    ui -> Crackplot -> graph(0) -> setData(Qx,Qy);

    ui -> Crackplot -> xAxis->setLabel(QString::fromStdString(xtitle));
    ui -> Crackplot -> yAxis->setLabel(QString::fromStdString(ytitle));

    double z1 = *max_element(x.begin(), x.end());
    double z2 = *max_element(y.begin(), y.end());

    ui -> Crackplot -> xAxis->setRange(0, z1+0.002);
    ui -> Crackplot -> yAxis->setRange(0, z2+0.002);
    ui -> Crackplot -> replot();

    if(!savestate)
    {
        ui -> Crackplot ->savePdf(QString::fromStdString(path)+".pdf",false,1000,1000,"Test","Test");
    }



}

void guimain::plotresults(vector<double> x, vector<double> y, string title, string xtitle, string ytitle, char savestate)
{
    extern File file;

    path = (ui -> path -> text().toStdString()) + "Results/" + title;
    ui -> Resultsplot -> addGraph();
    ui -> Resultsplot -> graph(0)->setLineStyle(QCPGraph::lsNone);
    ui -> Resultsplot -> graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));

    QVector<double> Qx = QVector<double>::fromStdVector(x);

    QVector<double> Qy = QVector<double>::fromStdVector(y);

    ui -> Resultsplot -> graph(0) -> setData(Qx,Qy);

    ui -> Resultsplot -> xAxis->setLabel(QString::fromStdString(xtitle));
    ui -> Resultsplot -> yAxis->setLabel(QString::fromStdString(ytitle));

    double z1 = *max_element(x.begin(), x.end());
    double z2 = *max_element(y.begin(), y.end());

    ui -> Resultsplot -> xAxis->setRange(0, z1+0.2);
    ui -> Resultsplot -> yAxis->setRange(0, z2+0.2);
    ui -> Resultsplot -> replot();
    if(!savestate)
    {
        ui -> Resultsplot ->savePdf(QString::fromStdString(path) + ".pdf",false, 1000, 1000,"Test","Test");
    }
}

Parameters guimain::update()
{

    Parameters temp;

    extern File file;
    file.directory = ui -> path -> text().toStdString();

    temp.varname = ui ->parameter ->currentIndex();

    temp.singlemode = ui -> singlemode -> checkState();
    temp.from = ui -> from -> text().toDouble();
    temp.to = ui -> to -> text().toDouble();
    temp.rangenumber = ui -> noofpoints -> text().toDouble();

    temp.fullScale = ui -> fs -> checkState();
    temp.isBackfilled = ui -> backfill -> checkState();
    temp.outflowModelOn = ui -> fixedlength -> checkState();

    temp.matID = ui -> materialname ->currentText().toStdString();
    temp.density = ui -> density -> text().toDouble();    
    temp.eDyn0degC = ui -> dynamicmodulus -> text().toDouble();    
    temp.dEdyndT = ui -> deltadynamicmodulus -> text().toDouble();    
    temp.creepModulus = ui -> creepmodulus -> text().toDouble();    
    temp.poisson = ui -> dynpoissonratio -> text().toDouble();
    temp.eDyn0degC = ui -> dynamicmodulus -> text().toDouble();
    temp.p0bar = ui ->initialpressure -> text().toDouble();

    temp.pipeID = ui -> pipename -> currentText().toStdString();
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
    temp.verbose = ui ->verbose ->checkState();

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

void guimain::on_Save_clicked()
{
    extern File file;
    file.writeresults();
}


void guimain::on_Resultstable_cellClicked(int row, int column)
{

    extern Solution solution;

    plotprofiles(solution.z, solution.w[row+1], "Crack displacement profile", "Distance behind crack tip(mm)", "Crack opening displacement (m)",0);
    switch(ui->parameter->currentIndex())
    {
        case 0:
        {
            switch(column)
            {
                case 1:
                    plotresults(solution.aDotc0, solution.decompression, "Decompression factor vs non-dimensional speed", "Non-dimensional speed", "Decompression factor",1);
                    break;
                case 2:
                    plotresults(solution.aDotc0, solution.alpha, "Speed factor vs non-dimensional speed", "Non-dimensional speed", "Speed factor",1);
                    break;
                case 3:
                    plotresults(solution.aDotc0, solution.m, "Support factor vs non-dimensional speed", "Non-dimensional speed", "Support factor",1);
                    break;
                case 4:
                    plotresults(solution.aDotc0, solution.outflowLength, "Outflow length vs non-dimensional speed", "Non-dimensional speed", "Outflow length",1);
                    break;
                case 6:
                    plotresults(solution.aDotc0, solution.g0, "Irwin Corten Crack Force vs non-dimensional speed", "Non-dimensional speed", "Irwin Corten Crack Driving Force",1);
                    break;
                case 7:
                    plotresults(solution.aDotc0, solution.gG0, "Crack driving force vs non-dimensional speed", "Non-dimensional speed", "Crack driving force",1);
                    break;
                case 8:
                    plotresults(solution.aDotc0, solution.gTotal, "Speed factor vs non-dimensional speed", "Non-dimensional speed", "Non-dimensional crack driving force",1);
                    break;
            }
            break;
        }
        case 1:
        {
            switch(column)
            {
                case 1:
                    plotresults(solution.p0bar, solution.decompression, "Decompression factor vs initial pressure", "Initial pressure", "Decompression factor",1);
                    break;
                case 2:
                    plotresults(solution.p0bar, solution.alpha, "Speed factor vs initial pressure", "Initial pressure", "Speed factor",1);
                    break;
                case 3:
                    plotresults(solution.p0bar, solution.m, "Support factor vs initial pressure", "Initial pressure", "Support factor",1);
                    break;
                case 4:
                    plotresults(solution.p0bar, solution.outflowLength, "Outflow length vs initial pressure ", "Initial pressure", "Outflow length",1);
                    break;
                case 6:
                    plotresults(solution.p0bar, solution.g0, "Irwin Corten Crack Force vs initial pressure", "Initial pressure", "Irwin Corten Crack Driving Force",1);
                    break;
                case 7:
                    plotresults(solution.p0bar, solution.gG0, "Crack driving force vs initial pressure", "Initial pressure", "Crack driving force",1);
                    break;
                case 8:
                    plotresults(solution.p0bar, solution.gTotal, "Speed factor vs initial pressure", "Initial pressure", "Non-dimensional crack driving force",1);
                    break;
            }
            break;
        }
        case 2:
        {
            switch(column)
            {
                case 1:
                    plotresults(solution.tempDegC, solution.decompression, "Decompression factor vs temperature", "Temperature", "Decompression factor",1);
                    break;
                case 2:
                    plotresults(solution.tempDegC, solution.alpha, "Speed factor vs temperature", "Temperature", "Speed factor",1);
                    break;
                case 3:
                    plotresults(solution.tempDegC, solution.m, "Support factor vs temperature", "Temperature", "Support factor",1);
                    break;
                case 4:
                    plotresults(solution.tempDegC, solution.outflowLength, "Outflow length vs temperature", "Temperature", "Outflow length",1);
                    break;
                case 6:
                    plotresults(solution.tempDegC, solution.g0, "Irwin Corten Crack Force vs temperature", "Temperature", "Irwin Corten Crack Driving Force",1);
                    break;
                case 7:
                    plotresults(solution.tempDegC, solution.gG0, "Crack driving force vs temperature", "Temperature", "Crack driving force",1);
                    break;
                case 8:
                    plotresults(solution.tempDegC, solution.gTotal, "Speed factor vs temperature", "Temperature", "Non-dimensional crack driving force",1);
                    break;
            }
            break;
        }
    }
}

void guimain::on_materialname_currentIndexChanged(int index)
{

    ui -> density -> setText(QString::number(Parameters::density_lib[index]));
    ui -> dynamicmodulus -> setText(QString::number(Parameters::eDyn0degC_lib[index]));
    ui -> deltadynamicmodulus -> setText(QString::number(Parameters::dEdyndT_lib[index]));
    ui -> creepmodulus -> setText(QString::number(Parameters::creepModulus_lib[index]));
    ui -> dynpoissonratio -> setText(QString::number(Parameters::poisson_lib[index]));

}

void guimain::on_pipename_currentIndexChanged(int index)
{

    ui -> outsidediameter -> setText(QString::number(Parameters::diameter_lib[index]));
    ui -> sdr -> setText(QString::number(Parameters::sdr_lib[index]));

}

void guimain::on_action_Load_triggered()
{

    extern File file;

    switch(file.loadcheck("caseInputData.txt"))
    {
        case 0:
        {
            ConfigFile config(file.directory + "caseInputData.txt");
            Parameters temp(config);

            dialog *e = new dialog;
            e->Warning("caseInputData.txt was loaded successfully");
            e->show();

            setnames(temp,1);
            break;
        }
        case 1:
        {
            dialog *e = new dialog;
            e->Warning("caseInputData.txt could not be found in: \n \n" + file.directory);
            e->show();
            break;
        }

    }

}

void guimain::on_action_Save_triggered()
{
    extern File file;

    Parameters temp;
    temp = update();
    dialog *e = new dialog;
    filename = "caseInputData.txt";
    if(!file.casehandler(temp, filename))
    {
        e->Warning("caseInputData.txt saved successfully");

    }
    else
    {
        e->Warning(filename + " not saved successfully, enter a viable name");
    }
    e->show();
}

void guimain::on_actionAbout_triggered()
{
    about *d = new about;
    d->show();
    d->setWindowTitle("About");
}

void guimain::on_parameter_currentIndexChanged(int index)
{
    ui -> from -> setText(QString::number(Parameters::from_lib[index]));
    ui -> to -> setText(QString::number(Parameters::to_lib[index]));
}
