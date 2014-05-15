#pragma once
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
