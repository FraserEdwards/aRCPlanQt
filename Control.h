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
        static int outflowModelOn_lib[5];
		static double lambda_lib[5];
        static int analyticalSolutionMode_lib[5];
        static int mode_lib[5];
        static int rangenumber_lib[5];
        static int speednumber_lib[5];;
        static int elementsinl_lib[5];
        static double aDotc0_lib[5];
		ConfigFile config;
		
	public:
		// Prototypes
	    Control();													// null constructor
	    Control(const short recordNumber, ConfigFile config); 	// construct a Control definition from the library or a file
        Control& operator=(const Control& rhs);
        int outflowModelOn;
		double lambda;
        int analyticalSolutionMode;
        int mode;
        int rangenumber;
        int elementsinl;
        double aDotc0;
		
};

#endif
