#include "Filepath.h"

Filepath::Filepath()
{
//	Null constructor
	extern string location;
	GetCurrentDir(Path, sizeof(Path));
	location=string(Path);
}

