// aRCPLan: TestSetup.h
//
// Author: Dr Patrick Leevers
// Modified by: Fraser Edwards

#include "ConfigFile.h"

#ifndef TestSetupH
#define TestSetupH

// Class declaration section
class TestSetup
{
	private:
		// Variables
		static const short records = 5;
		static string methodID_lib[5];
		static short fullScale_lib[5];
		static double tempDegC_lib[5];
		static double p0bar_lib[5];
        static int isBackfilled_lib[5];
		static double backfillDepth_lib[5];
		static double backfillDensity_lib[5];
		static double solidInsidePipe_lib[5];
		static double waterInsidePipe_lib[5];
		ConfigFile config;
		
	public:
		// Prototypes
	    TestSetup();												// null constructor
	    TestSetup(const short matLibNumber, ConfigFile config); 	// construct a TestSetup definition from the library or a file
		TestSetup& operator=(const TestSetup& rhs);
		string methodID;
		short fullScale;
		double tempDegC;
		double p0bar;
        int isBackfilled;
		double backfillDepth;
		double backfillDensity;
		double solidInsidePipe;
		double waterInsidePipe;
};

#endif
