//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Class providing a decompression model

#include <cmath>

#include "Constants.h"
#include "Decompression.h"

Decomp::Decomp()
{
p0=0.0;
p1=0.0;
p1p0r=0;
gamma_=0.0;
aDotc0=0.0;
argument=0.0;
}

void Decomp::p1p0(double p0, double gamma_, double aDotc0)
{

if(aDotc0<0){
			p1p0r=0.0;
		   }

else if(aDotc0>1){
			p1p0r=1.0;
		   }

else	   {
			argument = 1 - (gamma_ - 1) / (gamma_ + 1) * (1 - aDotc0);
			p1 = (p0 + Constants::pAtm) * pow(argument, 2 * gamma_ / (gamma_ - 1)) - Constants::pAtm;
		   
		   if(p1<0.0){
					  p1=0.0;	   			
		   			 }

		   	p1p0r=p1/p0;

		   }
}
