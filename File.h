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

class File
{
private:
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
    void write(Parameters temp);
    void writeline(string title, double value, ofstream &out, int format);
    void writeline(string title, string value, ofstream &out, int format);
    void writeline(string title, ofstream &out, int format);
};

#endif
