#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QtWidgets>
#include "simulation_moudle.h"
class custombutton: public QPushButton
{
    Q_OBJECT
public:
    custombutton(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    Simulation_Moudle* moudle;
};
#endif // CUSTOMBUTTON_H
