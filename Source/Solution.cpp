//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Class which collects solution values in to one object for easy storage and access
//     Collects solution values as well as crack profiles for access later

#include <iostream>
#include <iomanip>

#include "Solution.h"

Solution::Solution(){

    soln=0;
    aDotc0.push_back(0.0);
    p0bar.push_back(0.0);
    tempDegC.push_back(0.0);
    z.push_back(0.0);
    k=0;

    decompression.push_back(0.0);
    alpha.push_back(0.0);
    m.push_back(0.0);
    outflowLength.push_back(0.0);
    deltaDStar.push_back(0.0);
    gS1.push_back(0.0);
    gUE.push_back(0.0);
    gSb.push_back(0.0);
    gKb.push_back(0.0);
    gG0.push_back(0.0);
    gTotal.push_back(0.0);
    g0.push_back(0.0);
    noCrackOpening.push_back(1);
    notConverged.push_back(1);
    iterations.push_back(0);

}

void Solution::clear()
{
    soln=0;
    k=0;
    aDotc0.clear();
    aDotc0.resize(1);
    p0bar.clear();
    p0bar.resize(1);
    tempDegC.clear();
    tempDegC.resize(1);
    z.clear();
    z.resize(1);
    w.clear();
    w.resize(1);

    decompression.clear();
    decompression.resize(1);
    alpha.clear();
    alpha.resize(1);
    m.clear();
    m.resize(1);
    outflowLength.clear();
    outflowLength.resize(1);
    deltaDStar.clear();
    deltaDStar.resize(1);
    gS1.clear();
    gS1.resize(1);
    gUE.clear();
    gUE.resize(1);
    gSb.clear();
    gSb.resize(1);
    gKb.clear();
    gKb.resize(1);
    gG0.clear();
    gG0.resize(1);
    gTotal.clear();
    gTotal.resize(1);
    g0.clear();
    g0.resize(1);
    noCrackOpening.clear();
    noCrackOpening.resize(1);
    notConverged.clear();
    notConverged.resize(1);
    iterations.clear();
    iterations.resize(1);

}

void Solution::displacement(Parameters &parameters)
{
    n = (parameters.elementsinl * (parameters.lambda+2))+1;
    vector<double> row;

    for(i = 0; i < n; i++ )
    {
        row.push_back(0.0);
    }
    for(i = 0; i < parameters.rangenumber; i++)
    {
        w.push_back(row);
    }

    for(i = 1; i < n; i++)
    {

        z.push_back(double(i)/double(parameters.elementsinl));

    }

}


void Solution::sprofile(const vector<double> zetas, const vector<double> vptras, const int ls)
{
    k++;
    for(i = 0; i <= ls; i++)
    {
        w[k][i]=vptras[i];
    }

}

void Solution::Tvalues(const double aDotc0s, const double p0bars, const double tempDegCs, const double decompressions, const double alphas, const double ms, const double outflowLengths, const double deltaDStars,
                            const double gS1s, const double gUEs, const double gSbs, const double gKbs, const double g0s, const double gG0s, const double gTotals, const short noCrackOpenings, const short notConvergeds, const short iterationss)
{
	soln++;
	aDotc0.push_back(aDotc0s);
    p0bar.push_back(p0bars);
    tempDegC.push_back(tempDegCs);

	decompression.push_back(decompressions);
	alpha.push_back(alphas);
	m.push_back(ms);
	outflowLength.push_back(outflowLengths);
	deltaDStar.push_back(deltaDStars);
	gS1.push_back(gS1s);
	gUE.push_back(gUEs);
	gSb.push_back(gSbs);
	gKb.push_back(gKbs);
	g0.push_back(g0s);

    noCrackOpening.push_back(!noCrackOpenings);
    notConverged.push_back(!notConvergeds);
    iterations.push_back(iterationss);

    if (gG0s < 1000)
    {gG0.push_back(gG0s);}
    else
    {gG0.push_back(0.0);}

    if (gTotals < 1000)
    {gTotal.push_back(gTotals);}
    else
    {gTotal.push_back(0.0);}
	
}
