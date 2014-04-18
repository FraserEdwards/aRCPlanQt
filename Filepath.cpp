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

    if(stat(directory.c_str(), &st) == 0)
    {

        if (st.st_mode & S_IFDIR != 0)
        {
            subfolder = directory + "Results/";

            if(stat(subfolder.c_str(), &st) == 0)
            {
                if (st.st_mode &S_IFDIR != 0)
                {
                    checkstate = 0;
                }
            }
            else
            {
                mkdir(subfolder.c_str(), 0777);
                cout << subfolder;
                return checkstate = 1;
            }

            subfolder = directory + "Profiles/";

            if(stat(subfolder.c_str(), &st) == 0)
            {
                if (st.st_mode &S_IFDIR != 0)
                {
                    checkstate = 0;
                }
            }
            else
            {
                mkdir(subfolder.c_str(), 0777);
                cout << subfolder;
                return checkstate = 2;
            }
        }
    }
    else
    {
        return checkstate = 3;
    }

    return checkstate;

}

