#pragma once
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
#include "Log.h"

class File : public FracMech, public Creep, public Backfill, public BeamModel
{
private:

    ofstream out;

    int i;
    int checkstate;
    string tempdir;
    string subfolder;
    string filename;
    int found;

public:

    double aDotc0;

    File();
    void initialise();
    void correct(); 	//Null constructor
    int check();
    int loadcheck(string name);
    string directory;
    int casehandler(Parameters temp, string filename);
    void writeparcsv(Parameters temp, string filename);
    void writepartxt(Parameters temp, string filename);
    void writeresults();
    void writelinedoublecsv(string title, double value, ofstream &out);
    void writelinestringcsv(string title, string value, ofstream &out);
    void writelinestringcsv(string title, ofstream &out);
    void writelinetxt(string title, double value, ofstream &out, int format);
    void writelinetxt(string title, string value, ofstream &out, int format);
    void writelinetxt(string title, ofstream &out, int format);
    void logprepare(Parameters temp);
    void writeheaders(string temp);
    void collect(FracMech fracmech);
    void collect(Creep creep);
    void collect(Backfill backfill);
    void collect(BeamModel *beamModel);
    void writelogline();
};

#endif
