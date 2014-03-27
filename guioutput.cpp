#include <QString>

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

void guioutput::setresults(Solution solution)
{

ui -> outflowresult -> setAlignment(Qt::AlignRight);
ui -> outflowresult ->setText(QString::number(solution.outflowLength[solution.soln]));

ui -> cortendriving -> setAlignment(Qt::AlignRight);
ui -> cortendriving ->setText(QString::number(solution.g0[solution.soln]));

ui -> normalisedforce -> setAlignment(Qt::AlignRight);
ui -> normalisedforce -> setText(QString::number(solution.gTotal[solution.soln]));

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
