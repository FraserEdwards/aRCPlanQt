// aRCPLan: Control.cpp
//
// Author: Dr Patrick Leevers
// Modified by: Fraser Edwards

// Control.h declares Control class
// Control.cpp initialises Control variables, displays them to user and asks if they'd
// like to change any values

#include <iostream>
using namespace std;

#include "Control.h"

		// Initialise array values
        static const int records = 5;
        int Control::outflowModelOn_lib[5] = {1, 0, 0, 0, 0};
		double Control::lambda_lib[5] = {3.0, 3.0, 3.0, 3.0, 3.0};
        int Control::analyticalSolutionMode_lib[5] = {0, 1, 0, 0, 0};
        int Control::rangenumber_lib[5] = {10,40,30,50,50};
        int Control::elementsinl_lib[5] = {5, 20, 15, 10, 25};
        double Control::aDotc0_lib[5] = {0, 0.2, 0.4, 0.6, 0.8};
        int Control::singlemode_lib[5]={0,2,0,2,0};

// Null constructor
Control::Control()
{	
		outflowModelOn = 0;
		lambda = 0.0;
		analyticalSolutionMode = 0;
        singlemode = 2;
        rangenumber = 0;
        elementsinl = 0;
        aDotc0 = 0;
}	

// Constructor for control parameter set
Control::Control(const short recordNumber, ConfigFile config)
{	

	if (recordNumber > 0 and recordNumber < records + 1)
	{
		short index = recordNumber - 1;
		outflowModelOn = outflowModelOn_lib[index];
		lambda = lambda_lib[index];
		analyticalSolutionMode = analyticalSolutionMode_lib[index];
        singlemode = singlemode_lib[index];
        rangenumber = rangenumber_lib[index];
        elementsinl = elementsinl_lib[index];
        aDotc0 = aDotc0_lib[index];
	}
	else
	{
		cout << "No control library record located:  reading data values from config file\n";
		config.readInto(outflowModelOn, "outflowModelOn");
		config.readInto(lambda, "lambda");
		config.readInto(analyticalSolutionMode, "analyticalSolutionMode");
        config.readInto(singlemode, "Mode");
        config.readInto(rangenumber, "numberOfSpeedValues");
        config.readInto(elementsinl, "elementsInL");
        config.readInto(aDotc0, "aDotc0");

	}
}	

// Make this Control identical to RHS one by operator '='
// Creates the "=" operator for this class
Control& Control::operator=(const Control& rhs)
{
	outflowModelOn = rhs.outflowModelOn;
	lambda = rhs.lambda;
	analyticalSolutionMode = rhs.analyticalSolutionMode;
    singlemode = rhs.singlemode;
    rangenumber = rhs.rangenumber;
    elementsinl = rhs.elementsinl;
    aDotc0 =  rhs.aDotc0;
    from = rhs.from;
    to = rhs.to;

    return *this;
} 
