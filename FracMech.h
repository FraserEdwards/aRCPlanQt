#ifndef _FRACHMECH_H
#define _FRACHMECH_H

#include "Creep.h"
#include "Backfill.h"
#include "BeamModel.h"

class FracMech
{
public:

	double g0;
	double gS1;
	double gUE;
	double gSb;
	double gKb;
	double gTotal;
	double gG0;
	double aDotc0;

	FracMech();	
	FracMech(const Parameters parameters);
	void extensionForce(const BeamModel beamModel, const Parameters parameters, const Creep creep);
};

#endif
