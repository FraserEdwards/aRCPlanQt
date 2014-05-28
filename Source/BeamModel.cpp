#include <cmath>
#include <iostream>
#include <QDesktopWidget>

#include "dialog.h"

#include "Constants.h"
#include "BeamModel.h"
#include "OutflowProcess.h"
#include "Decompression.h"
#include "FDprofile.h"
#include "Solution.h"
#include "File.h"


//Null constructor
BeamModel::BeamModel()
{
    initialise();
}

//Constructor
BeamModel::BeamModel(const Parameters parameters)
{
    initialise();
    extern File file;

	//Proportion of internal volume available for expansion
	availableInternalVolume = 1.0 - parameters.waterInsidePipe - parameters.solidInsidePipe;

	//Factors for modelling of S4 baffle leak
	baffleLeakageArea=parameters.diameter / Constants::kilo;  //m
	baffleLeakageArea = baffleLeakageArea * baffleLeakageArea * 0.01 * Constants::pi * (parameters.sdr - 2.0) / parameters.sdr;

	//Parameters for equivalent beam model
    dynamicShearModulus = parameters.dynamicModulus / 2.0 / (1.0 + parameters.poisson);
	sdrMinus1 = parameters.sdr - 1.0;
	sdrMinus2 = sdrMinus1 - 1.0;

    file.collect(this,0);

}
void BeamModel::initialise()
{

    dStarMinus1 = 0.0;
    dStarMinus2 = 0.0;
    baffleLeakageArea = 0.0;
    fdArraySize = 0;
    decompression = 0.0;

    zetaClosure = 0.0;
    printOpeningProfile = 0;

    l = 0;
    maxIterations = 0;
    hOverR = 0.0;
    lambdaLast = 0.0;
    zetaBackfilledLast = 0.0;
    notConverged = 1;
    iterations = 0;
    noCrackOpening = 0;
    wStar2 = 0.0;
    wStarMax = 0.0;
    wStar2dash = 0.0;
    wStar2dash2 = 0.0;
    integral_wStar2 = 0.0;
    zetaBackfillEject = 0.0;
    p1p0r = 0.0;
    dynamicShearModulus = 0.0;
    nodeResolution = 0.0;
    v0 = 0.0;
    factor = 0.0;
    p1bar = 0.0;
    vStarRes = 0.0;
    nodeAtClosure = 0;
    aDotOverCL = 0.0;
    aDotCLfactor = 0.0;
    aDotCLfactor_backfilled = 0.0;
    lambdaPow4 = 0;
    sdrMinus1 = 0.0;
    sdrMinus2 = 0.0;
    zetaBackfilled = 0.0;
    outflowLength = 0.0;
    v00 = 0.0;
    error = 0.0;
    availableInternalVolume = 0.0;
    vStarDashBackfillEject = 0.0;

    m[0] = 0.0;
    m[1] = 0.0;
    alpha[0] = 0.0;
    alpha[1] = 0.0;
    n = 0;

}

void BeamModel::speedandreset(const Parameters parameters, const Backfill backfill, Creep creep)
{
    extern File file;
	//  Set initial outflow length

    zetaClosure = 2.0;				//	Point (in outflow lengths) at which crack re-closes, with first guess.
    nodeResolution = 0.5 / parameters.elementsinl;	// used as a reference tolerance
    nodeAtClosure = short(zetaClosure * parameters.elementsinl);
    zetaBackfilled = 0.2;		// first guess

	outflowLength = parameters.lambda;
	lambdaPow4 =  pow(outflowLength, 4);
		
	//For FS configuration, prior decompression
	p1bar=parameters.p0bar;
	Decomp decomp;
	// Proportion of initial pressure which remains at crack tip	
	decomp.p1p0r=1.0;		

    if(parameters.fullScale==2)
						{

						availableInternalVolume=1.0;

						decomp.p1p0(parameters.p0bar, Constants::gamma, parameters.aDotc0);

						p1bar=parameters.p0bar * decomp.p1p0r; //New p1, could replace with p1 from decomp object, need to trace

						}

	p1p0r=decomp.p1p0r; //Stopgap measure

	//	v00 becomes reference length v0 on multiplying by lambda^4
	v00 = 0.4 / Constants::c1 * sdrMinus1 * sdrMinus2 / parameters.sdr * p1bar / parameters.dynamicModulus * parameters.diameter / Constants::mega;	//	(m)

	//	Dimensionless virtual crack opening at crack tip (representing residual strain)
	v0 = v00 * lambdaPow4;			//	(m)
    vStarRes = creep.residualCrackClosure / v0 / Constants::kilo;

	// Parameters for equivalent beam model (speed dependent)
	aDotOverCL = parameters.aDotc0 * Constants::vSonic / sqrt(parameters.dynamicModulus * Constants::giga / parameters.density);
	aDotCLfactor = 1.0 + aDotOverCL * aDotOverCL;

	aDotCLfactor_backfilled = 1.0 + aDotOverCL * aDotOverCL * backfill.densityratio;

	factor = Constants::pi * Constants::c1 * 625.0 * parameters.dynamicModulus / p1bar * availableInternalVolume * sdrMinus2 / sdrMinus1 / sdrMinus1 * parameters.aDotc0;	// Note GPa / bar / 16 = 625

    file.aDotc0 = parameters.aDotc0;
    file.collect(this, 1);

}

void BeamModel::stiffness()
{
	//	Dimensionless foundation stiffness [0] with backfill and [1] without
	m[1] = 8.0 / 3.0 / Constants::pi / Constants::c1 / sdrMinus1 / sdrMinus1 * lambdaPow4;
	m[0] = m[1] / aDotCLfactor_backfilled;
	m[1] /= aDotCLfactor;
}

void BeamModel::cspeed(const Parameters parameters, const Backfill backfill)
{
	//	Dimensionless crack speed [0] with backfill and [1] without
	alpha[1] = outflowLength * sqrt(Constants::c3 * aDotOverCL * aDotOverCL + Constants::c4 / 2.0 / (1.0 + parameters.poisson) / sdrMinus1 / sdrMinus1 / aDotCLfactor);
	alpha[0] = outflowLength * sqrt(Constants::c3 * aDotOverCL * aDotOverCL * backfill.densityratio + Constants::c4 * 0.5 / (1.0 + parameters.poisson) / sdrMinus1 / sdrMinus1 / aDotCLfactor_backfilled);
}

void BeamModel::converteffopen(const Parameters parameters)
{
    wStar2dash *= v0 / (2.0 * outflowLength * parameters.radius);
	wStar2dash2 *= v0 / pow(2.0 * outflowLength * parameters.radius, 2);
}

void BeamModel::iteration(const Parameters parameters, Backfill backfill, Creep creep)
{
    extern File file;
	maxIterations=100;
	notConverged = 1;
	iterations = 0;
	noCrackOpening = 0;
    error = 0;
    int infoLevel =0;

    if ((parameters.outflowModelOn==2) & (parameters.verbose==2))
    {
        dialog *e = new dialog;
        e->Warning("Starting outflowLength refinement with outflow length = ", outflowLength);
        e->exec();
    }		
	do
	{	// Refine given outflow length using the discharge analysis:
		lambdaLast = outflowLength;
		zetaBackfilledLast = zetaBackfilled;
	
		//	Dimensionless foundation stiffness 
		stiffness(); 
		
		//	Dimensionless crack speed 
		cspeed(parameters, backfill);

        file.collect(this, 0);

		//	Determine (either by analytical or FD method) the opening profile v*(zeta) for a given outflow length control.lambda and the properties of it which are needed for analysis.
        if (parameters.solutionmethod==2)
		{	// ...then use FINITE DIFFERENCE solution method:
			//		short waitForMe;	

			// Make first guess for closure length -- two nodes less than input value -- and construct FD solution:
			nodeAtClosure -= 2;
			double wStarMax = 0.0;
            FDprofile fdSolution(alpha, m, zetaBackfilled, vStarRes, parameters.elementsinl, nodeAtClosure);

			short nodeAtClosure_previous = nodeAtClosure;				// Store position of last node in this FD array
			double errorLast = fdSolution.closureMoment();				// ...and resulting d2v/dz2 at closure point, divided by that at crack tip
        if (infoLevel > 1)
		{
            dialog *e = new dialog;
            e->Warning("Starting closure length refinement with closure node = ",nodeAtClosure_previous, "and closure moment = ", errorLast);
            e->exec();
		}

	// Make second guess for closure length (two nodes MORE than input value):
		nodeAtClosure += 4;

        if (parameters.verbose==2)
        {
            dialog *e = new dialog;
            e->Warning("Second-guess closure node = ", nodeAtClosure);
            e->exec();
        }

		// Prepare to refine closure length by iteration
		double dontNeedThis;
        error = 0;
        iterations = 0;
        short maximumNonContact = 0;

        //Need to declare again here! Without this, program exits first loop immediately, hence provides incorrect solutions
        short notConverged = 1;

		do
		{	// ...until bending moment at closure point is negligible compared to that at crack tip:

            fdSolution = FDprofile(alpha, m, zetaBackfilled, vStarRes, parameters.elementsinl, nodeAtClosure);
			error = fdSolution.closureMoment();
            short noSurfaceContact = 1;								// FIXME:  necessary?
            short minPoint = fdSolution.nodeAtMinimum();			// this is set to -1 if NO minimum is found within domain
            if (parameters.verbose==2)
			{
                dialog *e = new dialog;
                e->Warning("At closure length iteration ",iterations," closure moment = ", error, " min at point ",minPoint);
                e->exec();
			}	
			if (minPoint > 0)
			{
                if (parameters.verbose==2)
                {
                    dialog *e = new dialog;
                    e->Warning("BUT there's a minimum (crack surface overlap) to left of closure point ", minPoint);
                    e->exec();
                }

				// So back up to find maximum closure length with NO overlap:
				double tempError;
				nodeAtClosure = minPoint - 2;
                if (nodeAtClosure < (parameters.elementsinl + 1))
                    nodeAtClosure = parameters.elementsinl + 1;	// Is this really necessary?  Closure might really occur inside decompression length!
				short newMin;
				do
				{
                    fdSolution = FDprofile(alpha, m, zetaBackfilled, vStarRes, parameters.elementsinl, nodeAtClosure);
					tempError = fdSolution.closureMoment();
					newMin = fdSolution.nodeAtMinimum();
                    if (parameters.verbose==2)
					{
                        dialog *e = new dialog;
                        e->Warning("nodeAtClosure = ",nodeAtClosure, " error = ", tempError, " min point = ", newMin);
                        e->exec();
					}	
					nodeAtClosure++;
				}
				while (newMin < 0);
				nodeAtClosure = nodeAtClosure - 1;
                if (parameters.verbose==2)
                {
                    dialog *e = new dialog;
                    e->Warning("Least worst non-contacting solution nodeAtClosure = ", nodeAtClosure);
                    e->exec();
                }
					
				maximumNonContact = true;
                fdSolution = FDprofile(alpha, m, -1.0, vStarRes, parameters.elementsinl, nodeAtClosure);

				error = fdSolution.closureMoment();
				integral_wStar2 = fdSolution.integral_wStar2();
				fdSolution.findBackfillEjectPoint(zetaBackfillEject, dontNeedThis);

			}
			else
			{
				nodeAtClosure++;
                if (parameters.verbose==2)
                {
                    dialog *e = new dialog;
                    e->Warning("node interpolated = ", nodeAtClosure);
                    e->exec();
                }
		
			}

			if (maximumNonContact)	// not necessarily converged, but the best available
				notConverged = 0;
			else if ((fabs(error) < 0.01 and noSurfaceContact) or maximumNonContact)
				{	// converged:
					notConverged = false;
					fdSolution.outflowPointValues(wStar2, wStar2dash, wStar2dash2, integral_wStar2);	
					fdSolution.findBackfillEjectPoint(zetaBackfillEject, dontNeedThis);
					wStarMax = fdSolution.wStarMax(nodeAtClosure);
				}
				else
				{
                    if (parameters.verbose==2)
                    {
                        dialog *e = new dialog;
                        e->Warning("Next try for iteration will be nodeAtClosure = ", nodeAtClosure);
                        e->exec();
                    }

					errorLast = error;
					iterations++;
				}

            file.collect(this, 0);

			} // done that refinement iteration
			while (notConverged & (iterations < maxIterations));

            if (parameters.verbose==2)
			{
                dialog *e = new dialog;
                e->Warning("At nodeAtClosure = ", nodeAtClosure, " converged in ", iterations," iterations with error = ", error);
                e->exec();
			}

        } // done FD solution
		else
        {
            //Formally location of analytical solution
		} 
	
        if (parameters.verbose==2)
		{
            dialog *e = new dialog;
            e->Warning("Computed profile properties", "Ejection point = ", zetaBackfillEject, "Opening at outflow point = ", wStarMax, "1st-deriv at outflow = ", wStar2dash, "2nd-deriv at outflow = ", wStar2dash2, "Integral to outflow = ", integral_wStar2);
            e->exec();
		}

		if (integral_wStar2 > 0.0)
		{
            if (parameters.outflowModelOn==2)
			{	
				double throatArea = integral_wStar2;
				OutflowProcess outflow(p1bar);
				outflowLength = pow(factor * outflow.get_tStarOutflow() / throatArea, 0.2);
			}
		//	tStarOutflow being the number of characteristic times for discharge
            if (parameters.verbose==2)
			{	                
                dialog *e = new dialog;
                e->Warning("alpha = ", alpha[1], "m = ", m[1], "integral_wStar2 = ", integral_wStar2, "New outflowLength = ", outflowLength);
                e->exec();
			}
			lambdaPow4 =  pow(outflowLength, 4);
			v0 = v00 * lambdaPow4;
			vStarRes = creep.residualCrackClosure / v0 / Constants::kilo;

			if ((fabs(1.0 - lambdaLast / outflowLength) < nodeResolution) and (fabs(1.0 - zetaBackfilledLast / zetaBackfilled) < nodeResolution))
				notConverged = false;

			iterations++;
			short waitForMe;
            if (infoLevel > 2)
			{	
//				waitForMe=interface.input("enter digit: ");
			}
		}
		else
		{
			noCrackOpening = 1;
		}

        file.collect(this, 0);

	} // end outflow length refinement
    while (notConverged & (iterations < maxIterations)  and not noCrackOpening);
}

void BeamModel::opening(Parameters parameters, Creep creep)
{

    int infoLevel=0;
    extern Solution solution;
	//	So we now have the correct numerical or analytical crack opening profile vStar(zeta), and can output it if needed


        if (parameters.verbose==2)
		{
            dialog *e = new dialog;
            e->Warning("Final outflowLength convergence in ", iterations, " iterations for outflowLength = ", outflowLength);
            e->exec();
		}
        if (parameters.solutionmethod==2)
        {	// then recalculate and print the numerical solution
				
            FDprofile final(alpha, m, zetaBackfilled, vStarRes, parameters.elementsinl, nodeAtClosure);
            FDprofile* ptr=&final;
            final.fprofile();
				
            final.findBackfillEjectPoint(zetaBackfillEject, vStarDashBackfillEject);
            final.outflowPointValues(wStar2, wStar2dash, wStar2dash2, integral_wStar2);

            solution.sprofile(final.zeta, final.vptra, final.l);

        }
        else
        {
			//Originally Analytical Method
        }
		
		wStar2 *= v0;
	
		// Convert derivatives from vStar(zeta) to v(z)
		converteffopen(parameters);
	
		//	Flaring of pipe wall at decompression point:
		deltaDStar = wStar2 / Constants::pi / parameters.diameter * Constants::kilo + creep.diameterRes0 / parameters.diameter - 1.0;		

        if (iterations == maxIterations)  cout << "UNCONVERGED";
			
}
