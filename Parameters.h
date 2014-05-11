#include "TestSetup.h"
#include "Control.h"
#include "Material.h"
#include "Geometry.h"

#include <iostream>
#include <fstream>
using namespace std;


#ifndef _PARAMETERS_H
#define _PARAMETERS_H

class Parameters : public Control, public TestSetup, public Material, public Geometry
{

private:

	ConfigFile config;
	Geometry geometry;
	Material material;
	TestSetup testSetup;
    Control control;
    string filename;

	
public:

    Parameters() : Control(), TestSetup(), Material(), Geometry() {}
	void collect(ConfigFile config);
	void copy(Material material, Geometry geometry, TestSetup testSetup, Control control);
	void conditionToTemperature();	
    void write();

} ;

#endif
