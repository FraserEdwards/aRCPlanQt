#include "Simulation.h"
#include <iostream>
using namespace std;

Simulation::Simulation()
{

	controlCode=0;	
	i=0;
	aDotc0=0.0;

}

Solution Simulation::run(Parameters parameters)
{
    Results results;
    Plot plot;
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

    //  Proceed to vary crack speed
    for (i = 0; i < parameters.rangenumber; i++)
    {

        parameters.aDotc0 = (i + 1) / double(parameters.rangenumber);

        // Single shot mode
        if (parameters.rangenumber == 1)
            {

				// Enter speed of interest
				parameters.aDotc0=interface.input("Enter the single crack-speed/sonic-velocity ratio of interest: ");		
				
			}  



        // Speed dependent properties
        beamModel.speedandreset(parameters, backfill, creep);
        // Iteration function
        beamModel.iteration(parameters, interface, backfill, creep);

        if(!beamModel.noCrackOpening)
        {
            beamModel.opening(parameters, interface, solution, creep, plot, results);
            fracmech.extensionForce(beamModel, parameters, creep);
//			interface.line("Solution profile: ");
//			interface.line("with v0 = ", beamModel.v0);

            solution.sprofile(beamModel.zeta, beamModel.crackdisplacement, beamModel.l);
            solution.Tvalues(parameters.aDotc0, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
            fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);

//          plot.profile(beamModel.zeta, beamModel.crackdisplacement, "aDotc0 = ", "/Profile/", parameters.aDotc0, "Distance behind crack tip, z (mm)", "Crack Opening Displacement (mm)");
				
//			interface.iprofile(solution.zeta, solution.vptra, solution.l);
//			interface.returnsol(solution);
            results.line(solution);

        }
        else
        {

            solution.Tvalues(parameters.aDotc0, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
            fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);

            // solution.Tvalues(parameters.aDotc0, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[1]);
//			interface.returnnsol(solution);
            results.line(solution);
				
        }
					
    }
    return solution;

//        plot.handler(solution);

}
