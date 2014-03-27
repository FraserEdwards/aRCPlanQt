// aRCPLan: Control.h
//
// Author: Dr Patrick Leevers
// Modified by: Fraser Edwards


#include "ConfigFile.h"

#ifndef ControlH
#define ControlH

// Class declaration section
class Control
{
	private:
		// Variables
		static const short libRecords = 5;
		static short outflowModelOn_lib[5];
		static double lambda_lib[5];
		static short analyticalSolutionMode_lib[5];
		static short numberOfSpeedValues_lib[5];
		static short elementsInL_lib[5];
        static double aDotc0_lib[5];
		ConfigFile config;
		
	public:
		// Prototypes
	    Control();													// null constructor
	    Control(const short recordNumber, ConfigFile config); 	// construct a Control definition from the library or a file
        Control& operator=(const Control& rhs);
		short outflowModelOn;
		double lambda;
		short analyticalSolutionMode;
		short numberOfSpeedValues;
		short elementsInL;
        double aDotc0;
		
};

#endif
