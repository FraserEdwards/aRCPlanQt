// aRCPLan: TestSetup.cpp
//
// Author: Dr Patrick Leevers
// Modified by: Fraser Edwards

// TestSetup.h declares TestSetup class
// TestSetup.cpp initialises TestSetup variables, displays them to user and asks if they'd
// like to change any values


#include <iostream>
using namespace std;

#include "TestSetup.h"

		// Initialise array values
		string TestSetup::methodID_lib[5] = {"S4, 0degC, 1.5 bar", "FS, 0degC, 5 bar, no backfill", "S4, 0degC, 5 bar", "FS, 0degC, 5 bar, backfilled", "S4, 0degC, 5 bar, 25% water"};
		short TestSetup::fullScale_lib[5] = {0, 1, 0, 1, 0};
		double TestSetup::tempDegC_lib[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
		double TestSetup::p0bar_lib[5] = {1.5, 5.0, 5.0, 5.0, 5.0};
        int TestSetup::isBackfilled_lib[5] = {0, 0, 0, 1, 0};
		double TestSetup::backfillDepth_lib[5] = {0.0, 0.0, 0.0, 100.0, 0.0};
		double TestSetup::backfillDensity_lib[5] = {0.0, 0.0, 0.0, 2200.0, 0.0};
		double TestSetup::solidInsidePipe_lib[5] = {0.25, 0.0, 0.25, 0.0, 0.25};
		double TestSetup::waterInsidePipe_lib[5] = {0.0, 0.0, 0.0, 0.0, 0.25};

// Null constructor
TestSetup::TestSetup()
{
		methodID = " ";
		fullScale = 0;
		tempDegC = 0.0;
		p0bar = 0.0;
		isBackfilled = 0;
		backfillDepth = 0.0;
		backfillDensity = 0.0;
		solidInsidePipe = 0.0;
        waterInsidePipe = 0.0;
}

// Constructor for a TestSetup at specified test temperature, using library data
TestSetup::TestSetup(const short recordNumber, ConfigFile config)
{

	if (recordNumber > 0 and recordNumber < records + 1)
	{
		short index = recordNumber - 1;
		methodID = methodID_lib[index];
		fullScale = fullScale_lib[index];
		tempDegC = tempDegC_lib[index];
		p0bar = p0bar_lib[index];
		isBackfilled = isBackfilled_lib[index];
		backfillDepth = backfillDepth_lib[index];
		backfillDensity = backfillDensity_lib[index];
		solidInsidePipe = solidInsidePipe_lib[index];
		waterInsidePipe = waterInsidePipe_lib[index];
	}
	else
	{
		cout << "No test setup library record located:  reading data values from config file\n";
		config.readInto(methodID, "methodID");
		config.readInto(fullScale, "fullScale");
		config.readInto(tempDegC, "tempDegC");
		config.readInto(p0bar, "p0bar");
		config.readInto(isBackfilled, "isBackfilled");
		config.readInto(backfillDepth, "backfillDepth");
		config.readInto(backfillDensity, "backfillDensity");
		config.readInto(solidInsidePipe, "solidInsidePipe");
		config.readInto(waterInsidePipe, "waterInsidePipe");

		if((tempDegC-0.0) < 0.001)
		{
			tempDegC=0.0;
		} 

	}
}

// Make this TestSetup identical to RHS one by operator '='
// Creates the "=" operator for this class
TestSetup& TestSetup::operator=(const TestSetup& rhs)
{
	methodID = rhs.methodID;
	fullScale = rhs.fullScale;
	tempDegC = rhs.tempDegC;
	p0bar = rhs.p0bar;
    isBackfilled = rhs.isBackfilled;
	backfillDepth = rhs.backfillDepth;
	backfillDensity = rhs.backfillDensity;
	return *this;
}

