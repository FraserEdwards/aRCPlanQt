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

private:
    Ui::dialog *ui;
};

#endif // DIALOG_H
