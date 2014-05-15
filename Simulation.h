#ifndef _SIMULATION_H
#define _SIMULATION_H

#include <QObject>

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
	
	ConfigFile config;
	Simulation();
    Solution run(Parameters parameters);

};

#endif
