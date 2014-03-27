#include <QString>

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

void guiinput::setnames(Parameters parameters)
{

ui -> materialname -> setAlignment(Qt::AlignRight);
ui ->materialname->setText(QString::fromStdString(parameters.matID));

ui -> density -> setAlignment(Qt::AlignRight);
ui -> density->setText(QString::number(parameters.density));

ui -> dynamicmodulus -> setAlignment(Qt::AlignRight);
ui -> dynamicmodulus ->setText(QString::number(parameters.eDyn0degC));

ui -> deltadynamicmodulus -> setAlignment(Qt::AlignRight);
ui -> deltadynamicmodulus ->setText(QString::number(parameters.dEdyndT));

ui -> creepmodulus -> setAlignment(Qt::AlignRight);
ui -> creepmodulus -> setText(QString::number(parameters.creepModulus));

ui -> dynpoissonratio -> setAlignment(Qt::AlignRight);
ui -> dynpoissonratio -> setText(QString::number(parameters.poisson));

ui -> from -> setAlignment(Qt::AlignRight);
ui -> from -> setText(QString::number(0));

ui -> to -> setAlignment(Qt::AlignRight);
ui -> to -> setText(QString::number(1));

ui -> noofpoints -> setAlignment(Qt::AlignRight);
ui -> noofpoints -> setText(QString::number(50));

ui -> pipename -> setAlignment(Qt::AlignRight);
ui -> pipename->setText(QString::fromStdString(parameters.pipeID));

ui -> outsidediameter -> setAlignment(Qt::AlignRight);
ui -> outsidediameter -> setText(QString::number(parameters.diameter));

ui -> sdr -> setAlignment(Qt::AlignRight);
ui -> sdr -> setText(QString::number(parameters.sdr));

ui -> groovedepth -> setAlignment(Qt::AlignRight);
ui -> groovedepth -> setText(QString::number(parameters.notchDepth));

ui -> relativediameter -> setAlignment(Qt::AlignRight);
ui -> relativediameter -> setText(QString::number(parameters.diameterCreepRatio));

ui -> testtemperature -> setAlignment(Qt::AlignRight);
ui -> testtemperature -> setText(QString::number(parameters.tempDegC));

ui -> initialpressure -> setAlignment(Qt::AlignRight);
ui -> initialpressure -> setText(QString::number(parameters.p0bar));

ui -> backfilldepth -> setAlignment(Qt::AlignRight);
ui -> backfilldepth -> setText(QString::number(parameters.backfillDepth));

ui -> backfilldensity -> setAlignment(Qt::AlignRight);
ui -> backfilldensity -> setText(QString::number(parameters.backfillDensity));

ui -> solidfraction -> setAlignment(Qt::AlignRight);
ui -> solidfraction -> setText(QString::number(parameters.solidInsidePipe));

ui -> waterfraction -> setAlignment(Qt::AlignRight);
ui -> waterfraction -> setText(QString::number(parameters.waterInsidePipe));

ui -> initiallength -> setAlignment(Qt::AlignRight);
ui -> initiallength -> setText(QString::number(parameters.lambda));

ui -> crackspeed -> setAlignment(Qt::AlignRight);
ui -> crackspeed -> setText(QString::number(parameters.aDotc0));

ui -> fdnumber -> setAlignment(Qt::AlignRight);
ui -> fdnumber -> setText(QString::number(parameters.elementsInL));
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
