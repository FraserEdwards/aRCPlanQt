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

void guiinput::on_checkBox_2_toggled(bool checked)
{

}

void guiinput::on_comboBox_2_currentTextChanged(const QString &arg1)
{

}

void guiinput::on_lineEdit_4_textChanged(const QString &arg1)
{

}

void guiinput::on_lineEdit_5_textChanged(const QString &arg1)
{

}

void guiinput::on_lineEdit_6_textChanged(const QString &arg1)
{

}
