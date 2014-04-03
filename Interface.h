#include <cstdlib>
#include <string>
using namespace std;

#include "Solution.h"
#include "FDprofile.h"
#include "ConfigFile.h"

#ifndef _INTERFACE_H
#define _INTERFACE_H

class Interface{

private:

	static short infoLevel_lib[5];
	static short plotcontrol_lib[5];
	static short printOpeningProfile_lib[5];

	int itemNumber;
	short index;
	short records;
	string title;
	string units;
	double value;
	ConfigFile config;

public:

	short infoLevel;
	short plotcontrol;
	short printOpeningProfile;
	Interface();
	Interface(const short recordNumber, ConfigFile config);

};

#endif
