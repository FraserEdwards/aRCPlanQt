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

private:
    Ui::guioutput *ui;
};

#endif // GUIOUTPUT_H
