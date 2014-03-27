#include<iostream>

using namespace std;

#include "ConfigFile.h"

int main ()
{
		//declare variables
		string matID;
		double density;
		double eDyn0degC;
		double dEdyndT;
		double dynamicModulus;
		double creepModulus;
		double poisson;
		double creepModulusRatio;

		
		ConfigFile config("caseInputData.txt");


			cout << "No material library record located:  reading data values from config file\n";
			config.readInto(matID, "matID" );
			config.readInto(density, "density" );
			config.readInto(eDyn0degC, "eDyn0degC" );
			config.readInto(dEdyndT, "dEdyndT" );
			config.readInto(creepModulus, "creepModulus" );
			config.readInto(poisson, "poisson" );


			cout << endl
					<< "MATERIAL parameters: \n"
					<< "1.                                       Name/ID = " << matID << "\n"
					<< "2.                                       Density = " << density << " kg/m^3 \n"
					<< "3.                    Dynamic modulus at 0 deg C = " << eDyn0degC << " GPa \n"
					<< "4.         Increase in dynamic modulus per deg C = " << dEdyndT << " GPa/K \n"
					<< "5.             Creep modulus at room temperature = " << creepModulus << " GPa \n"
					<< "6.                         Dynamic Poisson ratio = " << poisson << endl;

	return 0;
}
