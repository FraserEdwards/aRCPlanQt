// aRCPLan: Constants.cpp
//
// Author: Dr Patrick Leevers
// Modified by: Fraser Edwards

// Constants.cpp declares and initialises constants within 
// the Constants class

#include "Constants.h"

//Initialise constants
const double Constants::pi = 3.141592653;
const double Constants::bar = 1.0e5;
const double Constants::piSqr = pi * pi;
const double Constants::gamma = 1.4;			// Specific heat ratio
const double Constants::pAtm = 1.0;				// bar
const double Constants::vSonic = 330.0;			// Speed of sound in air
const double Constants::c1 = 0.25 / pi + 4.0 / piSqr / pi - 32.0 / piSqr / piSqr / pi;
const double Constants::c2 = pi / 6.0 + 0.5 / pi;
const double Constants::c3 = 4.0 * c2 / c1;
const double Constants::c4 = 2.0 * pi / 3.0 / c1;
const double Constants::c5 = 8.0 / pi / c1;
const double Constants::c10 = (0.05 + 1.0 / 252.0);
const double Constants::c11 = 11.0 / 60.0;
const double Constants::kilo = 1.0e3;
const double Constants::mega = 1.0e6;
const double Constants::giga = 1.0e9;
