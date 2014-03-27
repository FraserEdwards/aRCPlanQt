#include "Interface.h"
#include "TestSetup.h"
#include "Material.h"
#include "BeamModel.h"
#include "Parameters.h"

#ifndef _FRACHMECH_H
#define _FRACHMECH_H

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