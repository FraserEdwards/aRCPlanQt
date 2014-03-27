#include <cstdlib>
using namespace std;

#include "Filepath.h"
#include "gui.h"

double gG0;
string location;

int main(int argc, char *argv[])
{
    // Read the problem configuration file to provide parameter values where library data does not exist
    Filepath filePath;
    GUI gui;
    gui.run(argc, argv);

    return 0;
}
