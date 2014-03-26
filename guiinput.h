#ifndef GUIINPUT_H
#define GUIINPUT_H

#include <QWidget>

namespace Ui {
class guiinput;
}

class guiinput : public QWidget
{
    Q_OBJECT

public:
    explicit guiinput(QWidget *parent = 0);
    ~guiinput();

private slots:

    void on_Runbutton_clicked();
    void on_checkBox_2_toggled(bool checked);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

private:
    Ui::guiinput *ui;
};

#endif // GUIINPUT_H
