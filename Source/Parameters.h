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

    static string matID_lib[5];
    static double density_lib[5];
    static double eDyn0degC_lib[5];
    static double dEdyndT_lib[5];
    static double creepModulus_lib[5];
    static double poisson_lib[5];

    static string pipeID_lib[5];
    static double diameter_lib[5];
    static double sdr_lib[5];
    static double notchDepth_lib[5];
    static double diameterCreepRatio_lib[5];

    static double from_lib[3];
    static double to_lib[3];

    string methodID;
    short fullScale;
    double tempDegC;
    double p0bar;
    int isBackfilled;
    double backfillDepth;
    double backfillDensity;
    double solidInsidePipe;
    double waterInsidePipe;

    string matID;
    double density;
    double eDyn0degC;
    double dEdyndT;
    double dynamicModulus;
    double creepModulus;
    double poisson;
    double creepModulusRatio;

    string pipeID;
    double diameter;
    double sdr;
    double notchDepth;
    double diameterCreepRatio;
    double h;
    double crackWidth;
    double hOverR;
    double radius;

    short verbose;
    int outflowModelOn;
    double lambda;
    int solutionmethod;
    int singlemode;
    int rangenumber;
    int elementsinl;
    double aDotc0;
    double from;
    double to;
    double indvar;
    int varname;

    Parameters();
    Parameters(ConfigFile config);
    Parameters& operator=(const Parameters& rhs);
    void geometryupdate(int n);
    void materialupdate(int n);
    void controlupdate(int n);
    void testupdate(int n);
	void collect(ConfigFile config);
    void conditionToTemperature();

} ;

#endif
