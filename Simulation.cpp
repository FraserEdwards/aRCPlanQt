
#include <iostream>
#include <QObject>
using namespace std;

#include "Simulation.h"
#include "guimain.h"
#include "ui_guimain.h"

Simulation::Simulation()
{

	controlCode=0;	
	i=0;
	aDotc0=0.0;

}

Solution Simulation::run(Parameters parameters)
{

    extern Solution solution;
    extern File file;
    file.logprepare(parameters);

    //  Initialise crack and compute Irwin-Corten crack driving force at initial pressure:
    FracMech fracmech(parameters);
    file.collect(fracmech);

    //	Calculate natural diameter of pipe due to residual strain contraction in time scale of fracture
    Creep creep(parameters);
    file.collect(creep);

    //  Compute the effective multiplier on pipe wall density where the wall has 'attached' backfill or contains water
    Backfill backfill(parameters);
    file.collect(backfill);

    //	Preliminary calculations
    BeamModel beamModel(parameters);

    if(parameters.singlemode)
    {
        solution.clear();
        solution.displacement(parameters);

        // Speed dependent properties
        beamModel.speedandreset(parameters, backfill, creep);
        // Iteration function
        beamModel.iteration(parameters, backfill, creep);

        if(!beamModel.noCrackOpening)
        {

            beamModel.opening(parameters, creep);
            fracmech.extensionForce(beamModel, parameters, creep);

            solution.Tvalues(parameters.aDotc0, parameters.p0bar, parameters.tempDegC, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
            fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);

        }
        else
        {
            beamModel.opening(parameters, creep);
            fracmech.extensionForce(beamModel, parameters, creep);

            solution.Tvalues(parameters.aDotc0, parameters.p0bar, parameters.tempDegC, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
            fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);

            // solution.Tvalues(parameters.aDotc0, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[1]);

        }

    }
    else
    {
        solution.clear();
        solution.displacement(parameters);

        //  Proceed to vary crack speed
        for (i =0; i < parameters.rangenumber; i++)
        {
            switch(parameters.varname)
            {
                case 0:
                    parameters.aDotc0 = parameters.from + ((i+1) * ((parameters.to - parameters.from)/parameters.rangenumber));
                    break;
                case 1:
                    parameters.p0bar = parameters.from + ((i+1) * ((parameters.to - parameters.from)/parameters.rangenumber));
                    break;
                case 2:
                    parameters.tempDegC = parameters.from + ((i+1) * ((parameters.to - parameters.from)/parameters.rangenumber));
                    break;
                default:
                    break;
            }

            // Speed dependent properties
            beamModel.speedandreset(parameters, backfill, creep);
            // Iteration function
            beamModel.iteration(parameters, backfill, creep);

            if(!beamModel.noCrackOpening)
            {

                beamModel.opening(parameters, creep);
                fracmech.extensionForce(beamModel, parameters, creep);

                solution.Tvalues(parameters.aDotc0, parameters.p0bar, parameters.tempDegC, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
                fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);

            }
            else
            {   beamModel.opening(parameters, creep);
                fracmech.extensionForce(beamModel, parameters, creep);

                solution.Tvalues(parameters.aDotc0, parameters.p0bar, parameters.tempDegC, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
                fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);
				
            }
					
        }

    }

    return solution;

}
