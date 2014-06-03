//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef _SIMULATION_H
#define _SIMULATION_H

#include <QObject>

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

class Simulation
{

signals:


private:
	
	int i;
	short controlCode;
	double aDotc0;
	
public:	
	
    //Null constructor
	Simulation();

    //Iteration function, parameters as arguments, returns solution
    Solution run(Parameters parameters);

};

#endif
