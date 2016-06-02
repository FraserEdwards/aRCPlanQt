//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Class providing functions to vary decompression length to find solutions

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

#include "Constants.h"
#include "OutflowProcess.h"
#include "File.h"

const short OutflowProcess::maxTimeSteps = 100;

// Null constructor
OutflowProcess::OutflowProcess()
{

}	

OutflowProcess::OutflowProcess(const double p1Gauge)
{
    extern File file;
    //  A vessel of volume V, which initially contained gas at pressure p1Gauge, discharges through an aperture of throat area = exit area = A.
    //  Pressure is computed as a function of time t/tChar where tChar = V / (A c0) and cO is the sonic velocity.
    //  The pressure decay curve is then fitted to a straight line and characterised by a single time.
    //
    //  Ratio of internal to ambient absolute pressures below which outflow will be unchoked:
    pStarUnchoke = pow((Constants::gamma + 1.0) / 2.0, Constants::gamma / (Constants::gamma - 1.0));
//  xUnch = X(pStarUnchoke);
    double p1 = p1Gauge + Constants::pAtm;                  //  Convert to absolute pressure
    double p1Star = p1 / Constants::pAtm;                   //  Ratio of absolute initial vessel pressure to atmosphere pressure
    pStar = p1Star;
    pHalfStar = p1Gauge / 2.0 + Constants::pAtm;
    int firstHalf = 1;                                      //  gauge pressure is still more than half initial value
    double pStarXcess = pStar - pStarUnchoke;

    file.collect(this,0);

    //  Calculate the pressure/time history (if any) for choked adiabatic discharge, at uniform time intervals deltaTStar,
    //  and integrate pressure vs. time using Simpson.
    int iIsOdd;                                             // Boolean
    double pStarLast;
    //  Unless outflow is already unchoked, calculate pressures at regular time intervals until it is, while integrating pressure wrt time:
    double deltaTStar = 5.0 / OutflowProcess::maxTimeSteps;
    double simpsonIntegral = p1Star;                        // First Simpson point weighted at 1
    int i = 0;
    while (pStarXcess > 0.0)
    {
        i++;
        iIsOdd = i - 2 * (i / 2);
        tStar = double(i) * deltaTStar;
        pStarLast = pStar;
        pStar = p1 * pp1WhileChoked(tStar);
//	Did gauge pressure just fall below half?  If so, estimate full outflow time by this method.
                if (firstHalf && (pStar <= pHalfStar))
                {
                    firstHalf = false;
                    tStarOutflow2 = 2.0 * (tStar - (pHalfStar - pStar) / (pStarLast - pStar) * deltaTStar);
                }
        pStarXcess = pStar - pStarUnchoke;
        if (iIsOdd)
            simpsonIntegral += pStar * 4.0;                 // Odd Simpson points (other than first) are weighted at 4
        else
            simpsonIntegral += pStar * 2.0;                 // ...and even ones (except the last) are weighted at 2
    }

    //  We are now in the unchoked region but have placed a Simpson point here, so a correction is needed to round off choked region integration.
    double correction = pStarXcess / (pStar - pStarLast);      // We are inside the unchoked region by this fraction of a trapezoid width.
    tStarUnchoke = tStar - deltaTStar * correction;
    if (i > 0)                                              // If there ever was a choked region...
    {
        if (iIsOdd)                                         // ...then last point lay between a new strip pair. Cancel its contribution and add a trapezoid instead.
            simpsonIntegral = simpsonIntegral - pStar * 4.0 + 1.5 * (pStarUnchoke + pStar) * correction;
        else                                                // ...last point completed a strip pair. Correct its weighting and trim off excess trapezoid.
            simpsonIntegral = simpsonIntegral - pStar       - 1.5 * (pStarUnchoke + pStar) * (1 - correction);
    }
    double integralPressureDt = simpsonIntegral * deltaTStar / 3.0;

//	Outflow is now unchoked. Calculate times for, and integrate by Simpson, 10 strips for pressure intervals from the initial value down to zero
    double deltaPStar = (pStarUnchoke - 1.0) / 10.0;
//  Value at origin (i=0, p = p_unch) is t* - t*_unch = 0
    simpsonIntegral = 0.0;
    for (int i = 1; i < 11; i++)
    {
        iIsOdd = i - 2 * (i / 2);
        pStar = pStarUnchoke - double(i) * deltaPStar;
        tStar = tStarWhileUnchoked(X(pStarUnchoke), pStar);
        if (iIsOdd)
            simpsonIntegral += tStar * 4.0;
        else
            simpsonIntegral += tStar * 2.0;
    }
//  Final (11th point) value
    simpsonIntegral += tStarWhileUnchoked(X(1.0), 1.0);;
    integralPressureDt += simpsonIntegral * deltaPStar / 3.0;

//  Hence the outflow time by method 1, assuming linear pressure/time decay throughout
    integralPressureDt *= 2.0 / (p1 - Constants::pAtm);
    tStarOutflow = 2.0 * integralPressureDt / p1Gauge;

file.collect(this,0);

} // end constructor.


double OutflowProcess::X(double pp0)
{// Function of pressure ratio
    return sqrt(pow(pp0, (1.0 - 1.0 / Constants::gamma)) - 1.0);
}// end


double OutflowProcess::pp1WhileChoked(double tStar)
{//  Choked adiabatic discharge
	double gPlus12 = (Constants::gamma + 1) / 2;
	double gMinus1 =  Constants::gamma - 1;
	double temp = pow(gPlus12, -gPlus12 / gMinus1); 
    return pow((1 + gMinus1 / 2 * temp * tStar), -2 * Constants::gamma / gMinus1);
}// end Choked.


double OutflowProcess::tStarWhileUnchoked(double xUnch, double pStar)
{// Time since unchoking, unchoked adiabatic discharge
	double gMinus12 =  (Constants::gamma - 1) / 2;
    double x = X(pStar);
    double watchMe = pow(pStar, gMinus12 / Constants::gamma) / sqrt(gMinus12) * (xFunction(xUnch) - xFunction(x));
    return watchMe;
}// end Choked.


double OutflowProcess::xFunction(double x)
{
	double sqrtx21 = sqrt(x * x + 1);
	return x * (x * x / 4 + 0.625) * sqrtx21 + 0.375 * log(x + sqrtx21);
}// end xFunction;


double OutflowProcess::get_tStarOutflow()
{
	return tStarOutflow;
}// end tStar.


void OutflowProcess::pressurePlot()
{
//	outflowFile.open("outflowPressurePlot.txt");
//	if(outflowFile.fail())
//	{
//		cout << "outflowPressurePlot results output file could not be opened.  Is it in use by another application?\n";
//		exit(1);
//	}
//	Calculate internal/ambient pressure ratio at unchoking:
	cout << "Unchoking pressure = " << pStarUnchoke * Constants::pAtm << " bar " << endl;
//	outflowFile.close();
}// end plot.

