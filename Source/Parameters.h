//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include <iostream>
#include <fstream>
using namespace std;

#include "ConfigFile.h"

class Parameters
{

private:

    string filename;



    ConfigFile config;
	
public:

    static string matid_lib[5];
    static double density_lib[5];
    static double edyn0degc_lib[5];
    static double dedyndt_lib[5];
    static double creepmodulus_lib[5];
    static double poisson_lib[5];

    static string pipeid_lib[5];
    static double diameter_lib[5];
    static double sdr_lib[5];
    static double notchdepth_lib[5];
    static double diametercreepratio_lib[5];

    static double from_lib[3];
    static double to_lib[3];

    string methodid;
    short fullscale;
    double tempdegc;
    double p0bar;
    int isbackfilled;
    double backfilldepth;
    double backfilldensity;
    double solidinsidepipe;
    double waterinsidepipe;

    string matid;
    double density;
    double edyn0degc;
    double dedyndt;
    double dynamicmodulus;
    double creepmodulus;
    double poisson;
    double creepmodulusratio;

    string pipeid;
    double diameter;
    double sdr;
    double notchdepth;
    double diametercreepratio;
    double h;
    double crackwidth;
    double hoverr;
    double radius;

    short verbose;
    int outflowmodelon;
    double lambda;
    int solutionmethod;
    int singlemode;
    int rangenumber;
    int elementsinl;
    double adotc0;
    double from;
    double to;
    double indvar;
    int varname;

    //Null constructor
    Parameters();

    //Constructor
    Parameters(ConfigFile config);

    //'=' operator
    Parameters& operator=(const Parameters& rhs);

    //Updates the geometry and material values respectively
    void geometryupdate(int n);
    void materialupdate(int n);

    //Reads in the parameter values from the config file provided
    void collect(ConfigFile config);

    //Modifies parameters for temperature changes
    void conditionToTemperature();

} ;

#endif
