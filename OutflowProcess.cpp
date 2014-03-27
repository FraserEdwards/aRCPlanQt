#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

#include "Constants.h"
#include "OutflowProcess.h"

const short OutflowProcess::maxTimeSteps = 100;

OutflowProcess::OutflowProcess()
{	// Null constructor
}	


OutflowProcess::OutflowProcess(double p1Gauge)
{
	//	Computes the pressure as a vessel of volume V discharges through an aperture of throat area = exit area = A, 
	//	as a function of time t/tChar where tChar = V / (A c0), cO being sonic velocity.
	//	Calculate internal/ambient absolute pressure ratio below which outflow will be unchoked:
	pStarUnchoke = pow((Constants::gamma + 1.0) / 2.0, Constants::gamma / (Constants::gamma - 1.0));
	double xUnch = X(pStarUnchoke);
	int unchoked = 0;	//  boolean
	int firstHalf = 1;

	double p1 = p1Gauge + Constants::pAtm;		// Convert to absolute pressure
	double p1Star = p1 / Constants::pAtm;		// Initial ratio of vessel to atmosphere pressure
	double pHalfStar = p1Gauge / 2.0 + Constants::pAtm;
	pHalfStar = pHalfStar / Constants::pAtm;	// p1Star after 50% decompression
	
	//	Calculate (using choked adiabatic case as reference) the discharge history for up to 
	//	5 characteristic times, recording the times at which unchoking and final discharge occur:
	double deltaTStar = 5.0 / OutflowProcess::maxTimeSteps;
	double simpsonIntegral = 0.0;
	double tStarOutflow2;
	double pStarLast;
	double pStar = p1Star;
	double tStar = 0.0;
	double tStarLast = 0.0;
	int i = 1;
	
	//check if flow is already choked
	if (p1Star <= pStarUnchoke)
	{
		unchoked = true;
		tStarUnchoke = 0.0;
	}
	

	
	while ((pStar > 1.0) & (i < maxTimeSteps))
	{
		tStar = double(i) * deltaTStar;
//  Compute pressure assuming choked flow:
//  (we need to even for unchoked flow, since we must then compute time from pressure, not vice versa)
		pStarLast = pStar;
		pStar = p1 * pp1WhileChoked(tStar);

//	Did outflow just unchoke?  If so, interpolate the time at which that occurred.
		if (!unchoked && (pStar <= pStarUnchoke))
		{
			unchoked = true;
			tStarUnchoke = tStar - (pStarUnchoke - pStar) / (pStarLast - pStar) * deltaTStar;
			simpsonIntegral += 0.5 * (pStar + pStarLast - 2.0) * (tStarUnchoke - tStarLast);
			tStarLast = tStarUnchoke;
		}

//	Did pressure just fall below half?  If so, estimate full outflow time.
		if (firstHalf && (pStar <= pHalfStar))
		{
			firstHalf = false;			
			tStarOutflow2 = 2.0 * tStarLast + (pHalfStar - pStarLast) * (tStar - tStarLast) / (pStar - pStarLast);
		}
		
//  If outflow is unchoked then back-calculate the time at which the pressure would reach the choked value calculated aobve:
		if (unchoked)
		{
			tStar = tStarUnchoke + tStarWhileUnchoked(xUnch, pStar);
			simpsonIntegral += 0.5 * (pStar + pStarLast - 2.0) * (tStar - tStarLast);
			tStarLast = tStar;
		}
		else
			simpsonIntegral += 0.5 * (pStar + pStarLast - 2.0) * deltaTStar;
		tStarLast = tStar;
		i = i + 1;
	}	// End of calculation for that pressure/time step

// If we quit because we had the whole pressure/time history:
	if (pStar < 1.0)
	{	//	Compute discharge time by linear interpolation (assuming unchoked flow):
		tStar = tStar - (1.0 - pStar) / (pStarLast - pStar) * (tStar - tStarLast);
		simpsonIntegral += 0.5 * (pStarLast - 1.0) * (tStar - tStarLast);
	}
	else
		cout << "Discharge time has not been reached. \n";
// Fit the outflow time assuming linear pressure/time decay
	simpsonIntegral *= 2.0 / (p1 - Constants::pAtm);
//	tStarOutflow = simpsonIntegral;
	tStarOutflow = tStarOutflow2;
} // end constructor.


double OutflowProcess::X(double pp0)
{// Function of pressure ratio
	return sqrt(pow(pp0, (1 - 1 / Constants::gamma)));
}// end X.


double OutflowProcess::pp1WhileChoked(double tStar)
{//  Choked adiabatic discharge
	double gPlus12 = (Constants::gamma + 1) / 2;
	double gMinus1 =  Constants::gamma - 1;
	double temp = pow(gPlus12, -gPlus12 / gMinus1); 
	return pow((1 + gMinus1 / 2 * temp * tStar), -2 * Constants::gamma / gMinus1);
}// end Choked.


double OutflowProcess::tStarWhileUnchoked(double xUnch, double pp1)
{// Unchoked adiabatic discharge
	double gMinus12 =  (Constants::gamma - 1) / 2;
	double x = X(pp1);
	return pow(pp1, -gMinus12 / Constants::gamma) / sqrt(gMinus12) * (xFunction(xUnch) - xFunction(x));
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

