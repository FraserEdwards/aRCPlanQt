#include <iostream>
#include <fstream>
using namespace std;

#include "Solution.h"

#ifndef ResultsH
#define ResultsH

class Results
//  
{
	private:

		ofstream results;
		int i;		
		
	public:	
		
		Results();			// Null constructor
		Results(const Results& original);			// Copy constructor
		void placeholder(string title);
		void cell(double value);
		void newline();
		void line(Solution solution);
		void copy(const Results& original);
		void resetSize(short newSize);
        Results& operator=(const Results& rhs);
		~Results();		// Destructor
};

#endif
