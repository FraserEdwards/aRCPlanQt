#include "ConfigFile.h"
#include "Parameters.h"
#include "File.h"
#include "Creep.h"
#include "Backfill.h"
#include "BeamModel.h"
#include "FracMech.h"
#include "qcustomplot.h"
#include "guimain.h"
#include "ui_guimain.h"
#include <QObject>


#ifndef _SIMULATION_H
#define _SIMULATION_H

class Simulation
{

signals:


private:
	
	int i;
	short controlCode;
	double aDotc0;
	
	Parameters parameters;	
    File file;
	Creep creep;
	Backfill backfill;
	BeamModel beamModel;
	Solution solution;


public:	
	
	ConfigFile config;
	Simulation();
    Solution run(Parameters parameters);

};

#endif
