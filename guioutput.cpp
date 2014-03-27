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

void guioutput::on_Resultscombo_currentTextChanged(const QString &arg1)
{

}

void guioutput::on_Crackspeedcombo_currentTextChanged(const QString &arg1)
{

}

void guioutput::on_outflowresult_textChanged(const QString &arg1)
{

}

void guioutput::on_cortendriving_textChanged(const QString &arg1)
{

}

void guioutput::on_normalisedforce_textChanged(const QString &arg1)
{

}

void guioutput::on_newcase_clicked()
{

}

void guioutput::on_quit_clicked()
{

}
