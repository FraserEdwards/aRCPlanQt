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
        cout << "No interface library record located:  reading data values from config file";
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
                 cout << "Unrecognised code.  Try again: ";
			}

		}

		itemNumber = input("Edit another parameter?  If so, enter reference number;  if not, enter 0: ");

	}

}

void Interface::outputData()
{

    cout << "Interface parameters: ";
	output("1.                          Console output level = ", infoLevel, " (0: minimal;  1: moderate;  2:  verbose;  3:  interactive)");
	output("2.                 Plot output for crack profile = ", plotcontrol, " (0: off, 1: On)");
	output("3.          Print (using terminal) crack profile = ", printOpeningProfile, " (0: off, 1: On)");

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



