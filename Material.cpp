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
        string Material::matID_lib[5] = {"Soft PE80", "Generic PE100", "Soft PE100", "Generic PE", "Generic PE"};
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

// Make this material identical to RHS one by operator '='
// Creates the "=" operator for this class
Material& Material::operator=(const Material& rhs)
{
	matID = rhs.matID;
	density = rhs.density;
	eDyn0degC = rhs.eDyn0degC;
	dEdyndT = rhs.dEdyndT;
    dynamicModulus = rhs.dynamicModulus;
	creepModulus = rhs.creepModulus;
	poisson = rhs.poisson;
    return *this;
} 

