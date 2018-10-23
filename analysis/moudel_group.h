#ifndef MOUDEL_GROUP_H
#define MOUDEL_GROUP_H
#include "simulation_moudle.h"
#include "custombutton.h"
class moudel_group
{
public:
    QList<Simulation_Moudle*> group;
    moudel_group();
    Simulation_Moudle* findwithbutton(Button* button);
};

#endif // MOUDEL_GROUP_H
