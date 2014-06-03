//     aRCPLan

//     Authors: Dr Patric Leevers, Fraser //
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef _CREEP_H
#define _CREEP_H

#include "Parameters.h"
class Creep
{
	
private:

	double creepModulusRatio;

public:

	double diameterRes0;
	double residualCrackClosure;

	//Null constructor
	Creep();

	//Constructor
	Creep(const Parameters parameters);

};

#endif
