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

// Null constructor
Control::Control()
{	
		outflowModelOn = 0;
		lambda = 0.0;
		analyticalSolutionMode = 0;
		numberOfSpeedValues = 0;
		elementsInL = 0;
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
	}
	else
	{
		cout << "No control library record located:  reading data values from config file\n";
		config.readInto(outflowModelOn, "outflowModelOn");
		config.readInto(lambda, "lambda");
		config.readInto(analyticalSolutionMode, "analyticalSolutionMode");
		config.readInto(numberOfSpeedValues, "numberOfSpeedValues");
		config.readInto(elementsInL, "elementsInL");

	}
}	

//Allows user to modify control parameters
void Control::inputData()
{
	short itemNumber;
	cout << "** To edit any Control parameter enter its code;  if not, enter 0: ";
	cin >> itemNumber;
	while (itemNumber != 0)
	{
		switch (itemNumber)
		{
			case 1:
			{
				cout << "              Outflow length fixed (0) or automatic (1): ";
				cin >> outflowModelOn;
			}
			break;
			case 2:
			{
				cout << "                Outflow length (mean diameters, e.g. 3): ";
				cin >> lambda;
			}
			break;
			case 3:
			{
				cout << "Solution method  (0: FD;  1: analytical): ";
				cin >> analyticalSolutionMode;
			}
			break;
			case 4:
			{
				cout << "                  Number of crack speed values required: ";
				cin >> numberOfSpeedValues;
				if (numberOfSpeedValues < 1)
					numberOfSpeedValues = 1;
			}
			break;
			case 5:
			{
				cout << "         Number of elements per outflow length (min. 6): ";
				cin >> elementsInL;
				if (elementsInL < 6)
					elementsInL = 6;
			}
			break;
			default:
				cout << "Unrecognised code.  Try again:\n";
			break;
		}
		cout << "\nEdit another parameter?  If so, enter reference number;  if not, enter 0: ";
		cin >> itemNumber;	
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

// Displays all control parameters to the user with corresponding reference number
void Control::outputData()
{

	cout
		<< endl
		<< "Control parameters: \n"
		<< "1.     Outflow length fixed (0) or automatic (1) = " << outflowModelOn << endl
		<< "2. Fixed/initial outflow length (mean diameters) = " << lambda << endl
		<< "3.                               Solution method = " << analyticalSolutionMode << " (0: finite difference;  1: analytical)" << endl
		<< "4.                  Number of crack speed values = " << numberOfSpeedValues << " (e.g. 10, 20;  1 or fewer gives 'single shot' mode" << endl
		<< "5.       Number of FD elements in outflow length = " << elementsInL << endl;
} 