//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Class which reads values in from configFile and stores to pass val

#include <iostream>
using namespace std;

#include "Parameters.h"
#include "ConfigFile.h"

    string Parameters::pipeid_lib[5] = {"250mm_SDR11", "250mm_SDR17", "110mm_SDR11", "110mm_SDR17", "63mm_SDR11"};
    double Parameters::diameter_lib[5] = {250.0, 250.0, 110.0, 110.0, 63.0};
    double Parameters::sdr_lib[5] = {11.0, 17.6, 11.0, 17.6, 11.0};

    double Parameters::density_lib[5] = {938.0, 960.0, 938.0, 960.0, 950.0};
    double Parameters::edyn0degc_lib[5] = {2.62, 3.17, 1.31, 1.585, 1.5};
    double Parameters::dedyndt_lib[5] = {-0.037, -0.0427, -0.0185, -0.02135, -0.02};
    double Parameters::creepmodulus_lib[5] = {0.3, 0.3, 0.3, 0.3, 0.3};
    double Parameters::poisson_lib[5] = {0.38, 0.38, 0.38, 0.38, 0.38};
    double Parameters::from_lib[3] = {0.0, 1.0, 1.0};
    double Parameters::to_lib[3] = {1.0, 20.0, 50.0};

//Null constructor
Parameters::Parameters()
{

    outflowmodelon = 0;
    lambda = 3.0;
    solutionmethod = 2;
    singlemode = 2;
    rangenumber = 0;
    elementsinl = 10;
    adotc0 = 0.5;
    varname = 0;

    fullscale = 2;
    tempdegc = 0.0;
    p0bar = 5.0;
    isbackfilled = 2;
    backfilldepth = 100;
    backfilldensity = 2200;
    solidinsidepipe = 0.25;
    waterinsidepipe = 0.25;

    h=0.0;
    hoverr=0.0;
    radius=0.0;
    crackwidth=0.0;

    geometryupdate(0);
    materialupdate(0);

    conditionToTemperature();

}
//Updates the geometry for the pipe
void Parameters::geometryupdate(int n)
{
    pipeid = Parameters::pipeid_lib[n];
    diameter = diameter_lib[n];
    sdr = sdr_lib[n];
    notchdepth = 0.0;
    diametercreepratio = 1.0;

}

//Update the material for the pipe
void Parameters::materialupdate(int n)
{
    matid = matid[n];
    density = density_lib[n];
    edyn0degc = edyn0degc_lib[n];
    dedyndt = dedyndt_lib[n];
    creepmodulus = creepmodulus_lib[n];
    poisson = poisson_lib[n];
}

//Constructor
Parameters::Parameters(ConfigFile config)
{
    config.readInto(outflowmodelon, "outflowModelOn");
    config.readInto(lambda, "lambda");
    config.readInto(solutionmethod, "solutionmethod");
    config.readInto(singlemode, "Mode");
    config.readInto(rangenumber, "numberOfSpeedValues");
    config.readInto(elementsinl, "elementsInL");
    config.readInto(adotc0, "aDotc0");

    config.readInto(pipeid, "pipeID");
    config.readInto(diameter, "diameter");
    config.readInto(sdr, "sdr");
    config.readInto(notchdepth, "notchDepth");
    config.readInto(diametercreepratio, "diameterCreepRatio");

    config.readInto(matid, "matID" );
    config.readInto(density, "density" );
    config.readInto(edyn0degc, "eDyn0degC" );
    config.readInto(dedyndt, "dEdyndT" );
    config.readInto(creepmodulus, "creepModulus" );
    config.readInto(poisson, "poisson" );

    config.readInto(fullscale, "fullScale");
    config.readInto(tempdegc, "tempDegC");
    config.readInto(p0bar, "p0bar");
    config.readInto(isbackfilled, "isBackfilled");
    config.readInto(backfilldepth, "backfillDepth");
    config.readInto(backfilldensity, "backfillDensity");
    config.readInto(solidinsidepipe, "solidInsidePipe");
    config.readInto(waterinsidepipe, "waterInsidePipe");
}

//Creates the "=" operator for this class
Parameters& Parameters::operator=(const Parameters& rhs)
{
    outflowmodelon = rhs.outflowmodelon;
    lambda = rhs.lambda;
    solutionmethod = rhs.solutionmethod;
    singlemode = rhs.singlemode;
    rangenumber = rhs.rangenumber;
    elementsinl = rhs.elementsinl;
    adotc0 =  rhs.adotc0;
    from = rhs.from;
    to = rhs.to;
    varname = rhs.varname;
    verbose = rhs.verbose;

    pipeid = rhs.pipeid;
    diameter = rhs.diameter;
    sdr = rhs.sdr;
    notchdepth = rhs.notchdepth;
    diametercreepratio = rhs.diametercreepratio;
    radius = rhs.radius;
    h = rhs.h;
    hoverr = rhs.hoverr;
    crackwidth = rhs.crackwidth;

    matid = rhs.matid;
    density = rhs.density;
    edyn0degc = rhs.edyn0degc;
    dedyndt = rhs.dedyndt;
    dynamicmodulus = rhs.dynamicmodulus;
    creepmodulus = rhs.creepmodulus;
    poisson = rhs.poisson;

    methodid = rhs.methodid;
    fullscale = rhs.fullscale;
    tempdegc = rhs.tempdegc;
    p0bar = rhs.p0bar;
    isbackfilled = rhs.isbackfilled;
    backfilldepth = rhs.backfilldepth;
    backfilldensity = rhs.backfilldensity;

    return *this;

}

//Modifies parameters to account for temperature
void Parameters::conditionToTemperature()
{
    dynamicmodulus = edyn0degc + tempdegc * dedyndt;
} 

