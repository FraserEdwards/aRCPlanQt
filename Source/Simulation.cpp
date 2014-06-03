//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Class providing function to iterate through independent variable
//     Calls various modules such as Backfill, Creep and FracMech prior to BeamModel iteration

#include <iostream>
#include <QObject>
using namespace std;

#include "Constants.h"
#include "Simulation.h"
#include "guimain.h"
#include "ui_guimain.h"

//Null constructor
Simulation::Simulation()
{

	controlCode=0;	
	i=0;
	aDotc0=0.0;

}

//Taking parameters as arguments, peforms the calculation for a given range of
//the independent variable eventually produced a solution
Solution Simulation::run(Parameters parameters)
{

    parameters.h = parameters.diameter/parameters.sdr/Constants::kilo; // (m)
    parameters.hoverr = 2.0/ (parameters.sdr-1);
    parameters.radius = parameters.h / parameters.hoverr;

    parameters.crackwidth = parameters.diameter / parameters.sdr - parameters.notchdepth; //(mm, giving kJ/m2 for G; not necessarily equal to h)

    extern Solution solution;
    extern File file;
    file.logprepare(parameters);

    //  Compute the effective multiplier on pipe wall density where the wall has 'attached' backfill or contains water
    Backfill backfill(parameters);
    file.collect(backfill);

    //	Preliminary calculations
    BeamModel beamModel(parameters);

    if(parameters.singlemode)
    {
        solution.clear();
        solution.displacement(parameters);

        parameters.dynamicmodulus = parameters.edyn0degc + parameters.tempdegc * parameters.dedyndt;

        //  Initialise crack and compute Irwin-Corten crack driving force at initial pressure:
        FracMech fracmech(parameters);
        file.collect(fracmech);

        //	Calculate natural diameter of pipe due to residual strain contraction in time scale of fracture
        Creep creep(parameters);
        file.collect(creep);

        // Speed dependent properties
        beamModel.speedandreset(parameters, backfill, creep);

        // Iteration function
        beamModel.iteration(parameters, backfill, creep);

        beamModel.opening(parameters, creep);
        fracmech.extensionForce(beamModel, parameters, creep);

        solution.Tvalues(parameters.adotc0, parameters.p0bar, parameters.tempdegc, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
        fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal, beamModel.noCrackOpening, beamModel.notConverged, beamModel.iterations);

        file.initialise();

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
                    parameters.adotc0 = parameters.from + ((i+1) * ((parameters.to - parameters.from)/parameters.rangenumber));
                    break;
                case 1:
                    parameters.p0bar = parameters.from + ((i+1) * ((parameters.to - parameters.from)/parameters.rangenumber));
                    break;
                case 2:
                    parameters.tempdegc = parameters.from + ((i+1) * ((parameters.to - parameters.from)/parameters.rangenumber));
                    break;
                default:
                    break;
            }

            parameters.dynamicmodulus = parameters.edyn0degc + parameters.tempdegc * parameters.dedyndt;

            //  Initialise crack and compute Irwin-Corten crack driving force at initial pressure:
            FracMech fracmech(parameters);
            file.collect(fracmech);

            //	Calculate natural diameter of pipe due to residual strain contraction in time scale of fracture
            Creep creep(parameters);
            file.collect(creep);

            // Speed dependent properties
            beamModel.speedandreset(parameters, backfill, creep);

            // Iteration function
            beamModel.iteration(parameters, backfill, creep);

            beamModel.opening(parameters, creep);
            fracmech.extensionForce(beamModel, parameters, creep);

            solution.Tvalues(parameters.adotc0, parameters.p0bar, parameters.tempdegc, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
            fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal, beamModel.noCrackOpening, beamModel.notConverged, beamModel.iterations);

            file.initialise();

        }

    }

    return solution;

}
