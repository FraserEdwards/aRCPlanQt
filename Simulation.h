#include "ConfigFile.h"
#include "Parameters.h"
#include "Filepath.h"
#include "Interface.h"
#include "Creep.h"
#include "Backfill.h"
#include "BeamModel.h"
#include "FracMech.h"
#include "Results.h"
#include "Plot.h"


#ifndef _SIMULATION_H
#define _SIMULATION_H

class Simulation
{

private:
	
	int i;
	short controlCode;
	double aDotc0;
	
	Parameters parameters;	
	Filepath filePath;
	Creep creep;
	Backfill backfill;
	BeamModel beamModel;
	Results results;
	Plot plot;
	Interface interface;
	Solution solution;


public:	
	
	ConfigFile config;
	Simulation();
    Results run(Parameters parameters, Solution solution);

};

#endif
