#include "Filepath.h"
#include <iostream>

Filepath::Filepath()
{
//	Null constructor

	GetCurrentDir(Path, sizeof(Path));
    location=string(Path);
}

