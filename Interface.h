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
	void inputData();
	void outputData();

	void line(const string title);
	void line(const string title, const double value);
	void line(const string title, const double value, const string units);
	void oneline(const string title, const double value);
	double input(const string title);
	int inputi(const string title);
	void output(const string title, const double value, const string units);
	void returnsol(Solution solution);
	void returnnsol(Solution solution);
	void iprofile(vector<double> zeta, vector<double> vptra, const int l);

};

#endif