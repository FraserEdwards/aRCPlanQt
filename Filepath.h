#include <string>
using namespace std;

#ifdef _WIN32
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif


#ifndef _FILEPATH_H
#define _FILEPATH_H

class Filepath
{
private:
	char Path[256];	
	
public:
	Filepath(); 	//Null constructor
};

#endif