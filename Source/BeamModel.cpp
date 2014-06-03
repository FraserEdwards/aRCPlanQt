//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Large class containing the equivalent beam model
//     Contains the iteration function which is sizeable and still relatively complex

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
//Calculates properties which aren't dependant on speed
BeamModel::BeamModel(const Parameters parameters)
{
    initialise();
    extern File file;

	//Proportion of internal volume available for expansion
    available_internal_volume = 1.0 - parameters.water_inside_pipe - parameters.solid_inside_pipe;

	//Factors for modelling of S4 baffle leak
    baffle_leakage_area=parameters.diameter / Constants::kilo;  //m
    baffle_leakage_area = baffle_leakage_area * baffle_leakage_area * 0.01 * Constants::pi * (parameters.sdr - 2.0) / parameters.sdr;

	//Parameters for equivalent beam model
    dynamic_shear_modulus = parameters.dynamic_modulus / 2.0 / (1.0 + parameters.poisson);
    sdrminus1 = parameters.sdr - 1.0;
    sdrminus2 = sdrminus1 - 1.0;

    file.collect(this,0);

}

//Clears all values within class
void BeamModel::initialise()
{

    dstarminus1 = 0.0;
    dstarminus2 = 0.0;
    baffle_leakage_area = 0.0;
    fd_array_size = 0;
    decompression = 0.0;

    zetaclosure = 0.0;

    l = 0;
    max_iterations = 0;
    hoverr = 0.0;
    lambda_last = 0.0;
    zetabackfilledlast = 0.0;
    not_converged = 1;
    iterations = 0;
    no_crack_opening = 0;
    wstar2 = 0.0;
    wstarmax = 0.0;
    wstar2dash = 0.0;
    wstar2dash2 = 0.0;
    integral_wstar2 = 0.0;
    zetabackfilleject = 0.0;
    p1p0r = 0.0;
    dynamic_shear_modulus = 0.0;
    node_resolution = 0.0;
    v0 = 0.0;
    factor = 0.0;
    p1bar = 0.0;
    vStarRes = 0.0;
    node_at_closure = 0;
    adotovercl = 0.0;
    adotclfactor = 0.0;
    adotclfactor_backfilled = 0.0;
    lambdapow4 = 0;
    sdrminus1 = 0.0;
    sdrminus2 = 0.0;
    zetabackfilled = 0.0;
    outflow_length = 0.0;
    v00 = 0.0;
    error = 0.0;
    available_internal_volume = 0.0;
    vstardashbackfilleject = 0.0;

    m[0] = 0.0;
    m[1] = 0.0;
    alpha[0] = 0.0;
    alpha[1] = 0.0;
    n = 0;

}

//Calculates properties dependent on the independent variable: speed, temperature, pressure
//Also resets certain values at the beginning of each simulation
void BeamModel::reset(const Parameters parameters, const Backfill backfill, Creep creep)
{
    extern File file;
	//  Set initial outflow length

    zetaclosure = 2.0;				//	Point (in outflow lengths) at which crack re-closes, with first guess.
    node_resolution = 0.5 / parameters.elements_in_l;	// used as a reference tolerance
    node_at_closure = short(zetaclosure * parameters.elements_in_l);
    zetabackfilled = 0.2;		// first guess

    outflow_length = parameters.lambda;
    lambdapow4 =  pow(outflow_length, 4);
		
	//For FS configuration, prior decompression
	p1bar=parameters.p0bar;
	Decomp decomp;
	// Proportion of initial pressure which remains at crack tip	
	decomp.p1p0r=1.0;		

    //Checks against 2 as checkboxes are assigned this value when ticked, rather than 1
    if(parameters.fullscale==2)
						{

                        available_internal_volume=1.0;

                        decomp.p1p0(parameters.p0bar, Constants::gamma, parameters.adotc0);

						p1bar=parameters.p0bar * decomp.p1p0r; //New p1, could replace with p1 from decomp object, need to trace

						}

    p1p0r=decomp.p1p0r; //TODO: swap throughout remainder of code, so only decomp.p1p0r is used

	//	v00 becomes reference length v0 on multiplying by lambda^4
    v00 = 0.4 / Constants::c1 * sdrminus1 * sdrminus2 / parameters.sdr * p1bar / parameters.dynamic_modulus * parameters.diameter / Constants::mega;	//	(m)

	//	Dimensionless virtual crack opening at crack tip (representing residual strain)
    v0 = v00 * lambdapow4;			//	(m)
    vStarRes = creep.residual_crack_closure / v0 / Constants::kilo;

	// Parameters for equivalent beam model (speed dependent)
    adotovercl = parameters.adotc0 * Constants::vSonic / sqrt(parameters.dynamic_modulus * Constants::giga / parameters.density);
    adotclfactor = 1.0 + adotovercl * adotovercl;

    adotclfactor_backfilled = 1.0 + adotovercl * adotovercl * backfill.density_ratio;

    factor = Constants::pi * Constants::c1 * 625.0 * parameters.dynamic_modulus / p1bar * available_internal_volume * sdrminus2 / sdrminus1 / sdrminus1 * parameters.adotc0;	// Note GPa / bar / 16 = 625

    file.adotc0 = parameters.adotc0;
    file.collect(this, 0);

}

//	Dimensionless foundation stiffness [0] with backfill and [1] without
void BeamModel::stiffness()
{

    m[1] = 8.0 / 3.0 / Constants::pi / Constants::c1 / sdrminus1 / sdrminus1 * lambdapow4;
    m[0] = m[1] / adotclfactor_backfilled;
    m[1] /= adotclfactor;
}

//	Dimensionless crack speed [0] with backfill and [1] without
void BeamModel::cspeed(const Parameters parameters, const Backfill backfill)
{

    alpha[1] = outflow_length * sqrt(Constants::c3 * adotovercl * adotovercl + Constants::c4 / 2.0 / (1.0 + parameters.poisson) / sdrminus1 / sdrminus1 / adotclfactor);
    alpha[0] = outflow_length * sqrt(Constants::c3 * adotovercl * adotovercl * backfill.density_ratio + Constants::c4 * 0.5 / (1.0 + parameters.poisson) / sdrminus1 / sdrminus1 / adotclfactor_backfilled);
}

//Converts opening from v to w
void BeamModel::convertEffOpen(const Parameters parameters)
{
    wstar2dash *= v0 / (2.0 * outflow_length * parameters.radius);
    wstar2dash2 *= v0 / pow(2.0 * outflow_length * parameters.radius, 2);
}

//Iteration function
//Uses two loops to calculate solution for the given parameters
void BeamModel::iteration(const Parameters parameters, Backfill backfill, Creep creep)
{
    extern File file;
    max_iterations=50;
    not_converged = 1;
	iterations = 0;
    no_crack_opening = 0;
    error = 0;
    int infoLevel =0;

    //Checked against 2 as checkboxes are assigned 2 when selected rather than 1
    if ((parameters.outflow_model_on==2) & (parameters.verbose==2))
    {
        dialog *e = new dialog;
        e->warning("Starting outflowLength refinement with outflow length = ", outflow_length);
        e->exec();
    }		
	do
	{	// Refine given outflow length using the discharge analysis:
        lambda_last = outflow_length;
        zetabackfilledlast = zetabackfilled;
	
		//	Dimensionless foundation stiffness 
		stiffness(); 
		
		//	Dimensionless crack speed 
		cspeed(parameters, backfill);

        file.collect(this, 0);

		//	Determine (either by analytical or FD method) the opening profile v*(zeta) for a given outflow length control.lambda and the properties of it which are needed for analysis.
        if (parameters.solution_method==2)
        {
            // ...then use FINITE DIFFERENCE solution method:
			//		short waitForMe;	

			// Make first guess for closure length -- two nodes less than input value -- and construct FD solution:
            node_at_closure -= 2;
            double wstarmax = 0.0;
            FDprofile fdSolution(alpha, m, zetabackfilled, vStarRes, parameters.elements_in_l, node_at_closure);

            short nodeAtClosure_previous = node_at_closure;				// Store position of last node in this FD array
			double errorLast = fdSolution.closureMoment();				// ...and resulting d2v/dz2 at closure point, divided by that at crack tip
        if (infoLevel > 1)
		{
            dialog *e = new dialog;
            e->warning("Starting closure length refinement with closure node = ",nodeAtClosure_previous, "and closure moment = ", errorLast);
            e->exec();
		}

        // Make second guess for closure length (two nodes MORE than input value):
        node_at_closure += 4;

        if (parameters.verbose==2)
        {
            dialog *e = new dialog;
            e->warning("Second-guess closure node = ", node_at_closure);
            e->exec();
        }

		// Prepare to refine closure length by iteration
		double dontNeedThis;
        error = 0;
        short maximumNonContact = 0;

        //Need to declare again here! Without this, program exits first loop immediately, hence provides incorrect solutions
        short notConverged = 1;

		do
		{	// ...until bending moment at closure point is negligible compared to that at crack tip:

            fdSolution = FDprofile(alpha, m, zetabackfilled, vStarRes, parameters.elements_in_l, node_at_closure);
			error = fdSolution.closureMoment();
            short noSurfaceContact = 1;								// FIXME:  necessary?
            short minPoint = fdSolution.nodeAtMinimum();			// this is set to -1 if NO minimum is found within domain
            if (parameters.verbose==2)
			{
                dialog *e = new dialog;
                e->warning("At closure length iteration ",iterations," closure moment = ", error, " min at point ",minPoint);
                e->exec();
			}	
			if (minPoint > 0)
			{
                if (parameters.verbose==2)
                {
                    dialog *e = new dialog;
                    e->warning("BUT there's a minimum (crack surface overlap) to left of closure point ", minPoint);
                    e->exec();
                }

				// So back up to find maximum closure length with NO overlap:
				double tempError;
                node_at_closure = minPoint - 2;
                if (node_at_closure < (parameters.elements_in_l + 1))
                    node_at_closure = parameters.elements_in_l + 1;	// Is this really necessary?  Closure might really occur inside decompression length!
				short newMin;
				do
				{
                    fdSolution = FDprofile(alpha, m, zetabackfilled, vStarRes, parameters.elements_in_l, node_at_closure);
					tempError = fdSolution.closureMoment();
					newMin = fdSolution.nodeAtMinimum();
                    if (parameters.verbose==2)
					{
                        dialog *e = new dialog;
                        e->warning("nodeAtClosure = ",node_at_closure, " error = ", tempError, " min point = ", newMin);
                        e->exec();
					}	
                    node_at_closure++;
				}
				while (newMin < 0);
                node_at_closure = node_at_closure - 1;
                if (parameters.verbose==2)
                {
                    dialog *e = new dialog;
                    e->warning("Least worst non-contacting solution nodeAtClosure = ", node_at_closure);
                    e->exec();
                }
					
				maximumNonContact = true;
                fdSolution = FDprofile(alpha, m, -1.0, vStarRes, parameters.elements_in_l, node_at_closure);

				error = fdSolution.closureMoment();
                integral_wstar2 = fdSolution.integral_wStar2();
                fdSolution.findBackfillEjectPoint(zetabackfilleject, dontNeedThis);

			}
			else
			{
                node_at_closure++;
                if (parameters.verbose==2)
                {
                    dialog *e = new dialog;
                    e->warning("node interpolated = ", node_at_closure);
                    e->exec();
                }
		
			}

			if (maximumNonContact)	// not necessarily converged, but the best available
				notConverged = 0;
			else if ((fabs(error) < 0.01 and noSurfaceContact) or maximumNonContact)
				{	// converged:
					notConverged = false;
                    fdSolution.outflowPointValues(wstar2, wstar2dash, wstar2dash2, integral_wstar2);
                    fdSolution.findBackfillEjectPoint(zetabackfilleject, dontNeedThis);
                    wstarmax = fdSolution.wStarMax(node_at_closure);
				}
				else
				{
                    if (parameters.verbose==2)
                    {
                        dialog *e = new dialog;
                        e->warning("Next try for iteration will be nodeAtClosure = ", node_at_closure);
                        e->exec();
                    }

					errorLast = error;
					iterations++;
				}

            file.collect(this, 0);

            // done that refinement iteration
            }
            while (notConverged & (iterations < max_iterations));

            if (parameters.verbose==2)
			{
                dialog *e = new dialog;
                e->warning("At nodeAtClosure = ", node_at_closure, " converged in ", iterations," iterations with error = ", error);
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
            e->warning("Computed profile properties", "Ejection point = ", zetabackfilleject,
                       "Opening at outflow point = ", wstarmax, "1st-deriv at outflow = ", wstar2dash,
                       "2nd-deriv at outflow = ", wstar2dash2, "Integral to outflow = ", integral_wstar2);
            e->exec();
		}

        if (integral_wstar2 > 0.0)
		{
            if (parameters.outflow_model_on==2)
			{	
                double throatArea = integral_wstar2;

				OutflowProcess outflow(p1bar);
                outflow_length = pow(factor * outflow.get_tStarOutflow() / throatArea, 0.2);
			}
		//	tStarOutflow being the number of characteristic times for discharge
            if (parameters.verbose==2)
			{	                
                dialog *e = new dialog;
                e->warning("alpha = ", alpha[1], "m = ", m[1], "integral_wStar2 = ", integral_wstar2, "New outflowLength = ", outflow_length);
                e->exec();
			}
            lambdapow4 =  pow(outflow_length, 4);
            v0 = v00 * lambdapow4;
            vStarRes = creep.residual_crack_closure / v0 / Constants::kilo;

            if ((fabs(1.0 - lambda_last / outflow_length) < node_resolution) and (fabs(1.0 - zetabackfilledlast / zetabackfilled) < node_resolution))
                not_converged = false;

			iterations++;

		}
		else
		{
            no_crack_opening = 1;
		}

        file.collect(this, 0);

	} // end outflow length refinement
    while (not_converged & (iterations < max_iterations)  and not no_crack_opening);
}

void BeamModel::opening(Parameters parameters, Creep creep)
{

    extern Solution solution;
	//	So we now have the correct numerical or analytical crack opening profile vStar(zeta), and can output it if needed

        if (parameters.verbose==2)
		{
            dialog *e = new dialog;
            e->warning("Final outflowLength convergence in ", iterations, " iterations for outflowLength = ", outflow_length);
            e->exec();
		}
        if (parameters.solution_method==2)
        {	// then recalculate and print the numerical solution
				
            FDprofile final(alpha, m, zetabackfilled, vStarRes, parameters.elements_in_l, node_at_closure);
            FDprofile* ptr=&final;
            final.fprofile();
				
            final.findBackfillEjectPoint(zetabackfilleject, vstardashbackfilleject);
            final.outflowPointValues(wstar2, wstar2dash, wstar2dash2, integral_wstar2);

            solution.collectProfile(final.zeta, final.vptra, final.l);

        }
        else
        {
			//Originally Analytical Method
        }
		
        wstar2 *= v0;
	
		// Convert derivatives from vStar(zeta) to v(z)
        convertEffOpen(parameters);
	
		//	Flaring of pipe wall at decompression point:
        deltadstar = wstar2 / Constants::pi / parameters.diameter * Constants::kilo + creep.diameter_res0 / parameters.diameter - 1.0;

        if (iterations == max_iterations)  cout << "UNCONVERGED";
			
}
