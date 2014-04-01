#include <iostream>
#include <iomanip>
#include <cmath>

#include "Interface.h"
#include "FDprofile.h"

	// Initialise array values
	short Interface::plotcontrol_lib[5]={1,1,1,1,1};
	short Interface::infoLevel_lib[5] = {1, 2, 3, 1, 1};
	short Interface::printOpeningProfile_lib[5]={1,0,1,0,1};


Interface::Interface(){

	title="		";
	value=0.0;
	units="		";
	infoLevel=0.0;
	plotcontrol=0.0;
	printOpeningProfile=0.0;

}

Interface::Interface(const short recordNumber, ConfigFile config)
{
	title="		";
	value=0.0;
	units="		";
	records=5;

	if(recordNumber > 0 and recordNumber < records +1)
	{
		index = recordNumber-1;
		infoLevel = infoLevel_lib[index];
		plotcontrol = plotcontrol_lib[index]; 
		printOpeningProfile = printOpeningProfile_lib[index];
	}
	else
	{
//		line("No interface library record located:  reading data values from config file");
		config.readInto(infoLevel, "infoLevel");
		config.readInto(plotcontrol, "plotcontrol");
		config.readInto(printOpeningProfile, "printOpeningProfile");
	}

}








