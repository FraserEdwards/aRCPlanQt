#include "Simulation.h"
#include "guimain.h"
#include "ui_guimain.h"
#include <iostream>
using namespace std;

Simulation::Simulation()
{

	controlCode=0;	
	i=0;
	aDotc0=0.0;

}

Solution Simulation::precalc(Parameters parameters)
{

    Solution solution;

    Interface interface(1, config);

    //  Initialise crack and compute Irwin-Corten crack driving force at initial pressure:
    FracMech fracmech(parameters);
//		interface.line("Irwin-Corten crack driving force = ", fracmech.g0, " kJ/m^2");

    //	Calculate natural diameter of pipe due to residual strain contraction in time scale of fracture
    Creep creep(parameters);

    //  Compute the effective multiplier on pipe wall density where the wall has 'attached' backfill or contains water
    Backfill backfill(parameters);
//		interface.line("Effective ratio of backfilled to free pipe density = ", backfill.densityratio);

    //	Preliminary calculations
    BeamModel beamModel(parameters, backfill, creep);

    if (parameters.mode == 0)
    {

     // Enter speed of interest
//      parameters.aDotc0=interface.input("Enter the single crack-speed/sonic-velocity ratio of interest: ");
        run(parameters, fracmech, creep, backfill);

    }
    else
    {

        //  Proceed to vary crack speed
        for (i = 0; i < parameters.rangenumber; i++)
        {
            parameters.aDotc0 = (i + 1) / double(parameters.rangenumber);
            run(parameters, fracmech, creep, backfill);
        }

    }

    return solution;

}

Solution Simulation::run(Parameters parameters, FracMech fracmech, Creep creep, Backfill backfill)
{
        Solution temp;

        // Speed dependent properties
        beamModel.speedandreset(parameters, backfill, creep);
        // Iteration function
        beamModel.iteration(parameters, interface, backfill, creep);

        if(!beamModel.noCrackOpening)
        {
            beamModel.opening(parameters, interface, solution, creep);

            fracmech.extensionForce(beamModel, parameters, creep);

            temp.sprofile(beamModel.zeta, beamModel.crackdisplacement, beamModel.l);
            temp.Tvalues(parameters.aDotc0, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
            fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);

        }
        else
        {

            temp.Tvalues(parameters.aDotc0, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
            fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);
				
        }
					
    return temp;

}
