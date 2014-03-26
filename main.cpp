#include "guiinput.h"
#include "guioutput.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    guiinput w;
    guioutput x;
    w.show();
    x.show();

    return a.exec();
}
