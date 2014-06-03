//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

#ifndef _FILE_H
#define _FILE_H

#ifdef _WIN32
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

#include <string>
#include <QApplication>
#include <fstream>
using namespace std;

#include "Parameters.h"
#include "Solution.h"
#include "FracMech.h"
#include "OutflowProcess.h"

class File : public FracMech, public Creep, public Backfill, public BeamModel, public OutflowProcess
{
private:

    ofstream out;

    int i;
    int j;
    int check_state;
    string temp_dir;
    string subfolder;
    string file_name;
    int found;
    int log_number;

public:

    string directory;
    double adotc0;

    //Null constructor
    File();

    //Clears all values in file
    void initialise();

    //Resizes directory, removing aRCPlan.app to find overall directory of program
    void correct();

    //Check for existence of folder required for storing files
    int check();

    //Checks if file exists
    int loadcheck(string name);

    //Handles parameters, sending them to write function if file is found
    int casehandler(Parameters temp, string filename);

    //Writes parameters to csv file with appropriate formatting
    void writeparcsv(Parameters temp, string filename);

    //Write parameters to txt file with appropriate formatting
    void writepartxt(Parameters temp, string filename);

    //Reads from global solution object and writes to a csv file
    void writeresults();

    //Writes a single line to a csv file
    void writelinecsv(string title, double value, ofstream &out);
    void writelinecsv(string title, string value, ofstream &out);
    void writelinecsv(string title, ofstream &out);

    //Writes a single line to a txt file
    void writelinetxt(string title, double value, ofstream &out, int format);
    void writelinetxt(string title, string value, ofstream &out, int format);
    void writelinetxt(string title, ofstream &out, int format);

    //Handles log file, writing parameters and headers for remainder of logs
    void logprepare(Parameters temp);

    //Writes headers for log file
    void writeheaders(string temp);

    //Update log file before writing a line
    void collect(FracMech fracmech);
    void collect(Creep creep);
    void collect(Backfill backfill);
    void collect(BeamModel *beamModel, int newline);
    void collect(OutflowProcess *outflow, int newline);

    //Writes a single line to the log file with current log values
    void writelogline(int newline);
};

#endif
