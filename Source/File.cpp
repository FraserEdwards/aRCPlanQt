//     aRCPLan
//     Copyright (c) [2014] [Fraser Edwards][Dr Patrick Leevers]
//     aRCPlan may be freely distributed under the MIT license.
//     For the underlying model, see http://www.sciencedirect.com/science/article/pii/S0013794412003530

//     Class taking care of all file writing duties (Results, cracks and caseInputData.txt)
//     Also contains the log used to record values during run-time

#include <iostream>
#include <sys/stat.h>
using namespace std;

#include "File.h"

//Null constructor
File::File()
{
   initialise();
}

//Clears all variables within the file class
void File::initialise()
{
    adotc0 = 0.0;
    g0 = 0.0;
    diameter_res0 = 0.0;

    dStarMinus1 = 0.0;
    dStarMinus2 = 0.0;
    baffleLeakageArea = 0.0;
    fdArraySize = 0;
    decompression = 0.0;

    zetaClosure = 0.0;
    printOpeningProfile = 0;

    l = 0;
    maxIterations = 0;
    hOverR = 0.0;
    lambdaLast = 0.0;
    zetaBackfilledLast = 0.0;
    notConverged = 0;
    iterations = 0;
    noCrackOpening = 0;
    wStar2 = 0.0;
    wStarMax = 0.0;
    wStar2dash = 0.0;
    wStar2dash2 = 0.0;
    integral_wStar2 = 0.0;
    zetaBackfillEject = 0.0;
    p1p0r = 0.0;
    dynamicShearModulus = 0.0;
    nodeResolution = 0.0;
    v0 = 0.0;
    factor = 0.0;
    p1bar = 0.0;
    vStarRes = 0.0;
    nodeAtClosure = 0;
    aDotOverCL = 0.0;
    aDotCLfactor = 0.0;
    aDotCLfactor_backfilled = 0.0;
    lambdaPow4 = 0;
    sdrMinus1 = 0.0;
    sdrMinus2 = 0.0;
    zetaBackfilled = 0.0;
    outflowLength = 0.0;
    v00 = 0.0;
    error = 0.0;
    availableInternalVolume = 0.0;
    vStarDashBackfillEject = 0.0;

    m[0] = 0.0;
    m[1] = 0.0;
    alpha[0] = 0.0;
    alpha[1] = 0.0;

    pStarUnchoke = 0.0;
    xUnch = 0.0;
    pHalfStar = 0.0;
    pStar = 0.0;
    tStar = 0.0;
    tStarUnchoke = 0.0;
    simpsonIntegral = 0.0;
    unchoked = 0;
    tStarOutflow2 = 0.0;

    writelogline(1);

}

//Reduces directory path to where "aRCPlanQt.app" is found
void File::correct()
{

    found = directory.find("aRCPlanQt.app");

    if (found != string::npos)
    {
         directory.resize(found);
    }

}

//Checks if folders can be found for storing results files
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

//Checks if file exists
int File::loadcheck(string name)
{

    struct stat st;

    if(stat((directory + name).c_str(), &st) == 0)
    {
        return 0;
    }

    return 1;
}

//Provides handler for writing caseInputData.txt file
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

//Writes results file by accessing global object solution
void File::writeresults()
{
    extern File file;
    extern Solution solution;

    filename = "Results.csv";

    out.open((file.directory + "Results/" + filename).c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);

    out << "Normalised Crack Speed,Initial pressure, Temperature, Decomp. factor,Speed factor,Support factor,Outflow length,Flaring,Irwin Corten force,Crack driving force,Normalised total,"
            << "CrackOpening, Converged, Iterations \n";

    for(i=1; i<solution.soln+1;i++)
    {

        out << solution.adotc0[i] << "," << solution.p0bar[i] << "," << solution.tempdegc[i] << ","
                << solution.decompression[i] << "," << solution.alpha[i] << ","
                << solution.m[i] << "," << solution.outflow_length[i] << ", ," << solution.g0[i] << ","
                << solution.gg0[i] << "," << solution.gtotal[i] << "," << solution.no_crack_opening[i] << ","
                << solution.not_converged[i] << "," << solution.iterations[i] << "\n";

    }

    out.close();

    filename = "Crack Profiles.csv";

    out.open((file.directory + "Results/" +filename).c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);

    out << "zeta" << ",";

    for(i = 1; i < solution.n; i++)
    {
        out << solution.z[i] << ",";
    }

    out << "\n";

    for(j = 1; j < solution.soln; j++)
    {
        for(i = 0; i < solution.n; i++)
        {
             out << solution.w[j][i] << ",";

        }
        out << "\n";
    }

    out.close();

}

//Writes parameters to txt file with appropriate formatting
void File::writepartxt(Parameters temp, string filename)
{

    out.open((directory + filename).c_str());

    writelinetxt("Input Data", out,1);

    writelinetxt("Material Data", out, 1);

    writelinetxt("matID = ", temp.matid, out, 0);
    writelinetxt("density = ", temp.density, out, 0);
    writelinetxt("eDyn0degC = ", temp.edyn0degc, out, 0);
    writelinetxt("dEdyndT = ", temp.dedyndt, out, 0);
    writelinetxt("creepModulus = ", temp.creepmodulus, out, 0);
    writelinetxt("poisson = ", temp.poisson, out, 1);

    writelinetxt("Pipe Data", out,1);

    writelinetxt("pipeID = ", temp.pipeid, out, 0);
    writelinetxt("diameter = ", temp.diameter, out, 0);
    writelinetxt("sdr = ", temp.sdr, out, 0);
    writelinetxt("notchDepth = ", temp.notchdepth, out, 0);
    writelinetxt("diameterCreepRatio = ", temp.diametercreepratio, out, 1);

    writelinetxt("Test Setup Data", out, 1);

    writelinetxt("fullScale = ", temp.fullscale, out, 0);
    writelinetxt("tempDegC = ", temp.tempdegc, out, 0);
    writelinetxt("p0bar = ", temp.p0bar, out, 0);
    writelinetxt("isBackfilled = ", temp.isbackfilled, out, 0);
    writelinetxt("backfillDepth = ", temp.backfilldepth, out, 0);
    writelinetxt("backfillDensity = ", temp.backfilldensity, out, 0);
    writelinetxt("solidInsidePipe = ", temp.solidinsidepipe, out, 0);
    writelinetxt("waterInsidePipe = ", temp.waterinsidepipe, out, 1);

    writelinetxt("Program Control Data", out, 1);

    writelinetxt("outflowModelOn = ", temp.outflowmodelon, out, 0);
    writelinetxt("lambda = ", temp.lambda, out, 0);
    writelinetxt("solutionmethod = ", temp.solutionmethod, out, 0);
    writelinetxt("numberOfSpeedValues = ", temp.rangenumber, out, 0);
    writelinetxt("elementsInL = ", temp.elementsinl, out, 0);
    writelinetxt("aDotc0 = ", temp.adotc0, out, 0);

    out.close();

}

//Writes parameters to csv file with appropriate formatting
void File::writeparcsv(Parameters temp, string filename)
{

    out.open((directory + filename).c_str());

    writelinecsv("Input Data", out);
    writelinecsv("\n", out);

    writelinecsv("Material Data", out);
    writelinecsv("\n", out);

    writelinecsv("matID", temp.matid, out);
    writelinecsv("density", temp.density, out);
    writelinecsv("eDyn0degC", temp.edyn0degc, out);
    writelinecsv("dEdyndT", temp.dedyndt, out);
    writelinecsv("creepModulus", temp.creepmodulus, out);
    writelinecsv("poisson", temp.poisson, out);
    writelinecsv("\n", out);

    writelinecsv("Pipe Data", out);
    writelinecsv("\n", out);

    writelinecsv("pipeID", temp.pipeid, out);
    writelinecsv("diameter", temp.diameter, out);
    writelinecsv("sdr", temp.sdr, out);
    writelinecsv("notchDepth", temp.notchdepth, out);
    writelinecsv("diameterCreepRatio", temp.diametercreepratio, out);

    writelinecsv("\n", out);
    writelinecsv("Test Setup Data", out);
    writelinecsv("\n", out);

    writelinecsv("fullScale", temp.fullscale, out);
    writelinecsv("tempDegC", temp.tempdegc, out);
    writelinecsv("p0bar", temp.p0bar, out);
    writelinecsv("isBackfilled", temp.isbackfilled, out);
    writelinecsv("backfillDepth", temp.backfilldepth, out);
    writelinecsv("backfillDensity", temp.backfilldensity, out);
    writelinecsv("solidInsidePipe", temp.solidinsidepipe, out);
    writelinecsv("waterInsidePipe", temp.waterinsidepipe, out);

    writelinecsv("\n", out);
    writelinecsv("Program Control Data", out);
    writelinecsv("\n", out);

    writelinecsv("outflowModelOn", temp.outflowmodelon, out);
    writelinecsv("lambda", temp.lambda, out);
    writelinecsv("solutionmethod", temp.solutionmethod, out);
    writelinecsv("numberOfSpeedValues", temp.rangenumber, out);
    writelinecsv("elementsInL", temp.elementsinl, out);
    writelinecsv("aDotc0", temp.adotc0, out);

    out.close();
}

//The following functions write a single line to a txt file
//taking various arguments for different requirements

void File::writelinetxt(string title, double value, ofstream &out, int format)
{
    out << "\t" << title << value << endl;
    if(format == 1)
    {
        out << endl;
    }
}

void File::writelinetxt(string title, string value, ofstream &out, int format)
{
    out << "\t" << title << value << endl;
    if(format == 1)
    {
        out << endl;
    }
}

void File::writelinetxt(string title, ofstream &out, int format)
{
    out << title << endl;
    if(format == 1)
    {
        out << endl;
    }
}

//The following functions write a single line to a csv file
//taking various arguments for different requirements

void File::writelinecsv(string title, double value, ofstream &out)
{
    out << title << "," << value << "\n";
}

void File::writelinecsv(string title, string value, ofstream &out)
{
     out << title << "," << value << "\n";
}

void File::writelinecsv(string title, ofstream &out)
{

    out << title << "," << "\n";

}

//Writes the headers for a txt file
void File::writeheaders(string temp)
{
    filename = temp;
    out.open((directory + filename).c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

    writelinecsv("\n", out);
    lognumber = 0;
    out << "Log number" << "," << "aDotc0" << "," << "Irwin Corten Force" << "," << "diameterRes0" << "," << "residualCrackClosure" << ","
        << "densityratio" << "," << "zetaclosure" << "," << "nodeAtClosure" << "," << "outflowLength" << ","
        << "p1bar" << "," << "v0" << "," << "vStarRes" << "," << "factor" << "," << "aDotCLfactor" << "," << "aDotcClfactor_backfilled"
        << "," << "maxIterations" << "," << "iterations" << "," << "m[0]" << "," << "m[1]" << ","
        << "alpha[0]" << "," << "alpha[1]" << "," << "error" << "," << "notConverged" << ","
        << "pStarUnchoke" << "," << "xUnch" << "," << "pHalfStar" << "," << "pStar" << "," << "tStar" << ","
        << "tStarUnchoke" << "," << "simpsonIntegral" << "," << "unchoked" << "," << "tStarOutflow2" << "\n";

    writelinecsv("\n", out);
    out.close();
}

//Handler for the log file
void File::logprepare(Parameters temp)
{
    initialise();
    filename = "Log/Log.csv";
    writeparcsv(temp, filename);
    writeheaders(filename);
}

//Writes single line using the current log values
void File::writelogline(int newline)
{
    out.open((directory + filename).c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

    if(newline)
    {
    out << " \n";
    lognumber = 0;
    }
    lognumber++;
    out << lognumber << "," << adotc0 << ","
        << g0 << ","
        << diameter_res0 << "," << residual_crack_closure << ","
        << density_ratio << ","
        << zetaClosure << "," << nodeAtClosure << "," << outflowLength << ","
        << p1bar << "," << v0 << ","
        << vStarRes << "," << factor << "," << aDotCLfactor << "," << aDotCLfactor_backfilled << ","
        << maxIterations << "," << iterations << "," << m[0] << "," << m[1] << ","
        << alpha[0] << "," << alpha[1] << "," << error << "," << notConverged << ","
        << pStarUnchoke << "," << xUnch << "," << pHalfStar << "," << pStar << ","
        << tStar << "," << tStarUnchoke << "," << simpsonIntegral << "," << unchoked << ","
        << tStarOutflow2 << "\n";

    out.close();
}

//The following functions collect data from the argument object
//before writing a line using the function above

void File::collect(FracMech fracmech)
{
    g0 = fracmech.g0;
    writelogline(0);
}

void File::collect(Creep creep)
{
    diameter_res0 = creep.diameter_res0;
    residual_crack_closure = creep.residual_crack_closure;
    writelogline(0);
}

void File::collect(Backfill backfill)
{
    density_ratio =  backfill.density_ratio;
    writelogline(0);
}

void File::collect(BeamModel *beamModel, int newline)
{
    zetaClosure = beamModel ->zetaClosure;
    nodeAtClosure = beamModel->nodeAtClosure;
    outflowLength = beamModel -> outflowLength;
    p1bar = beamModel -> p1bar;
    v0 = beamModel ->v0;
    vStarRes = beamModel -> vStarRes;
    aDotCLfactor = beamModel -> aDotCLfactor;
    aDotCLfactor_backfilled = beamModel -> aDotCLfactor_backfilled;
    maxIterations = beamModel -> maxIterations;
    iterations = beamModel -> iterations;
    m[0] = beamModel -> m[0];
    m[1] = beamModel -> m[1];
    alpha[0] = beamModel -> alpha[0];
    alpha[1] = beamModel -> alpha[1];
    error = beamModel -> error;
    notConverged = beamModel -> notConverged;
    factor = beamModel ->factor;

    writelogline(newline);
}

void File::collect(OutflowProcess *outflow, int newline)
{

    pStarUnchoke = outflow ->pStarUnchoke;
    xUnch = outflow -> xUnch;
    pHalfStar = outflow -> pHalfStar;
    pStar = outflow -> pStar;
    tStar = outflow -> tStar;
    tStarUnchoke = outflow -> tStarUnchoke;
    simpsonIntegral = outflow -> simpsonIntegral;
    unchoked = outflow -> unchoked;
    tStarOutflow2 =  outflow -> tStarOutflow2;

    writelogline(newline);

}



