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

    creep_modulus_ratio=0.0;
    diameter_res0=0.0;
    residual_crack_closure=0.0;

}

//Constructor
//Takes parameters as arguments
//Does not explicitly return values
Creep::Creep(const Parameters parameters)
{
	//	Calculate natural diameter of pipe dues to residual strain contraction in time scale of fracture
    creep_modulus_ratio = parameters.creepmodulus / parameters.dynamicmodulus;

    diameter_res0 = parameters.diameter / ((1.0 - creep_modulus_ratio) + creep_modulus_ratio / parameters.diametercreepratio);

    residual_crack_closure = (parameters.diameter - diameter_res0) * Constants::pi;

}
