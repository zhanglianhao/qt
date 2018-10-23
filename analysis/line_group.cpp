#include "line_group.h"

line_group::line_group()
{
    this->current_id=0;
    this->idcount=0;

}
Line* line_group::findwithid(int id)
{
    for(int i=0;i<this->group.size();i++)
        if(this->group[i]->id==id)
            return this->group[i];
    return nullptr;

}
point* line_group::find_point_withid(Line* line,int id)
{
    for(int i=0;i<line->line.size();i++)
    {
        if(line->line[i].id==id)
            return &line->line[i];
    }
    return nullptr;
}
bool line_group::line_exist(QPoint* pointt,int error)
{
   Line* linee;   
   for(int i=0;i<this->group.size();i++)
   {
       linee=this->group[i];
       for(int j=0;j<linee->line.size();j++)
       {
         if(exist(pointt,&(linee->line[j].start),&linee->line[j].end,error)==1)
         //if(qAbs(point->x()-linee->line[j].end.x())<=error&&qAbs(point->y()-linee->line[j].end.y())<=error)
         {
             linee->line[j].flag=true;
             linee->line[j].end_flag=true;
             this->current_proportion=1*this->scale;
             this->parent_line=&linee->line[j];
             current_id=i;

             this->start_end=2;
            // qDebug()<<this->current_proportion;
             return true;
         }
         else if(exist(pointt,&(linee->line[j].start),&linee->line[j].end,error)==2)
         {
             linee->line[j].start_flag=true;
             this->current_proportion=0*this->scale;
             this->parent_line=&linee->line[j];
             current_id=i;

             this->start_end=1;
            // qDebug()<<this->current_proportion;
             return true;
         }
         else if(exist(pointt,&(linee->line[j].start),&linee->line[j].end,error)==3)
         {
             this->parent_line=&linee->line[j];
             current_id=i;

             this->start_end=0;
           //  qDebug()<<this->current_proportion;
             return true;
         }
       }
   }
   return false;
}
int line_group::exist(QPoint* point,QPoint* start,QPoint* end,int error)
{
    if((qAbs(point->x()-end->x())<=error&&qAbs(point->y()-end->y())<=error))
    {
        point->setX(end->x());
        point->setY(end->y());
        return 1;
    }
    else if(qAbs(point->x()-start->x())<=error&&qAbs(point->y()-start->y())<=error)
    {
        point->setX(start->x());
        point->setY(start->y());
        return 2;
    }
    else if(start->x()==end->x())
    {
        if(qAbs(point->x()-start->x())<=error&&((point->y()<=end->y()&&point->y()>=start->y())||(point->y()>=end->y()&&point->y()<=start->y())))
        {
            this->current_proportion=this->scale*(point->y()-start->y())/(end->y()-start->y());
            point->setX(start->x());
            return 3;
        }
    }
    else if((point->x()>=start->x()&&point->x()<=end->x())||(point->x()<=start->x()&&point->x()>=end->x()))
    {
        int temp=(point->x()-start->x())*(end->y()-start->y())/(end->x()-start->x())+start->y();
       // qDebug()<<point->y()<<temp;
        if(qAbs(temp-point->y())<=error)
        {
            this->current_proportion=this->scale*(point->x()-start->x())/(end->x()-start->x());
            point->setY(temp);
            return 3;
        }
    }
    return 0;
}
point* line_group::deleteline(QPoint* pos,int error)
{
    Line* linee;
    for(int i=0;i<this->group.size();i++)
    {
        linee=this->group[i];
        for(int j=0;j<linee->line.size();j++)
        {
          if(exist(pos,&(linee->line[j].start),&linee->line[j].end,error)!=0)
          //if(qAbs(point->x()-linee->line[j].end.x())<=error&&qAbs(point->y()-linee->line[j].end.y())<=error)
          {
              delete_flag=true;
              delete_id=i;
              current_id=i;
              //qDebug()<<i;
              return &linee->line[j];
          }
        }
    }
    delete_flag=false;
    return nullptr;
}
void line_group::current_idwithid(int id)
{
    for(int i=0;i<this->group.size();i++)
        if(this->group[i]->id==id)
        {
            this->current_id=i;
            break;
        }
}
void line_group::startline(Button* button)
{
    Line* line=new Line();
    line->id=this->idcount;
    //line->startbutton.push_back(button);
    this->current_button=button;
    this->group.push_back(line);
    this->idcount++;
    if(this->idcount==13)
        this->idcount++;
    current_idwithid(line->id);

}
void line_group::start_line(Button* button)
{

    //QPoint position;
   // bool flag;    
    Line* linee=this->group[this->current_id];
    point pos=linee->line[linee->line.size()-1];
    linee->line.removeLast();    

    /*
    position=pos.start;
    pos.start=pos.end;
    pos.end=position;

    flag=pos.start_flag;
    pos.start_flag=pos.end_flag;
    pos.end_flag=flag;
    */

    linee->line.insert(0,pos);
    this->group[this->current_id]->startbutton.push_back(button);
    this->group[this->current_id]->startline.push_back(&linee->line[0]);
    this->group[this->current_id]->line[0].flag=true;
    this->group[this->current_id]->line[0].end_flag=true;//start点已为连接状态
    this->group[this->current_id]->line[0].start_line=2;
    //turn_state(&this->group[this->current_id]->line[0]);
}
void line_group::endline(Button* button,int index,bool flag,int nodeindex)
{

    this->group[this->current_id]->endbutton.push_back(button);
    this->group[this->current_id]->endline.push_back(&this->group[this->current_id]->line[index]);
    this->group[this->current_id]->endindex.push_back(nodeindex);

    if(flag)
    {
        this->group[this->current_id]->line[index].end_flag=true;
        this->group[this->current_id]->line[index].end_line=2;
    }
    else
    {
        this->group[this->current_id]->line[index].start_flag=true;
        this->group[this->current_id]->line[index].end_line=1;
    }
   // qDebug()<<this->current_id<<this->group[this->current_id]->endbutton.size();
    this->group[this->current_id]->endline[this->group[this->current_id]->endline.size()-1]->flag=true;
}
bool line_group::insertline(QPoint* start,QPoint* end)
{
    point pos;
    //QPoint position;

    if(qAbs(start->x()-end->x())>=5||qAbs(start->y()-end->y())>=5)
    {
        //qDebug()<<*start<<*end;
        pos.start_flag=true;
        pos.proportion=this->current_proportion;//branch line在parent line 中的位置
        pos.start.setX(start->x());
        pos.start.setY(start->y());
        pos.end.setX(end->x());
        pos.end.setY(end->y());
        pos.id=this->group[this->current_id]->point_current_id++;
        if(this->group[this->current_id]->point_current_id==13)
            this->group[this->current_id]->point_current_id++;
        this->group[this->current_id]->line.push_back(pos);

        //将该line接入父line的分支中 line中的第一条line为根line，不需要添加parent line
        if(this->group[this->current_id]->line.size()!=1)
        {
            this->parent_line->branch.push_back(&this->group[this->current_id]->line[this->group[this->current_id]->line.size()-1]);
            this->group[this->current_id]->line[this->group[this->current_id]->line.size()-1].parent_line=this->parent_line;
            this->group[this->current_id]->line[this->group[this->current_id]->line.size()-1].parent_start_end=this->start_end;
            if(this->start_end==1)
                this->parent_line->start_point.push_back(&this->group[this->current_id]->line[this->group[this->current_id]->line.size()-1]);
            else if(this->start_end==2)
                this->parent_line->end_point.push_back(&this->group[this->current_id]->line[this->group[this->current_id]->line.size()-1]);
        }
        else
        {
            this->group[this->current_id]->startline.push_back(&this->group[this->current_id]->line[0]);
            this->group[this->current_id]->line[0].start_line=1;
            this->group[this->current_id]->startbutton.push_back(this->current_button);
        }
        return true;
      /*  if(this->group[this->current_id]->line.size()==1)
        {
            position=this->group[this->current_id]->line[0].start;
            this->group[this->current_id]->line[0].start=this->group[this->current_id]->line[0].end;
            this->group[this->current_id]->line[0].end=position;
        }
        */
    }
    return false;
}
void line_group::changeline(Button* button,QPoint* position,int inputsize,int outputsize)
{
    QPoint inputpoint;
    QPoint outputpoint;
    inputpoint.setX(position->x()+button->width());
    outputpoint.setX(position->x());
    inputpoint.setY(position->y()+button->height()/2);
    outputpoint.setY(position->y()+button->height()/2);
    int y=0;
    //设定与moudle相连的line起始位置，跟随moudle移动
    for(int i=0;i<this->group.size();i++)
    {      
        for(int j=0;j<this->group[i]->startbutton.size();j++)
        {
            if(this->group[i]->startbutton[j]==button)
            {
                y=position->y()+int((this->group[i]->startindex[j]+0.5)*button->height()/(outputsize));
                //qDebug()<<qAbs(this->group[i]->line[0].start.x()-inputpoint.x())<<" "<<qAbs(this->group[i]->line[0].end.x()-inputpoint.x());
                if(this->group[i]->line[0].start_line==1)
                {
                    {
                        this->group[i]->line[0].start.setX(inputpoint.x());
                        this->group[i]->line[0].start.setY(y);
                    }
                }
                else if(this->group[i]->line[0].start_line==2)
                {
                    this->group[i]->line[0].end.setX(inputpoint.x());
                    this->group[i]->line[0].end.setY(y);
                }
                change_linegroup(this->group[i]->startline[0]);

               // this->group[i]->line[0].start=inputpoint;
            }
        }
        for(int j=0;j<this->group[i]->endbutton.size();j++)
        {
            if(this->group[i]->endbutton[j]==button)
            {
                y=position->y()+int((this->group[i]->endindex[j]+0.5)*button->height()/(inputsize));
                if((*this->group[i]->endline[j]).end_line==1)
                {
                    (*this->group[i]->endline[j]).start.setX(outputpoint.x());
                    (*this->group[i]->endline[j]).start.setY(y);
                }
                else if((*this->group[i]->endline[j]).end_line==2)
                {
                    (*this->group[i]->endline[j]).end.setX(outputpoint.x());
                    (*this->group[i]->endline[j]).end.setY(y);
                }
                change_linegroup(this->group[i]->endline[j]);
              //  (*this->group[i]->endline[j]).end=outputpoint;
            }
        }
    }
}
void line_group::change_linegroup(point* ppoint)
{
    if(ppoint->branch.size()==0)
        return;
    for(int i=0;i<ppoint->branch.size();i++)
    {
        change_brance(ppoint,ppoint->branch[i]);
        change_linegroup(ppoint->branch[i]);
    }
}
void line_group::change_brance(point* point_parent,point* point_child)
{
    int y;
    int x;
    if(point_parent->start.x()==point_parent->end.x())
    {
        point_child->start.setX(point_parent->start.x());
        y=point_parent->start.y()+(point_parent->end.y()-point_parent->start.y())*point_child->proportion/this->scale;
        point_child->start.setY(y);
    }
    else
    {
        x=point_parent->start.x()+(point_parent->end.x()-point_parent->start.x())*point_child->proportion/this->scale;
        point_child->start.setX(x);
        y=point_parent->start.y()+(point_parent->end.y()-point_parent->start.y())*point_child->proportion/this->scale;
        point_child->start.setY(y);
    }
}
int line_group::moudle_point(Button* button,QPoint* pos,int error,bool flag,int nodeindex,bool leftright)
{
    Line* linee;
    QPoint* position_end;
    QPoint* position_start;
    point pos1;
    //QPoint position1;
    for(int i=0;i<this->group.size();i++)
    {
        linee=this->group[i];
        //position=&linee->line[linee->line.size()-1].end;
       // qDebug()<<*position<<*pos;
        for(int j=0;j<linee->line.size();j++)
        {            
            position_end=&linee->line[j].end;
            position_start=&linee->line[j].start;
            if(flag==true&&linee->line[j].end_flag==false&&leftright==true&&qAbs(position_end->x()-pos->x())<=error&&qAbs(position_end->y()-pos->y())<=error)
            {
                this->current_id=i;
                endline(button,j,true,nodeindex);
                return 1;
            }
            if(flag==true&&linee->line[j].start_flag==false&&leftright==true&&qAbs(position_start->x()-pos->x())<=error&&qAbs(position_start->y()-pos->y())<=error)
            {
                this->current_id=i;
                endline(button,j,false,nodeindex);
                return 1;
            }
            if(linee->startbutton.size()==0&&leftright==false)
            {
                if(linee->line[j].end_flag==false)
                {
                    if(qAbs(position_end->x()-pos->x())<=error&&qAbs(position_end->y()-pos->y())<=error)
                    {
                        pos1=linee->line[j];
                        linee->line.removeAt(j);
                        linee->line.insert(0,pos1);
                        //linee->line[0].flag=true;
                        this->current_id=i;
                        /*
                        position1=linee->line[0].start;
                        linee->line[0].start=linee->line[0].end;//line 起始位置互换
                        linee->line[0].end=position1;
                        linee->line[0].flag=true;
                        */
                        linee->line[0].end_flag=true;
                        linee->line[0].start_line=2;
                        //turn_state(&linee->line[0]);
                        this->group[this->current_id]->startbutton.push_back(button);
                        this->group[this->current_id]->startline.push_back(&linee->line[0]);
                        this->group[this->current_id]->startindex.push_back(nodeindex);
                        return 2;
                    }

                }
                if(linee->line[j].start_flag==false)
                {
                    if(qAbs(position_start->x()-pos->x())<=error&&qAbs(position_start->y()-pos->y())<=error)
                    {                       
                        pos1=linee->line[j];
                        linee->line.removeAt(j);
                        linee->line.insert(0,pos1);
                        //linee->line[0].flag=true;
                        this->current_id=i;

                        linee->line[0].flag=true;

                        linee->line[0].start_flag=true;
                        linee->line[0].start_line=1;
                        this->group[this->current_id]->startbutton.push_back(button);
                        this->group[this->current_id]->startline.push_back(&linee->line[0]);
                        this->group[this->current_id]->startindex.push_back(nodeindex);
                        return 2;
                    }

                }
            }
        }
    }
    return 0;
}
void line_group::remove_output(Button* button,Line* linee)
{
    for(int i=0;i<linee->endbutton.size();i++)
    {
        if(linee->endbutton[i]==button)
        {
            linee->endbutton.removeAt(i);
            linee->endindex.removeAt(i);
            if(linee->endline[i]->end_line==2)
                linee->endline[i]->end_flag=false;
            else if(linee->endline[i]->end_line==1)
                linee->endline[i]->start_flag=false;
            linee->endline.removeAt(i);
        }
    }
}
void line_group::remove_input(Line* linee)
{
    //QPoint position1;
    linee->startbutton.removeAt(0);
    linee->startindex.removeAt(0);
    if(linee->startline[0]->start_line==1)
        linee->startline[0]->start_flag=false;
    else if(linee->startline[0]->start_line==2)
        linee->startline[0]->end_flag=false;

    linee->startline.removeAt(0);
    //qDebug()<<linee->startline[0]->start_flag<<linee->startline[0]->end_flag;

    /*
    position1=linee->line[0].start;
    linee->line[0].start=linee->line[0].end;//line 起始位置互换
    linee->line[0].end=position1;
    linee->line[0].flag=false;
    */
}
int line_group::findindex_input()
{
    return 0;
}
int line_group::findindex_output(Line* line,Button* button)
{
    for(int i=0;i<line->endbutton.size();i++)
        if(line->endbutton[i]==button)
            return i;
    //return 0;
}
/*
void line_group::turn_state(point* parent)
{
    for(int i=0;i<parent->branch.size();i++)
    {
        parent->branch[i]->turn_flag=~parent->branch[i]->turn_flag;
    }
}
*/
