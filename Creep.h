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
