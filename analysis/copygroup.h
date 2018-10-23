#ifndef COPYGROUP_H
#define COPYGROUP_H
#include <QtWidgets>
#include "simulation_moudle.h"
class copygroup
{
public:
    copygroup();
    ~copygroup();
    QList<Simulation_Moudle*> moudle_group;
    QList<QPoint> distance;
    QList<int> width;
    QList<int> height;
    QPoint start;
    QPoint end;
    bool findmoudle(Button* button);

};

#endif // COPYGROUP_H
