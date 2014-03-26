#include "guiinput.h"
#include "ui_guiinput.h"

guiinput::guiinput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::guiinput)
{
    ui->setupUi(this);
}

guiinput::~guiinput()
{
    delete ui;
}

void guiinput::on_Runbutton_clicked()
{

}

void guiinput::on_rangemode_stateChanged(int arg1)
{

}

void guiinput::on_singlemode_stateChanged(int arg1)
{

}

void guiinput::on_parameter_currentTextChanged(const QString &arg1)
{

}

void guiinput::on_from_textChanged(const QString &arg1)
{

}

void guiinput::on_to_textChanged(const QString &arg1)
{

}

void guiinput::on_noofpoints_textChanged(const QString &arg1)
{

}

void guiinput::on_materialname_textChanged(const QString &arg1)
{

}

void guiinput::on_outsidediameter_textChanged(const QString &arg1)
{

}

void guiinput::on_density_textChanged(const QString &arg1)
{

}

void guiinput::on_dynamicmodulus_textChanged(const QString &arg1)
{

}

void guiinput::on_Tabs_tabBarClicked(int index)
{

}

void guiinput::on_deltadynamicmodulus_textChanged(const QString &arg1)
{

}

void guiinput::on_creepmodulus_textChanged(const QString &arg1)
{

}

void guiinput::on_dynpoissonratio_textChanged(const QString &arg1)
{

}

void guiinput::on_pipename_textChanged(const QString &arg1)
{

}

void guiinput::on_sdr_textChanged(const QString &arg1)
{

}

void guiinput::on_groovedepth_textChanged(const QString &arg1)
{

}

void guiinput::on_relativediameter_textChanged(const QString &arg1)
{

}

void guiinput::on_fs_stateChanged(int arg1)
{

}

void guiinput::on_s4_stateChanged(int arg1)
{

}

void guiinput::on_backfill_stateChanged(int arg1)
{

}

void guiinput::on_testtemperature_textChanged(const QString &arg1)
{

}

void guiinput::on_initialpressure_textChanged(const QString &arg1)
{

}

void guiinput::on_backfilldepth_textChanged(const QString &arg1)
{

}

void guiinput::on_backfilldensity_textChanged(const QString &arg1)
{

}

void guiinput::on_solidfraction_textChanged(const QString &arg1)
{

}

void guiinput::on_waterfraction_textChanged(const QString &arg1)
{

}

void guiinput::on_fixedlength_stateChanged(int arg1)
{

}

void guiinput::on_initiallength_textChanged(const QString &arg1)
{

}

void guiinput::on_crackspeed_textChanged(const QString &arg1)
{

}

void guiinput::on_fdnumber_textChanged(const QString &arg1)
{

}

void guiinput::on_plotcrack_stateChanged(int arg1)
{

}
