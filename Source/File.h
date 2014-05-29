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
#include "FracMech.h"

class File : public FracMech, public Creep, public Backfill, public BeamModel
{
private:

    ofstream out;

    int i;
    int j;
    int checkstate;
    string tempdir;
    string subfolder;
    string filename;
    int found;
    int measurement;

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
    void writelinecsv(string title, double value, ofstream &out);
    void writelinecsv(string title, string value, ofstream &out);
    void writelinecsv(string title, ofstream &out);
    void writelinetxt(string title, double value, ofstream &out, int format);
    void writelinetxt(string title, string value, ofstream &out, int format);
    void writelinetxt(string title, ofstream &out, int format);
    void logprepare(Parameters temp);
    void writeheaders(string temp);
    void collect(FracMech fracmech);
    void collect(Creep creep);
    void collect(Backfill backfill);
    void collect(BeamModel *beamModel, int newline);
    void writelogline(int newline);
};

#endif
