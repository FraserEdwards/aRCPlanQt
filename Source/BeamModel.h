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
{
private:
									
        int n;
		
		
public:	
        double dstarminus1;
        double dstarminus2;
        double baffle_leakage_area;
        short fd_array_size;
        double decompression;
        double zetaclosure;
        short print_opening_profile;
        double deltadstar;
        int l;
        short max_iterations;
		double m[2];
		double alpha[2];
        double hoverr;
        double lambda_last;
        double zetabackfilledlast;
        short not_converged;
		short iterations;
        short no_crack_opening;
        double wstar2, wstarmax, wstar2dash, wstar2dash2, integral_wstar2;
        double zetabackfilleject;
		double p1p0r;
        double dynamic_shear_modulus;
        double node_resolution;
		double v0;
		double factor;
		double p1bar;
		double vStarRes;
        short node_at_closure;
        double adotovercl;
        double adotclfactor;
        double adotclfactor_backfilled;
        double lambdapow4;
        double sdrminus1;
        double sdrminus2;
        double zetabackfilled;
        double outflow_length;
		double v00;
        double error;
        double available_internal_volume;
        vector<double> zeta;
        vector<double> crack_displacement;
        double vstardashbackfilleject;
        double pressurefactor;
        double residualpressure;

		//Null constructor
	    BeamModel();

        //Constructs a dynamic beam-on-elastic-foundation model of the specific pipe RCP case
        BeamModel(const Parameters parameters);

        //Clears all values within beammodel
        void initialise();
		
		// Speed dependent properties and reset for outflow length
        void reset(const Parameters parameters, Backfill backfill, Creep creep);

		// Dimensionless foundation stiffness
		void stiffness();

		// Dimensionless crack speed [0] with backfill and [1] without
        void crackSpeed(const Parameters parameters, const Backfill backfill);

        //Converts from v to w
        void convertEffOpen(const Parameters parameters);

        //Iteration function to find solution
        void iteration(Parameters parameters, Backfill backfill, Creep creep);

        //Finds final crack profile and calls conversion function
        void opening(Parameters parameters, Creep creep);


};

#endif
