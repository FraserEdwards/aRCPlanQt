//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Class providing a creep model

#include "Constants.h"
#include "Creep.h"

//Null constructor
Creep::Creep()
{

	creepModulusRatio=0.0;
	diameterRes0=0.0;
	residualCrackClosure=0.0;

}

//Constructor
//Takes parameters as arguments
//Does not explicitly return values
Creep::Creep(const Parameters parameters)
{
	//	Calculate natural diameter of pipe dues to residual strain contraction in time scale of fracture
    creepModulusRatio = parameters.creepmodulus / parameters.dynamicmodulus;

    diameterRes0 = parameters.diameter / ((1.0 - creepModulusRatio) + creepModulusRatio / parameters.diametercreepratio);

	residualCrackClosure = (parameters.diameter - diameterRes0) * Constants::pi;

}
