#include "guioutput.h"
#include "ui_guioutput.h"

guioutput::guioutput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::guioutput)
{
    ui->setupUi(this);
}

guioutput::~guioutput()
{
    delete ui;
}
