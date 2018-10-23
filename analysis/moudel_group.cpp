#include "moudel_group.h"
moudel_group::moudel_group()
{

}
Simulation_Moudle* moudel_group::findwithbutton(Button* button)
{
    for(int i=0;i<this->group.size();i++)
        if(group[i]->button==button)
            return group[i];
    return nullptr;
}
