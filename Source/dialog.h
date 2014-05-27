#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
using namespace std;

namespace Ui {
class dialog;
}

class dialog : public QDialog
{
    Q_OBJECT

public:

    explicit dialog(QWidget *parent = 0);
    ~dialog();
    void Warning(string title);
    void Warning(string title, double value);
    void Warning(string title, double value, string title1, double value1);
    void Warning(string title, double value, string title1, double value1, string title2, double value2);
    void Warning(string title, double value, string title1, double value1, string title2, double value2, string title3, double value3);
    void Warning(string title, string title1, double value1, string title2, double value2, string title3, double value3, string title4, double value4, string title5, double value5);

private:
    Ui::dialog *ui;
};

#endif // DIALOG_H
