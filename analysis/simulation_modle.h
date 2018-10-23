#ifndef SIMULATION_MODLE_H
#define SIMULATION_MODLE_H
#include <QtWidgets>
#include "custombutton.h"
struct line
{
QPushButton* start;
QPushButton* end;
};
struct moudle_param
{
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    QList<line*> connect_line;

};

class simulation_moudle
{
public:
    QPushButton* button;
    QIcon* icon;
    int index;
    int id;
    int x;
    int y;
    QString name;
    QList<moudle_param*> node;

};
#endif // SIMULATION_MODLE_H
