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
		static const short records = 5;
		short Control::outflowModelOn_lib[5] = {1, 0, 0, 0, 0};
		double Control::lambda_lib[5] = {3.0, 3.0, 3.0, 3.0, 3.0};
		short Control::analyticalSolutionMode_lib[5] = {0, 1, 0, 0, 0};
		short Control::numberOfSpeedValues_lib[5] = {20, 20, 20, 20, 20};
		short Control::elementsInL_lib[5] = {20, 20, 20, 20, 20};
//        double Control::aDotc0_lib[5] = {0, 0.2, 0.4, 0.6, 0.8};

// Null constructor
Control::Control()
{	
		outflowModelOn = 0;
		lambda = 0.0;
		analyticalSolutionMode = 0;
		numberOfSpeedValues = 0;
		elementsInL = 0;
//        aDotc0 = 0;
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
		numberOfSpeedValues = numberOfSpeedValues_lib[index];
		elementsInL = elementsInL_lib[index];
//        aDotc0 = aDotc0_lib[index];
	}
	else
	{
		cout << "No control library record located:  reading data values from config file\n";
		config.readInto(outflowModelOn, "outflowModelOn");
		config.readInto(lambda, "lambda");
		config.readInto(analyticalSolutionMode, "analyticalSolutionMode");
		config.readInto(numberOfSpeedValues, "numberOfSpeedValues");
		config.readInto(elementsInL, "elementsInL");
//        config.readInto(aDotc0, "aDotc0");

	}
}	

// Make this Control identical to RHS one by operator '='
// Creates the "=" operator for this class
Control& Control::operator=(const Control& rhs)
{
	outflowModelOn = rhs.outflowModelOn;
	lambda = rhs.lambda;
	analyticalSolutionMode = rhs.analyticalSolutionMode;
	// numberOfSpeedValues = numberOfSpeedValues;
	// elementsInL = elementsInL;
    return *this;
} 
