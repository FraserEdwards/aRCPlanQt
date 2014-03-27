// aRCPLan: Material.h
//
// Author: Dr Patrick Leevers
// Modified by: Fraser Edwards

#include "ConfigFile.h"

#ifndef MaterialH
#define MaterialH

// Class declaration section
class Material
{
	private:
		// Variables
		static const short records = 5;
		static string matID_lib[5];// Material::matName_lib = {"Generic PE80", "Generic PE100", "Soft PE80", "Soft PE100", "Generic PE"};
		static double density_lib[5];// Material::density_lib = {938.0, 960.0, 938.0, 960.0, 950.0};
		static double eDyn0degC_lib[5];// Material::eDyn0degC_lib = {2.62, 3.17, 1.31, 1.585, 1.5};
		static double dEdyndT_lib[5];// Material::dEdyndT_lib = {-0.037, -0.0427, -0.0185, -0.02135, -0.02};
		static double creepModulus_lib[5];// Material::eCreep_lib = {0.3, 0.3, 0.3, 0.3, 0.3};
		static double poisson_lib[5];// Material::poisson_lib = {0.38, 0.38, 0.38, 0.38, 0.38};
		ConfigFile config;
		
	public:
		// Prototypes
	    Material();													// null constructor
	    Material(const short recordNumber, ConfigFile config); 	// construct a material definition from the library or a file
		string matID;
		double density;
		double eDyn0degC;
		double dEdyndT;
		double dynamicModulus;
		double creepModulus;
		double poisson;
		double creepModulusRatio;
		Material& operator=(const Material& rhs);
};
#endif
