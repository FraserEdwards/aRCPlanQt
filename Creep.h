#include "Parameters.h"

#ifndef _CREEP_H
#define _CREEP_H

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
