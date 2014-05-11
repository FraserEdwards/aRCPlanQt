#include <string>
#include <QApplication>
using namespace std;

#ifdef _WIN32
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif


#ifndef _FILE_H
#define _FILE_H

class File
{
private:
	char Path[256];	
    int checkstate;
    string tempdir;
    string subfolder;
    int found;
public:
    File();
    void correct(); 	//Null constructor
    int check();
    int loadcheck(string name);
    string directory;
};

#endif
