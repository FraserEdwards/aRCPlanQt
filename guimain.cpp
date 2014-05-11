#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <fstream>
#include <ios>

#include "guimain.h"
#include "ui_guimain.h"
#include "qcustomplot.h"
#include "File.h"

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
    ui -> parameter ->insertItems(0, QStringList() << "Normalised Crack Speed" << "Initial Pressure" << "Test Temperaure");
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
        plothandler(solution);
    }
    else
    {
        cout << exists;
        switch(exists)
        {
            case 1:
                ui -> Information ->setText("Results folder couldn't be found, new folder created");
                break;
            case 2:
                ui -> Information -> setText("Profile folder couldn't be found, new folder created");
                break;
            case 3:
                ui -> Information -> setText("Log folder couldn't be found, new folder created");
                break;
            case 4:
                ui -> Information -> setText("Please enter a valid directory");
                break;
        }
    }
}

void guimain::plothandler(Solution solution)
{

    plotresults(solution.aDotc0, solution.decompression, "Decompression factor vs non-dimensional speed", "Non-dimensional speed", "Decompression factor",0);
    plotresults(solution.aDotc0, solution.outflowLength, "Outflow length vs non-dimensional speed", "Non-dimensional speed", "Outflow length",0);
    plotresults(solution.aDotc0, solution.gTotal, "Crack driving force vs non-dimensional speed", "Non-dimensional speed", "Crack driving force",0);
    plotresults(solution.aDotc0, solution.m, "Support factor vs non-dimensional speed", "Non-dimensional speed", "Support factor",0);
    plotresults(solution.aDotc0, solution.alpha, "Speed factor vs non-dimensional speed", "Non-dimensional speed", "Speed factor",0);
    plotresults(solution.aDotc0, solution.gG0, "Speed factor vs non-dimensional speed", "Non-dimensional speed", "Non-dimensional crack driving force",0);

}

void guimain::plotresults( vector<double> x, vector<double> y, string title, string xtitle, string ytitle, char savestate)
{
    extern File file;

    path = (ui -> path -> text().toStdString()) + "Results/" + title;
    ui -> Resultsplot -> addGraph();

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
        ui -> Resultsplot ->savePdf(QString::fromStdString(path)+".pdf",false,1000,1000,"Test","Test");
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

void guimain::on_Save_clicked()
{

    extern File file;

    filename = "Results.csv";

    results.open((file.directory + "Results/" + filename).c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);


    for (k = 0; k < ui -> Resultstable -> rowCount(); k++)
    {
        if(k == 0)
        {
            results << ui -> parameter -> currentText().toStdString() << ",Decomp. factor,Speed factor,Support factor,Outflow length,Flaring,Irwin Corten force,Crack driving force,Normalised total,\n";
        }

        for (j = 0; j < ui -> Resultstable -> columnCount(); j++)
        {

            QString temp = ui ->Resultstable->item(k,j) -> text();
            if (j == (ui -> Resultstable -> columnCount())-1)
            {
                results << temp.toStdString() << "\n";
            }
            else
            {
                results << temp.toStdString() << ",";
            }

        }

    }

    results.close();

}


void guimain::on_Resultstable_cellClicked(int row, int column)
{

    Solution temp;
    for(k = 0; k < ui -> Resultstable -> rowCount(); k++)
    {

        double indvar = ui -> Resultstable -> item(k,0) ->text().toDouble();
        double depvar = ui -> Resultstable -> item(k,column) -> text().toDouble();

        temp.aDotc0.push_back(indvar);
        temp.forplot.push_back(depvar);

    }

    switch(column)
    {
        case 1:
            plotresults(temp.aDotc0, temp.forplot, "Decompression factor vs non-dimensional speed", "Non-dimensional speed", "Decompression factor",1);
            break;
        case 2:
            plotresults(temp.aDotc0, temp.forplot, "Speed factor vs non-dimensional speed", "Non-dimensional speed", "Speed factor",1);
            break;
        case 3:
            plotresults(temp.aDotc0, temp.forplot, "Support factor vs non-dimensional speed", "Non-dimensional speed", "Support factor",1);
            break;
        case 4:
            plotresults(temp.aDotc0, temp.forplot, "Outflow length vs non-dimensional speed", "Non-dimensional speed", "Outflow length",1);
            break;
        case 7:
            plotresults(temp.aDotc0, temp.forplot, "Crack driving force vs non-dimensional speed", "Non-dimensional speed", "Crack driving force",1);
            break;
        case 8:
            plotresults(temp.aDotc0, temp.forplot, "Speed factor vs non-dimensional speed", "Non-dimensional speed", "Non-dimensional crack driving force",1);
            break;
     }

}

void guimain::on_materialname_currentIndexChanged(int index)
{
    double density_lib[5] = {938.0, 960.0, 938.0, 960.0, 950.0};
    double eDyn0degC_lib[5] = {2.62, 3.17, 1.31, 1.585, 1.5};
    double dEdyndT_lib[5] = {-0.037, -0.0427, -0.0185, -0.02135, -0.02};
    double creepModulus_lib[5] = {0.3, 0.3, 0.3, 0.3, 0.3};
    double poisson_lib[5] = {0.38, 0.38, 0.38, 0.38, 0.38};

    ui -> density -> setText(QString::number(density_lib[index]));
    ui -> dynamicmodulus -> setText(QString::number(eDyn0degC_lib[index]));
    ui -> deltadynamicmodulus -> setText(QString::number(dEdyndT_lib[index]));
    ui -> creepmodulus -> setText(QString::number(creepModulus_lib[index]));
    ui -> dynpoissonratio -> setText(QString::number(poisson_lib[index]));

}

void guimain::on_pipename_currentIndexChanged(int index)
{

    double diameter_lib[5] = {250.0, 250.0, 110.0, 110.0, 63.0};
    double sdr_lib[5] = {11.0, 17.6, 11.0, 17.6, 11.0};
    double notchDepth_lib[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    double diameterCreepRatio_lib[5] = {1.0, 1.0, 1.0, 1.0, 1.0};

    ui -> outsidediameter -> setText(QString::number(diameter_lib[index]));
    ui -> sdr -> setText(QString::number(sdr_lib[index]));
    ui -> groovedepth -> setText(QString::number(notchDepth_lib[index]));
    ui -> relativediameter -> setText(QString::number(diameterCreepRatio_lib[index]));


}

void guimain::on_action_Load_triggered()
{

    extern File file;

    switch(file.loadcheck("caseInputData.txt"))
    {
        case 0:
        {
            ui -> Information -> setText("caseInputData.txt was loaded successfully");
            ConfigFile config(file.directory + "caseInputData.txt");
            Parameters temp;
            temp.collect(config);
            setnames(temp,1);
            break;
        }
        case 1:
        {
            ui -> Information -> setText("caseInputData.txt could not be found in" + QString::fromStdString(file.directory));
            break;
        }

    }

}

void guimain::on_action_Save_triggered()
{
    extern File file;

    Parameters temp;
    temp = update();

    file.write(temp);
}

void guimain::on_actionAbout_triggered()
{


}
