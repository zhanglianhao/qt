#include "copygroup.h"
copygroup::copygroup()
{

}
copygroup::~copygroup()
{
    int count;
    count=this->moudle_group.size();
    for(int i=0;i<count;i++)
        delete this->moudle_group[i];
}
bool copygroup::findmoudle(Button* button)
{
    for(int i=0;i<this->moudle_group.size();i++)
    {
        if(this->moudle_group[i]->button==button)
            return true;
    }
    return false;
}
