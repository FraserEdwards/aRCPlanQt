#include <iostream>
using namespace std;

#include "Parameters.h"
#include "ConfigFile.h"
#include "File.h"

    string Parameters::pipeID_lib[5] = {"250mm_SDR11", "250mm_SDR17", "110mm_SDR11", "110mm_SDR17", "63mm_SDR11"};
    double Parameters::diameter_lib[5] = {250.0, 250.0, 110.0, 110.0, 63.0};
    double Parameters::sdr_lib[5] = {11.0, 17.6, 11.0, 17.6, 11.0};
    double Parameters::notchDepth_lib[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    double Parameters::diameterCreepRatio_lib[5] = {1.0, 1.0, 1.0, 1.0, 1.0};

    double Parameters::density_lib[5] = {938.0, 960.0, 938.0, 960.0, 950.0};
    double Parameters::eDyn0degC_lib[5] = {2.62, 3.17, 1.31, 1.585, 1.5};
    double Parameters::dEdyndT_lib[5] = {-0.037, -0.0427, -0.0185, -0.02135, -0.02};
    double Parameters::creepModulus_lib[5] = {0.3, 0.3, 0.3, 0.3, 0.3};
    double Parameters::poisson_lib[5] = {0.38, 0.38, 0.38, 0.38, 0.38};


//Null constructor
Parameters::Parameters()
{

    outflowModelOn = 0;
    lambda = 3.0;
    solutionmethod = 2;
    singlemode = 2;
    rangenumber = 0;
    elementsinl = 10;
    aDotc0 = 0.5;
    varname = 0;

    fullScale = 2;
    tempDegC = 0.0;
    p0bar = 5.0;
    isBackfilled = 2;
    backfillDepth = 100;
    backfillDensity = 2200;
    solidInsidePipe = 0.25;
    waterInsidePipe = 0.25;

    h=0.0;
    hOverR=0.0;
    radius=0.0;
    crackWidth=0.0;

    geometryupdate(0);
    materialupdate(0);

    conditionToTemperature();

}

void Parameters::geometryupdate(int n)
{
    pipeID = Parameters::pipeID_lib[n];
    diameter = diameter_lib[n];
    sdr = sdr_lib[n];
    notchDepth = notchDepth_lib[n];
    diameterCreepRatio = diameterCreepRatio_lib[n];

}

void Parameters::materialupdate(int n)
{
    matID = matID[n];
    density = density_lib[n];
    eDyn0degC = eDyn0degC_lib[n];
    dEdyndT = dEdyndT_lib[n];
    creepModulus = creepModulus_lib[n];
    poisson = poisson_lib[n];
}

//Constructor
Parameters::Parameters(ConfigFile config)
{
    config.readInto(outflowModelOn, "outflowModelOn");
    config.readInto(lambda, "lambda");
    config.readInto(solutionmethod, "solutionmethod");
    config.readInto(singlemode, "Mode");
    config.readInto(rangenumber, "numberOfSpeedValues");
    config.readInto(elementsinl, "elementsInL");
    config.readInto(aDotc0, "aDotc0");

    config.readInto(pipeID, "pipeID");
    config.readInto(diameter, "diameter");
    config.readInto(sdr, "sdr");
    config.readInto(notchDepth, "notchDepth");
    config.readInto(diameterCreepRatio, "diameterCreepRatio");

    config.readInto(matID, "matID" );
    config.readInto(density, "density" );
    config.readInto(eDyn0degC, "eDyn0degC" );
    config.readInto(dEdyndT, "dEdyndT" );
    config.readInto(creepModulus, "creepModulus" );
    config.readInto(poisson, "poisson" );

    config.readInto(fullScale, "fullScale");
    config.readInto(tempDegC, "tempDegC");
    config.readInto(p0bar, "p0bar");
    config.readInto(isBackfilled, "isBackfilled");
    config.readInto(backfillDepth, "backfillDepth");
    config.readInto(backfillDensity, "backfillDensity");
    config.readInto(solidInsidePipe, "solidInsidePipe");
    config.readInto(waterInsidePipe, "waterInsidePipe");
}

//Creates the "=" operator for this class
Parameters& Parameters::operator=(const Parameters& rhs)
{
    outflowModelOn = rhs.outflowModelOn;
    lambda = rhs.lambda;
    solutionmethod = rhs.solutionmethod;
    singlemode = rhs.singlemode;
    rangenumber = rhs.rangenumber;
    elementsinl = rhs.elementsinl;
    aDotc0 =  rhs.aDotc0;
    from = rhs.from;
    to = rhs.to;
    varname = rhs.varname;

    pipeID = rhs.pipeID;
    diameter = rhs.diameter;
    sdr = rhs.sdr;
    notchDepth = rhs.notchDepth;
    diameterCreepRatio = rhs.diameterCreepRatio;
    radius = rhs.radius;
    h = rhs.h;
    hOverR = rhs.hOverR;
    crackWidth = rhs.crackWidth;

    matID = rhs.matID;
    density = rhs.density;
    eDyn0degC = rhs.eDyn0degC;
    dEdyndT = rhs.dEdyndT;
    dynamicModulus = rhs.dynamicModulus;
    creepModulus = rhs.creepModulus;
    poisson = rhs.poisson;

    methodID = rhs.methodID;
    fullScale = rhs.fullScale;
    tempDegC = rhs.tempDegC;
    p0bar = rhs.p0bar;
    isBackfilled = rhs.isBackfilled;
    backfillDepth = rhs.backfillDepth;
    backfillDensity = rhs.backfillDensity;

    return *this;

}

void Parameters::conditionToTemperature()
{
	dynamicModulus = eDyn0degC + tempDegC * dEdyndT;
} 

