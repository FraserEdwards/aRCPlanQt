#include "Filepath.h"
#include <iostream>
#include <sys/stat.h>

Filepath::Filepath()
{



}

void Filepath::correct()
{

    found = directory.find("aRCPlanQt.app");

    if (found != string::npos)
    {
         directory.resize(found);
    }

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
                return checkstate = 2;
            }

            subfolder = directory + "Log/";

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
                return checkstate = 3;
            }
        }
    }
    else
    {
        return checkstate = 4;
    }

    return checkstate;

}

