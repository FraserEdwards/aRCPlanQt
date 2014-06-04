//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Class concerned with calculating the Irwin Corten driving force
//     Once solution has been reached calculates driving force using strain considerations

#include <cmath>
#include <iostream>

#include "FracMech.h"
#include "Constants.h"

//Null constructor
FracMech::FracMech()
{
	g0=0;

}

//Constructor
//Calculates the Irwin-Corten driving force
FracMech::FracMech(const Parameters parameters)
{

	g0 = parameters.p0bar * (parameters.sdr - 2.0);
    g0 = Constants::pi / 800.0/ Constants::kilo * g0 * g0 / parameters.dynamic_modulus * parameters.diameter * (1.0 - 1.0 / parameters.sdr);		// kJ/m2
	
}

//Calculates the final crack driving force using energy consideration
void FracMech::extensionForce(BeamModel beamModel, const Parameters parameters, const Creep creep)
{

	//	GS1 due to residual strain bending energy in pipe wall ahead of crack:
    gs1 = (parameters.diameter - creep.diameter_res0);			// (mm)
    gs1 = Constants::pi / 6.0 * parameters.dynamic_modulus * Constants::kilo / pow(beamModel.sdrminus1, 3) * gs1 * gs1 / parameters.crack_width;

	//  GUE due to work done on flaps (= dUE/da / crack width):
    gue = (parameters.radius - 0.5 * parameters.h) * beamModel.p1bar * Constants::bar * beamModel.v0 * beamModel.integral_wstar2  / parameters.crack_width;

	//  GSb due to strain energy at decompression point behind crack: (Pipe Model Manual. pg36)
    gsb = 0.5 * parameters.dynamic_modulus * Constants::giga *  (pow(parameters.hoverr, 3) / 24.0 / Constants::pi * beamModel.wstar2 * beamModel.wstar2 + Constants::c1 * pow(parameters.radius, 3) * parameters.h * beamModel.wstar2dash2 * beamModel.wstar2dash2);
    gsb = (gsb + Constants::pi / 48.0 * beamModel.dynamic_shear_modulus * Constants::giga * parameters.radius * parameters.h * pow(parameters.hoverr * beamModel.wstar2dash, 2)) / parameters.crack_width;

	//  GKb due to kinetic energy at decompression point behind crack: (Pipe Model Manual. pg36)
    gkb = 0.5 * parameters.dynamic_modulus * Constants::giga * parameters.radius * parameters.h * beamModel.adotovercl * beamModel.adotovercl *
    (Constants::c2 * beamModel.wstar2dash * beamModel.wstar2dash + Constants::c1 * pow(beamModel.wstar2dash2 * parameters.radius, 2)) / parameters.crack_width;

    //Check against 2 as checkboxes are assigned this in GUI rather than 1
    if (parameters.solution_method==2)
    {
        //  ... account for kinetic energy of detached backfill mass:
        beamModel.factor = beamModel.vstardashbackfilleject * beamModel.v0 * parameters.adotc0 * Constants::vSonic * parameters.sdr / 2.0 / beamModel.sdrminus1 / beamModel.outflow_length;
        gkb -= Constants::pi * parameters.backfill_density  * pow(beamModel.factor, 2) * log(1.0 + 2.0 * parameters.backfill_depth * double(parameters.is_backfilled/2)/ parameters.diameter) / Constants::kilo;
    }

	//  Total G:
    gtotal = gue + g0 + gs1 - gsb - gkb;

    if (gtotal < 0.0)
        gtotal = 0.0;

    gg0 = gtotal / g0;

}

