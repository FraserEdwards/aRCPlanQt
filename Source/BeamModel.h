//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef BeamModelH
#define BeamModelH

#include <vector>

#include "Backfill.h"
#include "Creep.h"

class BeamModel
{//
	private:
									
int n;
		
		
public:	
        double dStarMinus1;
        double dStarMinus2;
        double baffleLeakageArea;
        short fdArraySize;
        double decompression;
        double zetaClosure;
		short printOpeningProfile;
		double deltaDStar;
        int l;
        short maxIterations;
		double m[2];
		double alpha[2];
		double hOverR;	
		double lambdaLast;
		double zetaBackfilledLast;
		short notConverged;
		short iterations;
		short noCrackOpening;
		double wStar2, wStarMax, wStar2dash, wStar2dash2, integral_wStar2;
		double zetaBackfillEject;
		double p1p0r;
		double dynamicShearModulus;		
		double nodeResolution;
		double v0;
		double factor;
		double p1bar;
		double vStarRes;
		short nodeAtClosure;
		double aDotOverCL;
		double aDotCLfactor;
		double aDotCLfactor_backfilled;
		double lambdaPow4;
		double sdrMinus1;
		double sdrMinus2;
		double zetaBackfilled;	
		double outflowLength;
		double v00;
        double error;
		double availableInternalVolume;
        vector<double> zeta;
        vector<double> crackdisplacement;
        double vStarDashBackfillEject;
		
		//Null constructor
	    BeamModel();

        //Constructs a dynamic beam-on-elastic-foundation model of the specific pipe RCP case
        BeamModel(const Parameters parameters);

        //Clears all values within beammodel
        void initialise();
		
		// Speed dependent properties and reset for outflow length
		void speedandreset(const Parameters parameters, Backfill backfill, Creep creep);	

		// Dimensionless foundation stiffness
		void stiffness();

		// Dimensionless crack speed [0] with backfill and [1] without
		void cspeed(const Parameters parameters, const Backfill backfill);

        //Converts from v to w
		void converteffopen(const Parameters parameters);

        //Iteration function to find solution
        void iteration(Parameters parameters, Backfill backfill, Creep creep);

        //Finds final crack profile and calls conversion function
        void opening(Parameters parameters, Creep creep);


};

#endif
