#ifndef GUIOUTPUT_H
#define GUIOUTPUT_H

#include <QWidget>

namespace Ui {
class guioutput;
}

class guioutput : public QWidget
{
    Q_OBJECT

public:
    explicit guioutput(QWidget *parent = 0);
    ~guioutput();

private slots:

    void on_Resultscombo_currentTextChanged(const QString &arg1);

    void on_Crackspeedcombo_currentTextChanged(const QString &arg1);

    void on_outflowresult_textChanged(const QString &arg1);

    void on_cortendriving_textChanged(const QString &arg1);

    void on_normalisedforce_textChanged(const QString &arg1);

    void on_newcase_clicked();

    void on_quit_clicked();

private:
    Ui::guioutput *ui;
};

#endif // GUIOUTPUT_H
