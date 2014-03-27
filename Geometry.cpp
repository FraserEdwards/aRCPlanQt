// aRCPLan: Pipe.cpp
//
// Author: Dr Patrick Leevers
// Modified by: Fraser Edwards

// Pipe.h declares Pipe class
// Pipe.cpp initialises Pipe variables, displays them to user and asks if they'd
// like to change any values

#include <iostream>
using namespace std;

#include "Geometry.h"

		//Initialise array values
		string Geometry::pipeID_lib[5] = {"250mm_SDR11", "250mm_SDR17", "110mm_SDR11", "110mm_SDR17", "63mm_SDR11"};
		double Geometry::diameter_lib[5] = {250.0, 250.0, 110.0, 110.0, 63.0};
		double Geometry::sdr_lib[5] = {11.0, 17.6, 11.0, 17.6, 11.0};
		double Geometry::notchDepth_lib[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
		double Geometry::diameterCreepRatio_lib[5] = {1.0, 1.0, 1.0, 1.0, 1.0};

// Null constructor
Geometry::Geometry()
{	
		pipeID = " ";
		diameter = 0.0;
		sdr = 0.0;
		notchDepth = 0.0;
		diameterCreepRatio = 0.0;
		h=0.0;
		hOverR=0.0;
		radius=0.0;
		crackWidth=0.0;
}	

// Constructor 
Geometry::Geometry(const short recordNumber, ConfigFile config)
{	
	if (recordNumber > 0 and recordNumber < records + 1)
	{
		short index = recordNumber - 1;
		pipeID = pipeID_lib[index];
		diameter = diameter_lib[index];
		sdr = sdr_lib[index];
		notchDepth = notchDepth_lib[index];
		diameterCreepRatio = diameterCreepRatio_lib[index];
	}
	else
	{
		cout << "No pipe geoemtry library record located:  reading data values from config file\n";
		config.readInto(pipeID, "pipeID");
		config.readInto(diameter, "diameter");
		config.readInto(sdr, "sdr");
		config.readInto(notchDepth, "notchDepth");
		config.readInto(diameterCreepRatio, "diameterCreepRatio");
	}
	
	h = diameter/sdr/Constants::kilo; // (m)
	hOverR = 2.0/ (sdr-1);
	radius = h / hOverR;

	crackWidth = diameter / sdr - notchDepth; //(mm, giving kJ/m2 for G; not necessarily equal to h)

}	

// Allows user to modify pipe parameters
void Geometry::inputData()
{
	short itemNumber;
	cout << "** To edit any PIPE parameter, enter its code;  if not, enter 0: ";
	cin >> itemNumber;
	while (itemNumber != 0)
	{
		switch (itemNumber)
		{
			case 1:
			{
				cout << "                                        Name/identifier: ";
				cin >> pipeID;
			}
			break;
			case 2:
			{
				cout << "                             Outside pipe diameter (mm): ";
				cin >> diameter;
			}
			break;
			case 3:
			{
				cout << "                   SDR (Pipe diameter / Wall thickness): ";
				cin >> sdr;
			}
			break;
			case 4:
			{
				cout << "          Depth of internal or external sidegroove (mm): ";
				cin >> notchDepth;
			}
			break;
			case 5:
			{
				cout << "          Relative diameter after residual strain creep: ";
				cin >> diameterCreepRatio;
			}
			break;
			default:
				cout << "Unrecognised code.  Try again:\n";
			break;
		}
		cout << "\nEdit another parameter?  If so, enter reference number;  if not, enter 0: ";
		cin >> itemNumber;
	}
} 

// Make this Pipe identical to RHS one by operator '='
// Creates the "=" operator for this class
Geometry& Geometry::operator=(const Geometry& rhs)
{
	pipeID = rhs.pipeID;
	diameter = rhs.diameter;
	sdr = rhs.sdr;
	notchDepth = rhs.notchDepth;
	diameterCreepRatio = rhs.diameterCreepRatio;
    return *this;
} 

//Displays all pipe parameters to the user with corresponding reference number
void Geometry::outputData()
{
	cout
		<< endl
		<< "PIPE geometry parameters: \n"
		<< "1.                          Pipe name/identifier = " << pipeID << endl
		<< "2.                         Outside pipe diameter = " << diameter << " mm \n"
		<< "3.          SDR (Pipe diameter / Wall thickness) = " << sdr << endl
		<< "4.         Internal or external sidegroove depth = " << notchDepth << " mm \n"
		<< "5. Relative diameter after residual strain creep = " << diameterCreepRatio << endl;
} 