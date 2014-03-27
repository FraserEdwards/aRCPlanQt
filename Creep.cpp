#include "Constants.h"
#include "Creep.h"

Creep::Creep()
{

	creepModulusRatio=0.0;
	diameterRes0=0.0;
	residualCrackClosure=0.0;

}

Creep::Creep(const Parameters parameters)
{
	//	Calculate natural diameter of pipe dues to residual strain contraction in time scale of fracture
	creepModulusRatio = parameters.creepModulus / parameters.dynamicModulus;

	diameterRes0 = parameters.diameter / ((1.0 - creepModulusRatio) + creepModulusRatio / parameters.diameterCreepRatio);

	residualCrackClosure = (parameters.diameter - diameterRes0) * Constants::pi;

}