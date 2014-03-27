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
		line("No interface library record located:  reading data values from config file");
		config.readInto(infoLevel, "infoLevel");
		config.readInto(plotcontrol, "plotcontrol");
		config.readInto(printOpeningProfile, "printOpeningProfile");
	}

//	outputData();
//	inputData();
}

void Interface::inputData()
{

	itemNumber = input("To edit any Interface parameter enter its code;  if not, enter 0: ");
	while(itemNumber != 0)
	{

		switch(itemNumber)
		{

			case 1:
			{

				infoLevel = input("Console output level:");

			}
			break;
			case 2:
			{

				plotcontrol = input("Plot output for crack profile: ");
				if(plotcontrol > 1) plotcontrol = 1;
			}
			break;
			case 3:
			{
				printOpeningProfile = input("Print (using terminal) crack profile: ");
				if(printOpeningProfile > 1) printOpeningProfile =1;
			}
			break;
			default:
			{
				line("Unrecognised code.  Try again: ");
			}

		}

		itemNumber = input("Edit another parameter?  If so, enter reference number;  if not, enter 0: ");

	}

}

void Interface::outputData()
{

	line("Interface parameters: ");
	output("1.                          Console output level = ", infoLevel, " (0: minimal;  1: moderate;  2:  verbose;  3:  interactive)");
	output("2.                 Plot output for crack profile = ", plotcontrol, " (0: off, 1: On)");
	output("3.          Print (using terminal) crack profile = ", printOpeningProfile, " (0: off, 1: On)");

}



void Interface::line(const string title)
{

	cout << endl << title << endl;

}

void Interface::line(const string title, const double value)
{

	cout << endl << title << value << endl;

}

void Interface::line(const string title, const double value, const string units)
{

	cout << endl << title << value << units << endl;

}

void Interface::oneline(const string title, const double value)
{

	cout << title << value;

}

double Interface::input(const string title)
{

	cout << endl << title << endl;
	cin >> value;

	return value;

}

int Interface::inputi(const string title)
{

	cout << endl << title << endl;
	cin >> value;

	return value;

}

void Interface::output(const string title, const double value, const string units="	")
{

	cout << setw(20) << left << title << setw(6) << setprecision(4) << value << setw(4) << units << endl
	<< right;

}

void Interface::iprofile(const vector<double> zeta, const vector<double> vptra, const int l)
{

	cout << endl << "      zeta      value" << endl;
	cout << setw(9) << 0.0 << "\t" << 0.0 << endl;

	for (short i=0; i<l; i++)
	{
		cout << setw(9) << setprecision(4) << zeta[i] << "\t"<< vptra[i] << endl;	
	}
	cout << endl;
}

void Interface::returnsol(const Solution solution)
{

	output("aDotc0:", solution.aDotc0[solution.soln]);
	output("Decompression:", solution.decompression[solution.soln]);
	output("Alpha:", solution.alpha[solution.soln]);
	output("m:", solution.m[solution.soln]);
	output("Outflow Length:", solution.outflowLength[solution.soln]);
	output("DeltaDstar*100:", solution.deltaDStar[solution.soln]*100);
	output("gS1/g0:", solution.gS1[solution.soln] / solution.g0[solution.soln]); 
	output("gUE/g0:", solution.gUE[solution.soln] / solution.g0[solution.soln]);
	output("gSb/g0:", solution.gSb[solution.soln] / solution.g0[solution.soln]);
	output("gKb/g0:", solution.gKb[solution.soln] / solution.g0[solution.soln]);
	output("gC0:", solution.gG0[solution.soln], "*");            
	output("gTotal:", solution.gTotal[solution.soln], "kJ/m^2");

}

void Interface::returnnsol(Solution solution)
{
	output("aDotc0:", solution.aDotc0[solution.soln]);
	output("Decompression:", solution.decompression[solution.soln]);
	output("Alpha:", solution.alpha[solution.soln]);
	output("m:", solution.m[solution.soln]);
	line("No crack opening.");

}
