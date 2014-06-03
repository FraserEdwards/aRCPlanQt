//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef _BACKFILL_H
#define _BACKFILL_H

#include "Parameters.h"

class Backfill
{
	
public:	

	double densityratio;

    //Null Constructor
	Backfill();

    //Constructor
    //Calculates the density ratio
	Backfill(const Parameters parameters);

};
#endif
