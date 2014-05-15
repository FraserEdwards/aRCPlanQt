#ifndef BeamModelH
#define BeamModelH

#include <vector>

#include "Backfill.h"
#include "Creep.h"

class BeamModel 
{// 
	private:
									
		double dStarMinus1;
		double dStarMinus2;		
		double baffleLeakageArea;

		
		short fdArraySize;
		double decompression;
		
		
public:	

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

		// Constructs a dynamic beam-on-elastic-foundation model of the specific pipe RCP case
        BeamModel(const Parameters parameters);

        void initialise();
		
		// Speed dependent properties and reset for outflow length
		void speedandreset(const Parameters parameters, Backfill backfill, Creep creep);	

		// Dimensionless foundation stiffness
		void stiffness();

		// Dimensionless crack speed [0] with backfill and [1] without
		void cspeed(const Parameters parameters, const Backfill backfill);

		void converteffopen(const Parameters parameters);

        void iteration(Parameters parameters, Backfill backfill, Creep creep);

        void opening(Parameters parameters, Creep creep);


};

#endif
