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

class File
{
private:
    int i;
	char Path[256];	
    int checkstate;
    string tempdir;
    string subfolder;
    string filename;
    int found;
public:
    File();
    void correct(); 	//Null constructor
    int check();
    int loadcheck(string name);
    string directory;
    int casehandler(Parameters temp, string filename);
    void writeparcsv(Parameters temp, string filename);
    void writepartxt(Parameters temp, string filename);
    void writeresults();
    void writeline(string title, double value, ofstream &out, int format);
    void writeline(string title, string value, ofstream &out, int format);
    void writeline(string title, ofstream &out, int format);
};

#endif
