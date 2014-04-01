#include "ConfigFile.h"
#include "Parameters.h"
#include "Filepath.h"
#include "Interface.h"
#include "Creep.h"
#include "Backfill.h"
#include "BeamModel.h"
#include "FracMech.h"
#include "qcustomplot.h"
#include "guimain.h"
#include "ui_guimain.h"


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
	Interface interface;
	Solution solution;


public:	
	
	ConfigFile config;
	Simulation();
    Solution run(Parameters parameters);

};

#endif
