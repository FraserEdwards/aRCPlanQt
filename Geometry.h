// aRCPLan: Pipe.h
//
// Author: Dr Patrick Leevers
// Modified by: Fraser Edwards

#include "ConfigFile.h"
#include "Constants.h"

#ifndef GeometryH
#define GeometryH

//class declaration section
class Geometry
{
	private:
		//variables
		static const short records = 5;
		static string pipeID_lib[5];
		static double diameter_lib[5];
		static double sdr_lib[5];
		static double notchDepth_lib[5];
		static double diameterCreepRatio_lib[5];
		ConfigFile config;
		
	public:
		//prototypes
	    Geometry();								// null constructor
	    Geometry(const short recordNumber, ConfigFile config); 	// construct a Pipe definition from the library or a file
	    void inputData();
	    void outputData();
		Geometry& operator=(const Geometry& rhs);
		string pipeID;
		double diameter;
		double sdr;
		double notchDepth;
		double diameterCreepRatio;
		double h;
		double crackWidth;
		double hOverR;
		double radius;
};

#endif
