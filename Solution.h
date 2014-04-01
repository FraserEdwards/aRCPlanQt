#include <cstdlib>
using namespace std;

#include "FDprofile.h"

#ifndef _SOLUTION_H
#define _SOLUTION_H

class Solution{

private:
	

public:
	int soln;
	int l;
    int k;
	
	vector<double> zeta;
	vector<double> vptra;	
    vector <vector <double> > zetam;
    vector <vector <double > > vptram;

	vector <double> aDotc0;	
	vector <double> decompression;
	vector <double> alpha;
	vector <double> m;
	vector <double> outflowLength;
	vector <double> deltaDStar;
	vector <double> gS1;
	vector <double> gUE;
	vector <double> gSb;
	vector <double> gKb;
	vector <double> gG0;
	vector <double> gTotal;
	vector <double> g0;

	Solution();
	void sprofile(vector<double> zeta, vector<double> vptra, const int l);
	void Tvalues(const double aDotc0s, const double decompressions, const double alphas, const double ms, const double outflowLengths, const double deltaDStars,
							const double gS1s, const double gUEs, const double gSbs, const double gKbs, const double g0s, const double gG0s, const double gTotals);
	void Tvalues(const double aDotc0s, const double decompressions, const double alphas, const double ms);
};
#endif
