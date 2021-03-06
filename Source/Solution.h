//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef _SOLUTION_H
#define _SOLUTION_H

#include <cstdlib>
using namespace std;

#include "FDprofile.h"
#include "Parameters.h"

class Solution{

private:
	

public:
	int soln;
    int k;
    int i;
    int n;
	
    vector<double> z;
    vector <vector <double > > w;

    vector <double> adotc0;
    vector <double> p0bar;
    vector <double> tempdegc;

	vector <double> decompression;
	vector <double> alpha;
	vector <double> m;
    vector <double> outflow_length;
    vector <double> deltadstar;
    vector <double> gs1;
    vector <double> gue;
    vector <double> gsb;
    vector <double> gkb;
    vector <double> gg0;
    vector <double> gtotal;
	vector <double> g0;
    vector <double> forplot;
    vector <short> no_crack_opening;
    vector <short> not_converged;
    vector <short> iterations;

    //Null constructor
	Solution();

    //Clears all values within solution and resizes array
    void clear();

    //Initialises displacement values
    void displacement(Parameters &parameters);

    //Assigns crack profiles to matrix for access later to produce plots in GUI
    void collectProfile(vector<double> vptras, const int l);

    //Collects values provided as arguments, forming them in to solution object
    void collect(const double adotc0s, const double p0bars, const double tempdegcs, const double decompressions, const double alphas, const double ms, const double outflowlengths, const double deltadstars,
                            const double gs1s, const double gues, const double gsbs, const double gkbs, const double g0s, const double gg0s, const double gtotals, const short no_crack_openings, const short not_converged, const short iterations);
};
#endif
