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

    creepmodulusratio=0.0;
    diameterres0=0.0;
    residualcrackclosure=0.0;

}

//Constructor
//Takes parameters as arguments
//Does not explicitly return values
Creep::Creep(const Parameters parameters)
{
	//	Calculate natural diameter of pipe dues to residual strain contraction in time scale of fracture
    creepmodulusratio = parameters.creepmodulus / parameters.dynamicmodulus;

    diameterres0 = parameters.diameter / ((1.0 - creepmodulusratio) + creepmodulusratio / parameters.diametercreepratio);

    residualcrackclosure = (parameters.diameter - diameterres0) * Constants::pi;

}
