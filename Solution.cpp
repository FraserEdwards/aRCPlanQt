#include <iostream>
#include <iomanip>

#include "Solution.h"



Solution::Solution(){

    soln=0;
    aDotc0.push_back(0.0);
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


}

void Solution::clear()
{
    soln=0;
    k=0;
    aDotc0.clear();
    aDotc0.resize(1);
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

    cout << "Row size: " << row.size() << endl;
    cout << "w size: " << w.size() << endl;
    cout << "z size: " << z.size() << endl;

}


void Solution::sprofile(const vector<double> zetas, const vector<double> vptras, const int ls)
{
    k++;
	vptra=vptras;

    for(i = 0; i <= ls; i++)
    {
        w[k][i]=vptras[i];
    }

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

