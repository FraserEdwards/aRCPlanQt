#include "Filepath.h"
#include <iostream>
#include <sys/stat.h>

Filepath::Filepath()
{
//	Null constructor
	extern string location;
	GetCurrentDir(Path, sizeof(Path));
    location = string(Path);
    directory = location;
}

int Filepath::check()
{
    struct stat st;

    cout << directory;

    if(stat(directory.c_str(), &st) == 0)
    {

        cout << "Test!";

        if (st.st_mode & S_IFDIR != 0)
        {

            checkstate = 0;
            cout << "Found!";

        }
        else
        {

            checkstate = 1;
            cout << "Not a Directory!";

        }

    }
    else
    {

        checkstate = 2;
        cout << "Not Found!";

    }

    return checkstate;

}

