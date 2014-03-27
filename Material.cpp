// aRCPLan: Material.cpp
//
// Author: Dr Patrick Leevers
// Modified by: Fraser Edwards

// Material.h declares Material class
// Material.cpp initialises Material variables, displays them to user and asks if they'd
// like to change any values


#include <iostream>
using namespace std;

#include "Material.h"

		//Initialise array values
		string Material::matID_lib[5] = {"Generic PE80", "Generic PE100", "Soft PE80", "Soft PE100", "Generic PE"};
		double Material::density_lib[5] = {938.0, 960.0, 938.0, 960.0, 950.0};
		double Material::eDyn0degC_lib[5] = {2.62, 3.17, 1.31, 1.585, 1.5};
		double Material::dEdyndT_lib[5] = {-0.037, -0.0427, -0.0185, -0.02135, -0.02};
		double Material::creepModulus_lib[5] = {0.3, 0.3, 0.3, 0.3, 0.3};
		double Material::poisson_lib[5] = {0.38, 0.38, 0.38, 0.38, 0.38};

// Null constructor		
Material::Material()
{	
		matID = " ";
		density = 0.0;
		eDyn0degC = 0.0;
		dEdyndT = 0.0;
		creepModulus = 0.0;
		poisson = 0.0;
}	

// Constructor for a material at specified test temperature, using library data
Material::Material(const short recordNumber, ConfigFile config)
{	
	if (recordNumber > 0 and recordNumber < records + 1)
	{
		short index = recordNumber - 1;
		matID = matID_lib[index];
		density = density_lib[index];
		eDyn0degC = eDyn0degC_lib[index];
		dEdyndT = dEdyndT_lib[index];
		creepModulus = creepModulus_lib[index];
		poisson = poisson_lib[index];
	}
	else
	{
		cout << "No material library record located:  reading data values from config file\n";
		config.readInto(matID, "matID" );
		config.readInto(density, "density" );
		config.readInto(eDyn0degC, "eDyn0degC" );
		config.readInto(dEdyndT, "dEdyndT" );
		config.readInto(creepModulus, "creepModulus" );
		config.readInto(poisson, "poisson" );
	}
}	

// Allows user to modif test parameters
void Material::inputData()
{
	short itemNumber;
	cout << "** To edit any MATERIAL parameter, enter its code;  if not, enter 0: ";
	cin >> itemNumber;
	while (itemNumber != 0)
	{
		switch (itemNumber)
		{
			case 1:
			{
				cout << "                                       Material name/ID: ";
				cin >> matID;
			}
			break;
			case 2:
			{
				cout << "                                        Density (kg/m3): ";
				cin >> density;
			}
			break;
			case 3:
			{
				cout << "                       Dynamic modulus at 0 deg C (GPa): ";
				cin >> eDyn0degC;
			}
			break;
			case 4:
			{
				cout << " Increase in dynamic modulus per deg C (GPa, -ve value): ";
				cin >> dEdyndT;
			}
			break;
			case 5:
			{
				cout << "                Creep modulus at room temperature (GPa): ";
				cin >> creepModulus;
			}
			break;
			case 6:
			{
				cout << "                                  Dynamic poisson ratio: ";
				cin >> poisson;
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


// Make this material identical to RHS one by operator '='
// Creates the "=" operator for this class
Material& Material::operator=(const Material& rhs)
{
	matID = rhs.matID;
	density = rhs.density;
	eDyn0degC = rhs.eDyn0degC;
	dEdyndT = rhs.dEdyndT;
	creepModulus = rhs.creepModulus;
	poisson = rhs.poisson;
    return *this;
} 

// Displays all materail parameters to the user with corresponding reference number
void Material::outputData()
{
		cout << endl
		<< "MATERIAL parameters: \n"
		<< "1.                                       Name/ID = " << matID << "\n"
		<< "2.                                       Density = " << density << " kg/m^3 \n"
		<< "3.                    Dynamic modulus at 0 deg C = " << eDyn0degC << " GPa \n"
		<< "4.         Increase in dynamic modulus per deg C = " << dEdyndT << " GPa/K \n"
		<< "5.             Creep modulus at room temperature = " << creepModulus << " GPa \n"
		<< "6.                         Dynamic Poisson ratio = " << poisson << endl;
} 