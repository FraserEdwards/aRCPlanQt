#include "File.h"
#include <iostream>
#include <sys/stat.h>

File::File()
{



}

void File::correct()
{

    found = directory.find("aRCPlanQt.app");

    if (found != string::npos)
    {
         directory.resize(found);
    }

}

int File::check()
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

int File::loadcheck(string name)
{

    struct stat st;

    if(stat((directory + name).c_str(), &st) == 0)
    {
        return 0;
    }

    return 1;
}

int File::casehandler(Parameters temp, string filename)
{
    if(filename.find(".txt",0)<100)
    {
        writepartxt(temp, filename);
        return 0;
    }
    else
    {
        return 1;
    }
}

void File::writeresults()
{
    ofstream out;
    extern File file;
    extern Solution solution;

    filename = "Results.csv";

    out.open((file.directory + "Results/" + filename).c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);

    out << "Normalised Crack Speed,Decomp. factor,Speed factor,Support factor,Outflow length,Flaring,Irwin Corten force,Crack driving force,Normalised total,\n";

    for(i=1; i<solution.soln+1;i++)
    {

        out << solution.aDotc0[i] << "," << solution.decompression[i] << "," << solution.alpha[i] << ","
                << solution.m[i] << "," << solution.outflowLength[i] << ", ," << solution.g0[i] << ","
                << solution.gG0[i] << "," << solution.gTotal[i] << "\n";

    }

    out.close();

}

void File::writepartxt(Parameters temp, string filename)
{

    ofstream out;

    out.open((directory + filename).c_str());

    writeline("Input Data", out,1);

    writeline("Material Data", out, 1);

    writeline("matID = ", temp.matID, out, 0);
    writeline("density = ", temp.density, out, 0);
    writeline("eDyn0degC = ", temp.eDyn0degC, out, 0);
    writeline("dEdyndT = ", temp.dEdyndT, out, 0);
    writeline("creepModulus = ", temp.creepModulus, out, 0);
    writeline("poisson = ", temp.poisson, out, 1);

    writeline("Pipe Data", out,1);

    writeline("pipeID = ", temp.pipeID, out, 0);
    writeline("diameter = ", temp.diameter, out, 0);
    writeline("sdr = ", temp.sdr, out, 0);
    writeline("notchDepth = ", temp.notchDepth, out, 0);
    writeline("diameterCreepRatio = ", temp.diameterCreepRatio, out, 1);

    writeline("Test Setup Data", out, 1);

    writeline("fullScale = ", temp.fullScale, out, 0);
    writeline("tempDegC = ", temp.tempDegC, out, 0);
    writeline("p0bar = ", temp.p0bar, out, 0);
    writeline("isBackfilled = ", temp.isBackfilled, out, 0);
    writeline("backfillDepth = ", temp.backfillDepth, out, 0);
    writeline("backfillDensity = ", temp.backfillDensity, out, 0);
    writeline("solidInsidePipe = ", temp.solidInsidePipe, out, 0);
    writeline("waterInsidePipe = ", temp.waterInsidePipe, out, 1);

    writeline("Program Control Data", out, 1);

    writeline("outflowModelOn = ", temp.outflowModelOn, out, 0);
    writeline("lambda = ", temp.lambda, out, 0);
    writeline("solutionmethod = ", temp.solutionmethod, out, 0);
    writeline("numberOfSpeedValues = ", temp.rangenumber, out, 0);
    writeline("elementsInL = ", temp.elementsinl, out, 0);

    out.close();

}

void writeparcsv(Parameters temp, string filename)
{



}

void File::writeline(string title, double value, ofstream &out, int format)
{

    out << "\t" << title << value << endl;
    if(format == 1)
    {
        out << endl;
    }
}

void File::writeline(string title, string value, ofstream &out, int format)
{

    out << "\t" << title << value << endl;
    if(format == 1)
    {
        out << endl;
    }


}

void File::writeline(string title, ofstream &out, int format)
{

    out << title << endl;
    if(format == 1)
    {
        out << endl;
    }

}


