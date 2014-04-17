#include "Filepath.h"
#include <iostream>

Filepath::Filepath()
{
//	Null constructor
	extern string location;
	GetCurrentDir(Path, sizeof(Path));
    location = string(Path);
    directory = location;
}

