#include <iostream>

using namespace std;

#include "Decompression.h"
#include "Constants.h"

int main()
{

double p0=1.5;
double aDotc0=0.05;

Decomp decomp;
decomp.p1p0(p0, Constants::gamma, aDotc0);

cout << endl << "r=p1/p0: " << decomp.p1p0r << endl;

return 0;
}