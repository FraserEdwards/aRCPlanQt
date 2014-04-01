#include <cmath>
#include <vector>

#include "Solution.h"

#ifndef _PLOT_H
#define _PLOT_H

class Plot{

private:

	string filename;
	vector<double> x;
	vector<double> y;
	string title;
	string folder;

public:

	Plot();
	void profile(vector<double> x, vector<double> y, string title, string folder, double titlevalue, string xaxis, string yaxis);
	void results(vector<double> x, vector<double> y, string title, string folder, string xaxis, string yaxis);
	void handler(Solution solution);
};

#endif
