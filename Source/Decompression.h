//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef _DECOMPRESSION_H
#define _DECOMPRESSION_H

class Decomp
{
private:

	double p1;
	double p0;	
	double aDotc0;
	double argument;
	double gamma_;

public:

	Decomp();
	void p1p0(double p0, double gamma_, double aDotC0);
	double p1p0r;

};

#endif
