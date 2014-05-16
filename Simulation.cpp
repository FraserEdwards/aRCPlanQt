
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

    cout << "Parameters: " << endl;

    cout << "matID: " << parameters.matID << endl;
    cout << "density: " << parameters.density << endl;
    cout << "eDyn0degC: " << parameters.eDyn0degC << endl;
    cout << "dEdyndt: " << parameters.dEdyndT << endl;
    cout << "creepModulus: " << parameters.creepModulus << endl;
    cout << "poisson: " << parameters.poisson << endl;

    cout << "pipeID: " << parameters.pipeID << endl;
    cout << "diameter: " << parameters.diameter << endl;
    cout << "sdr: " << parameters.sdr << endl;
    cout << "notchDepth: " << parameters.notchDepth << endl;
    cout << "diameterCreepRatio: " << parameters.diameterCreepRatio << endl;

    cout << "fullScale: " << parameters.fullScale << endl;
    cout << "tempDegC: " << parameters.tempDegC << endl;
    cout << "p0bar: " << parameters.p0bar << endl;
    cout << "isBackfilled: " << parameters.isBackfilled << endl;
    cout << "backfillDepth: " << parameters.backfillDepth << endl;
    cout << "solidInsidePipe: " << parameters.solidInsidePipe << endl;
    cout << "waterInsidePipe: " << parameters.waterInsidePipe << endl;

    cout << "outflowModelOn: " << parameters.outflowModelOn << endl;
    cout << "lambda: " << parameters.lambda << endl;
    cout << "solutionmethod: " << parameters.solutionmethod << endl;
    cout << "aDotc0: " << parameters.aDotc0 << endl;
    cout << "elementsinl: " << parameters.elementsinl << endl;



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
    cout << "Internalvolume: " << beamModel.availableInternalVolume << endl;
    cout << "baffleLeakageArea: " << beamModel.baffleLeakageArea << endl;
    cout << "dynamicShearModulus: " << beamModel.dynamicShearModulus << endl;
    cout << "sdrMinus1: " << beamModel.sdrMinus1 << endl;
    cout << "sdrMinus2: " << beamModel.sdrMinus2 << endl;
    cout << "zetaClosure: " << beamModel.zetaClosure << endl;
    cout << "nodeResolution: " << beamModel.nodeResolution << endl;
    cout << "nodeAtClosure: " << beamModel.nodeAtClosure << endl;
    cout << "zetaBackfilled: " << beamModel.zetaBackfilled << endl;


    if(parameters.singlemode)
    {
        solution.clear();
        solution.displacement(parameters);

        // Speed dependent properties
        beamModel.speedandreset(parameters, backfill, creep);

        cout << "outflowLength: " << beamModel.outflowLength << endl;
        cout << "LambdaPow4: " << beamModel.lambdaPow4 << endl;

        // Iteration function
        beamModel.iteration(parameters, backfill, creep);

            beamModel.opening(parameters, creep);
            fracmech.extensionForce(beamModel, parameters, creep);

            solution.Tvalues(parameters.aDotc0, parameters.p0bar, parameters.tempDegC, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
            fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);
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

                beamModel.opening(parameters, creep);
                fracmech.extensionForce(beamModel, parameters, creep);

                solution.Tvalues(parameters.aDotc0, parameters.p0bar, parameters.tempDegC, beamModel.p1p0r, beamModel.alpha[1], beamModel.m[0], beamModel.outflowLength, beamModel.deltaDStar,
                fracmech.gS1, fracmech.gUE, fracmech.gSb, fracmech.gKb, fracmech.g0, fracmech.gG0, fracmech.gTotal);
        }

    }

    return solution;

}
