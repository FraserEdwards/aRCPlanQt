#include "Solution.h"
#include <iostream>
#include <iomanip>

Solution::Solution(){

	soln=0;
	aDotc0.push_back(0.0);

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

}

Solution::Solution(Parameters parameters){

    soln=0;
    aDotc0.push_back(0.0);

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

}


void Solution::sprofile(const vector<double> zetas, const vector<double> vptras, const int ls)
{
    k++;
	zeta=zetas;
	vptra=vptras;
    l=ls;

}

void Solution::Tvalues(const double aDotc0s, const double p0bars, const double tempDegCs, const double decompressions, const double alphas, const double ms, const double outflowLengths, const double deltaDStars,
							const double gS1s, const double gUEs, const double gSbs, const double gKbs, const double g0s, const double gG0s, const double gTotals)
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

	if (gG0s < 1000)
	{gG0.push_back(gG0s);}  
	else
	{gG0.push_back(0.0);}

	if (gTotals < 1000)
	{gTotal.push_back(gTotals);}
	else
	{gTotal.push_back(0.0);}
	
}

void Solution::Tvalues(const double aDotc0s, const double decompressions, const double alphas, const double ms)
{
	soln++;
	aDotc0.push_back(aDotc0s);
	decompression.push_back(decompressions);
	alpha.push_back(alphas);
	m.push_back(ms);
	
}

Solution* Solution::retrieve()
{

    return this;

}

