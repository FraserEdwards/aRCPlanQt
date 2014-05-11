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
    ofstream out;
public:
    File();
    void correct(); 	//Null constructor
    int check();
    int loadcheck(string name);
    void write(Parameters parameters);
    void line(string title, double value);
    string directory;
};

#endif
