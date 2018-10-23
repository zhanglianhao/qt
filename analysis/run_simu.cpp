#include "run_simu.h"
#include <math.h>
#include "analysis.h"
#include "mainwindow.h"
Run_Simu::Run_Simu(QWidget *parent,moudel_group* group,double time_length,double time_step,bool real_flag) : QMainWindow(parent),simulation_group(group)
{
    time.simu_time=time_length;
    time.simu_step=time_step;
    time.simu_count_max=int(time.simu_time/time.simu_step);
    this->flag_real=real_flag;
    init();
}
void Run_Simu::init()
{
    statusBar_init();
    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(100,150,200)));//设置背景颜色
    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    for(int i=0;i<ui->x_count;i++)
    {
        time_label.push_back(new QLabel(this));
        time_label[time_label.size()-1]->setGeometry(ui->x_start+ui->x_axia_precision*ui->x_interval_point*i,ui->y_start+2,ui->x_axia_precision*ui->x_interval_point-3,20);
    }

    for(int i=0;i<this->ui->y_count;i++)
    {
        value_label.push_back(new QLabel(this));
        value_label[value_label.size()-1]->setGeometry(ui->x_start-40,ui->y_start-12-ui->y_axis_length/ui->y_count*(i+1),35,20);
        value_label.push_back(new QLabel(this));
        value_label[value_label.size()-1]->setGeometry(ui->x_start-40,ui->y_start-12+ui->y_axis_length/ui->y_count*(i+1),35,20);
    }
}
void Run_Simu::statusBar_init()
{
    statusBar=new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    this->setStatusBar(statusBar);
    start_stop=new QPushButton(this);
    start_stop->setVisible(true);
    start_stop->setText("运行");
    connect(start_stop, &QAbstractButton::clicked, this, &Run_Simu::simu_run);
    run_stop_state=true;
}
void Run_Simu::simu_run()
{
    if(this->real_flag==true)
    {
        this->parent->statr_message("Currently is in connection state",1000);
        return;
    }

    if(run_stop_state==true)
    {
        run_stop_state=false;
        start_stop->setText("停止");
        mDataTimer.stop();
    }
    else
    {
        run_stop_state=true;
        start_stop->setText("运行");
        mDataTimer.start(10);
    }
}
bool Run_Simu::getstate()
{
    return this->run_stop_state;
}
void Run_Simu::statusBar_show()
{
    this->statusBar->showMessage("save",1000);
}
void Run_Simu::timerSlot()
{
    //qint64 time_before=QTime::currentTime().msec();
    time_before=QDateTime::currentDateTime().time();//QDateTime比Qtime获取毫秒级时间更精确
    //qDebug()<<time_before<<1;
    if(time.simu_count<=time.simu_count_max)
    {

        for(int i=0;i<this->moudle_generator->group.size();i++)
        {
            //qDebug()<<QDateTime::currentDateTime();
            //this->simulation_group->group[0]->output_number[0]=i;
            output_generator(this->moudle_generator->group[i],time.simu_count);
            run_simulation(this->moudle_generator->group[i]);

            //qDebug()<<QDateTime::currentDateTime();
            //qDebug()<<"\n";
        }
        /*
        for(int i=0;i<this->moudle_socket->group.size();i++)
        {
            run_socket(this->moudle_socket->group[i]);
        }
        */
        time.simu_count++;
        this->draw_point_flag=true;
    }
    //qDebug()<<QDateTime::currentDateTime()<<1;
    update();
    if(time.simu_count>time.simu_count_max)
    {
        run_end_flag=true;//仿真结束
        this->real_flag=false;
        int index=this->parent->run_to_mainwindow(this);
        if(index!=-1)//运行结束，断开所有客户端连接
        {
            if(this->parent->mainwindow_group[index]->sys_flag->socket_main!=nullptr)
                this->parent->mainwindow_group[index]->sys_flag->socket_main->disconnectFromHost();
            this->parent->mainwindow_group[index]->disconnect_input(0);
        }
        //mDataTimer.stop();
        mDataTimer.start(100);       
    }
    else if(time.simu_count==time.simu_count_max)//是否保存数据
    {
        this->save_graph_date();
    }
    else
    {
        if(this->flag_real==true)
            mDataTimer.start(int(time.simu_step*1000));
        else
            mDataTimer.start(10);
        clear_save_flag();//清save标志
        //qDebug()<<QTime::currentTime().msec();
    }

}
void Run_Simu::change()
{
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    int index=this->ui->graph_group.indexOf(button);
    if(this->moudle_graph->group[index]->grapg_flag==false)
    {
        this->moudle_graph->group[index]->grapg_flag=true;
        remove_shadow(button);
    }
    else
    {
        this->moudle_graph->group[index]->grapg_flag=false;
        set_shadow(button);
    }
    update();
}
void Run_Simu::mousePressEvent(QMouseEvent* event)
{
    this->parent->run_current=this;
    QPoint point=this->mapFromGlobal(event->globalPos());
    QRect rect(ui->x_start,ui->y_start-ui->y_axis_length,ui->x_length,ui->y_axis_length*2);
    this->setFocusPolicy(Qt::StrongFocus);
    if(this->ui->start_drag)
    {
        if(rect.contains(point))
        {
            this->time.time_drag=this->time.time_temp;
            this->ui->drag_x_start=point.x();
        }
    }
}//按下
void Run_Simu::mouseMoveEvent(QMouseEvent* event)
{
    QPoint point=this->mapFromGlobal(event->globalPos());
    if(this->ui->start_drag)
    {
        if((this->time.time_temp-point.x()+this->ui->drag_x_start)>=((ui->x_count-1)*ui->x_interval_point)&&(this->time.time_temp-point.x()+this->ui->drag_x_start)<=this->time.simu_count)
        {
            this->time.time_drag=this->time.time_temp-point.x()+this->ui->drag_x_start;
            update();
        }
    }
}//按下移动
void Run_Simu::mouseReleaseEvent(QMouseEvent* event)
{
    if(this->ui->start_drag)
    {
        this->time.time_temp=this->time.time_drag;
    }
}//松开
void Run_Simu::keyReleaseEvent(QKeyEvent *event)
{
}
void Run_Simu::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Z)
    {
        if(this->ui->start_drag)
        {
            this->ui->start_drag=false;
            update();
        }
        else
        {
            if(this->time.simu_count>((ui->x_count-1)*ui->x_interval_point))
                this->ui->start_drag=true;
        }
    }
    if(event->modifiers() == Qt::ControlModifier&&(event->key() == Qt::Key_S))
    {
       this->save_graph_date();
    }

}
void Run_Simu::wheelEvent(QWheelEvent* event)
{
    if(check_focus()==-1)
        return;
    //qDebug()<<this->ui->x_axia_precision;
    if(event->delta()>0)//缩小
    {
        //qDebug()<<(time.time_drag-((ui->x_count-1)*ui->x_interval_point))<<time.time_drag;
        if(this->ui->x_axia_precision>1)
        {
            this->ui->x_axia_precision--;
            while(this->ui->x_interview_length%this->ui->x_axia_precision!=0)
            {
                this->ui->x_axia_precision--;
                if(this->ui->x_axia_precision==1)
                    break;
            }
            if(!(this->ui->start_drag&&time.time_drag-((ui->x_count-1)*this->ui->x_interview_length/this->ui->x_axia_precision)<0))
            {
                this->ui->x_interval_point=this->ui->x_interview_length/this->ui->x_axia_precision;
            }
        }
    }
    else if(event->delta()<0)//放大
    {
        if(this->ui->x_axia_precision<this->ui->x_interview_length)
        {
            this->ui->x_axia_precision++;
            while(this->ui->x_interview_length%this->ui->x_axia_precision!=0)
            {
                this->ui->x_axia_precision++;
                if(this->ui->x_axia_precision==this->ui->x_interview_length)
                    break;
            }
            this->ui->x_interval_point=this->ui->x_interview_length/this->ui->x_axia_precision;
        }

    }
}
void Run_Simu::paintEvent(QPaintEvent *)
{
    //qDebug()<<QDateTime::currentDateTime()<<2;
    QPainter painter(this);//painter画笔只能是从属于当前类
   // if(draw_point_flag)
   // {
    update_size();
    check_focus();
    if(this->draw_point_flag==true||this->time.simu_count>this->time.simu_count_max)
    {
        check_data();
        if(this->ui->start_drag!=true)
        {
            if(this->time.simu_count<((ui->x_count-1)*ui->x_interval_point))
                get_max(0,this->time.simu_count);
            else
                get_max(this->time.simu_count-((ui->x_count-1)*ui->x_interval_point-1),this->time.simu_count);
        }
        else
        {
            get_max(this->time.time_drag-((ui->x_count-1)*ui->x_interval_point-1),this->time.time_drag);
        }

        for(int i=0;i<this->moudle_graph->group.size();i++)
        {
            if(i==0)
                painter.setPen(QPen(Qt::black,2));
            else if(i==1)
                painter.setPen(QPen(Qt::red,2));
            else if(i==2)
                painter.setPen(QPen(Qt::green,2));
            else if(i==3)
                painter.setPen(QPen(Qt::yellow,2));
            painter.drawLine(ui->graph_group[i]->x()-1,ui->graph_group[i]->y()+ui->graph_group[i]->height()/2,ui->graph_group[i]->x()-30,ui->graph_group[i]->y()+ui->graph_group[i]->height()/2);
            //qDebug()<< this->moudle_graph->group.size();
            if(this->moudle_graph->group[i]->grapg_flag==true&&this->moudle_graph->group[i]->graph_value.size()!=0)
            {               
                //for(int j=0;j<this->moudle_graph->group[i]->graph_value.size();j++)
                if(this->ui->start_drag!=true)
                {
                    time.time_drag=time.simu_count;
                    this->time.time_temp=this->time.simu_count;
                }
                int x_pos=0;
                for(int j=(time.time_drag-((ui->x_count-1)*ui->x_interval_point))>=0?(time.time_drag-((ui->x_count-1)*ui->x_interval_point)):0;j<time.time_drag;j++)
                {                    
                    //qDebug()<<200-int(this->moudle_graph->group[i]->graph_value[j]);
                    if(this->ui->start_drag!=true)
                    {
                        if(x_pos==0)
                        {
                            painter.drawLine(ui->x_start+ui->x_axia_precision*x_pos,ui->y_start-int(this->moudle_graph->group[i]->graph_value[j]/this->value_limit*this->ui->y_axis_length),ui->x_start+ui->x_axia_precision*x_pos,ui->y_start-int(this->moudle_graph->group[i]->graph_value[j]/this->value_limit*this->ui->y_axis_length+1));
                        }
                        else
                            painter.drawLine(ui->x_start+ui->x_axia_precision*x_pos,ui->y_start-int(this->moudle_graph->group[i]->graph_value[j]/this->value_limit*this->ui->y_axis_length),ui->x_start+ui->x_axia_precision*(x_pos-1),ui->y_start-int(this->moudle_graph->group[i]->graph_value[j-1]/this->value_limit*this->ui->y_axis_length+1));

                    }
                    else
                    {
                        if(x_pos==0)
                        {
                            painter.drawLine(ui->x_start+ui->x_axia_precision*x_pos,ui->y_start-int(this->moudle_graph->group[i]->graph_value[j]/this->value_limit*this->ui->y_axis_length),ui->x_start+ui->x_axia_precision*x_pos,ui->y_start-int(this->moudle_graph->group[i]->graph_value[j]/this->value_limit*this->ui->y_axis_length+1));
                        }
                        else
                            painter.drawLine(ui->x_start+ui->x_axia_precision*x_pos,ui->y_start-int(this->moudle_graph->group[i]->graph_value[j]/this->value_limit*this->ui->y_axis_length),ui->x_start+ui->x_axia_precision*(x_pos-1),ui->y_start-int(this->moudle_graph->group[i]->graph_value[j-1]/this->value_limit*this->ui->y_axis_length+1));
                    }
                    x_pos++;
                    //painter.drawLine(10,100,100,100);
                }


                //当前时刻value显示及动画
                if(this->check_focus()==-1||this->check_focus()>=this->moudle_graph->group[i]->graph_value.size())
                {
                    this->ui->current_value[i]->setText("");
                }
                else
                {
                    painter.setPen(Qt::PenStyle::DashLine);
                    int start=(time.time_drag-((ui->x_count-1)*ui->x_interval_point))>=0?(time.time_drag-((ui->x_count-1)*ui->x_interval_point)):0;
                    this->ui->current_value[i]->setText(QString::number(this->moudle_graph->group[i]->graph_value[start+this->check_focus()]));
                   // qDebug()<<this->moudle_graph->group[i]->graph_value[start+this->check_focus()];

                    painter.drawLine(ui->x_start+ui->x_axia_precision*this->check_focus(),ui->y_start-ui->y_axis_length,ui->x_start+ui->x_axia_precision*this->check_focus(),ui->y_start+ui->y_axis_length);
                    painter.drawLine(ui->x_start,ui->y_start-int(this->moudle_graph->group[i]->graph_value[start+this->check_focus()]/this->value_limit*this->ui->y_axis_length),ui->x_start+ui->x_length,ui->y_start-int(this->moudle_graph->group[i]->graph_value[start+this->check_focus()]/this->value_limit*this->ui->y_axis_length));
                }
            }


        }        
        if(this->moudle_graph->group.size()!=0)
        {
            //qDebug()<<moudle_graph->group[0]->graph_value.size();
            painter.setPen(QPen(Qt::black,2));
            if(this->moudle_graph->group[0]->graph_value.size()<((ui->x_count-1)*ui->x_interval_point))
            {
                int temp=0;
                for(int j=0;j<this->moudle_graph->group[0]->graph_value.size();j++)
                {
                    this->time_label[j/ui->x_interval_point]->setText(QString::number(j/ui->x_interval_point*ui->x_interval_point*this->time.simu_step));
                    temp=j/ui->x_interval_point;
                }
                for(int i=temp+1;i<this->time_label.size();i++)
                    this->time_label[i]->setText("");
            }
            else
            {

                for(int j=0;j<ui->x_count;j++)
                {
                    if(this->ui->start_drag!=true)
                        this->time_label[j]->setText(QString::number((this->time.simu_count-((ui->x_count-1)*ui->x_interval_point)+ui->x_interval_point*j)*this->time.simu_step));
                    else
                        this->time_label[j]->setText(QString::number((this->time.time_drag-((ui->x_count-1)*ui->x_interval_point)+ui->x_interval_point*j)*this->time.simu_step));
                }

            }
            for(int j=0;j<ui->x_count;j++)
            {
                painter.drawLine(ui->x_start+j*ui->x_interval_point*ui->x_axia_precision,ui->y_start,ui->x_start+j*ui->x_interval_point*ui->x_axia_precision,ui->y_start+3);
            }
            for(int i=0;i<this->ui->y_count;i++)
            {
                this->value_label[i*2]->setText(QString::number(this->value_limit/this->ui->y_count*(i+1)));
                painter.drawLine(this->ui->x_start,this->ui->y_start-this->ui->y_axis_length/this->ui->y_count*(i+1),this->ui->x_start-3,this->ui->y_start-this->ui->y_axis_length/this->ui->y_count*(i+1));
                this->value_label[i*2+1]->setText(QString::number(-1*this->value_limit/this->ui->y_count*(i+1)));
                painter.drawLine(this->ui->x_start,this->ui->y_start+this->ui->y_axis_length/this->ui->y_count*(i+1),this->ui->x_start-3,this->ui->y_start+this->ui->y_axis_length/this->ui->y_count*(i+1));
            }
        }
        painter.drawLine(this->ui->x_start,this->ui->y_start,this->ui->x_start+this->ui->x_length,this->ui->y_start);
        painter.drawLine(this->ui->x_start+this->ui->x_length+3,this->ui->y_start,this->ui->x_start+this->ui->x_length,this->ui->y_start-3);
        painter.drawLine(this->ui->x_start+this->ui->x_length+3,this->ui->y_start,this->ui->x_start+this->ui->x_length,this->ui->y_start+3);
        painter.drawLine(this->ui->x_start,this->ui->y_start-this->ui->y_axis_length-this->ui->y_invalid,this->ui->x_start+this->ui->x_length,this->ui->y_start-this->ui->y_axis_length-this->ui->y_invalid);
        painter.drawLine(this->ui->x_start,this->ui->y_start+this->ui->y_axis_length+this->ui->y_invalid,this->ui->x_start+this->ui->x_length,this->ui->y_start+this->ui->y_axis_length+this->ui->y_invalid);

        painter.drawLine(this->ui->x_start+this->ui->x_length+3,this->ui->y_start+this->ui->y_invalid+this->ui->y_axis_length,this->ui->x_start+this->ui->x_length+3,this->ui->y_start-this->ui->y_invalid-this->ui->y_axis_length);
        painter.drawLine(this->ui->x_start,this->ui->y_start-this->ui->y_invalid-this->ui->y_axis_length,this->ui->x_start,this->ui->y_start+this->ui->y_invalid+this->ui->y_axis_length);
        painter.drawLine(this->ui->x_start,this->ui->y_start-this->ui->y_invalid-this->ui->y_axis_length,this->ui->x_start-3,this->ui->y_start-this->ui->y_axis_length-this->ui->y_invalid+3);
        painter.drawLine(this->ui->x_start,this->ui->y_start-this->ui->y_invalid-this->ui->y_axis_length,this->ui->x_start+3,this->ui->y_start-this->ui->y_axis_length-this->ui->y_invalid+3);

        //this->draw_point_flag=false;
      //  }
        //qDebug()<<QDateTime::currentDateTime()<<3;
        if(this->time.simu_count<=this->time.simu_count_max)
        {
            //mDataTimer.start(int(time.simu_step*1000-time_before.msecsTo(QDateTime::currentDateTime().time())));//下次仿真时间为仿真步距减去上次程序运行时间与绘图时间
            //mDataTimer.start(int(time.simu_step*1000));
            //this->draw_point_flag=false;
            //qDebug()<<QDateTime::currentDateTime()<<2;
        }
        else
        {
            //qDebug()<<QDateTime::currentDateTime();//计算实际仿真时间与设定仿真时间差
        }
    }

}

void Run_Simu::moudle_relation()
{
    //qDebug()<<QThread::currentThreadId();
    relation_init();
    struct moudle_relation moudlee;

    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        for(int m=0;m<moudle->output.size();m++)
        {
            moudle_param* param=moudle->output[m];
            for(int n=0;n<param->connect_line.size();n++)
            {
                Line* linee=param->connect_line[n];
                for(int j=0;j<linee->endbutton.size();j++)
                {
                    moudlee.moudle=this->simulation_group->findwithbutton(linee->endbutton[j]);
                    moudlee.index=linee->endindex[j];
                    moudle->output[m]->next.push_back(moudlee);
                }
            }
        }
    }    
    detect_loop();//闭环检测
    clear_process_value();
    form();
    form_graph();
    qDebug()<<check_signal();//信号完整性检测
    for(int i=0;i<this->moudle_graph->group.size();i++)
    {
        this->save_complete.push_back(false);
        this->url.push_back("");
    }//图表保存标志位初始化

/*    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        for(int m=0;m<moudle->output.size();m++)
        {
            moudle_param* param=moudle->output[m];
            for(int n=0;n<param->next.size();n++)
                qDebug()<<param->next[n].moudle->id;
            qDebug()<<"a";
        }
        qDebug()<<"a"<<"a";
    }
    */
}
bool Run_Simu::check_signal()
{
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        for(int j=0;j<moudle->input_size;j++)//检查模块输入引脚是否信号完整
        {
            moudle_param* param=moudle->input[j];
            if(param->connect_line.size()!=0)
            {
                for(int m=0;m<param->connect_line.size();m++)
                {
                    if(param->connect_line[m]->startbutton.size()==0)
                    {
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }
        }

        for(int j=0;j<moudle->output_size;j++)//检查模块输出引脚是否信号完整
        {
            moudle_param* param=moudle->output[j];
            if(param->connect_line.size()!=0)
            {
                for(int m=0;m<param->connect_line.size();m++)
                {
                    if(param->connect_line[m]->endbutton.size()==0)
                    {
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}
void Run_Simu::relation_init()
{
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        for(int m=0;m<moudle->output.size();m++)
        {
            int count=moudle->output[m]->next.size();
            for(int n=0;n<count;n++)
                moudle->output[m]->next.removeAt(0);
        }
        int count=moudle->input_flag.size();
        for(int i=0;i<count;i++)
        {
            moudle->input_flag.removeAt(0);
            moudle->input_number.removeAt(0);
            moudle->input_loop.removeAt(0);
        }
        count=moudle->output_flag.size();
        for(int i=0;i<count;i++)
        {
            moudle->output_flag.removeAt(0);
            moudle->output_number.removeAt(0);
        }
        for(int i=0;i<moudle->input_size;i++)
        {
            moudle->input_flag.push_back(false);
            moudle->input_number.push_back(0);
            moudle->input_loop.push_back(false);
        }
        for(int i=0;i<moudle->output_size;i++)
        {
            moudle->output_flag.push_back(false);
            moudle->output_number.push_back(0);
        }
        moudle->loop_flag=false;
    }
}
void Run_Simu::detect_loop()
{
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        for(int j=0;j<this->simulation_group->group.size();j++)
        {
            this->simulation_group->group[j]->loop_flag=false;
        }
        loop_check(this->simulation_group->group[i],0);
    }

    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        for(int j=0;j<moudle->input_loop.size();j++)
            if(moudle->input_loop[j]==true)
                qDebug()<<i<<" "<<j;
    }
}
void Run_Simu::loop_check(Simulation_Moudle* moudle,int index)
{
    if(moudle->loop_flag)
    {
        moudle->input_loop[index]=true;
        return;
    }

    moudle->loop_flag=true;
    for(int m=0;m<moudle->output.size();m++)
    {
        moudle_param* param=moudle->output[m];
        for(int n=0;n<param->next.size();n++)
        {
            loop_check(param->next[n].moudle,param->next[n].index);
        }
    }
}
void Run_Simu::realtime_simulation()
{
    graph_button();
    qDebug()<<QDateTime::currentDateTime();//计算实际仿真时间与设定仿真时间差
    mDataTimer.start(10);
}
void Run_Simu::output_generator(Simulation_Moudle* moudle,int time)
{
    for(int i=0;i<moudle->output_size;i++)
    {
        if(moudle->index==0)//斜坡
        {
            moudle->output_number[i]=moudle->param[0]*time*this->time.simu_step;
        }
        else if(moudle->index==1)//阶跃
        {
            moudle->output_number[i]=moudle->param[0];
        }
        else if(moudle->index==2)//正弦
        {
            moudle->output_number[i]=moudle->param[0]*sin(time*moudle->param[1]*this->time.simu_step);
        }
        else if(moudle->index==3)//方波
        {
            if(this->time.simu_count%int(moudle->param[0]/2/this->time.simu_step)==0)
            {
                if(int(moudle->param[2])==1)
                {
                    moudle->param[2]=0;
                    moudle->output_number[i]=moudle->param[1];
                }
                else
                {
                    moudle->param[2]=1;
                    moudle->output_number[i]=0;
                }
            }
        }
        else if(moudle->index==4)//三角波
        {
            double bias=(moudle->param[0]/this->time.simu_step)/(moudle->param[0]/this->time.simu_step-1)-1;
            moudle->output_number[i]=double(this->time.simu_count%int(moudle->param[0]/this->time.simu_step))/int(moudle->param[0]/this->time.simu_step)*((moudle->param[1]-moudle->param[2])*(1+bias))+moudle->param[2];
        }
        else if(moudle->index==5)//分段折线波
        {
            if(int(moudle->param[2])<=(moudle->time_sequence.size()-1)&&this->time.simu_count>=moudle->time_sequence[int(moudle->param[2])]/this->time.simu_step)
            {
                if(moudle->param[2]<=moudle->value_sequence.size()-1)
                    moudle->output_number[i]=moudle->value_sequence[int(moudle->param[2])];
                else
                    moudle->output_number[i]=0;
                moudle->param[2]+=1;
            }
            else
            {
                moudle->output_number[i]=0;
            }
        }
        else if(moudle->index==6)//分段矩形波
        {

        }
        else if(moudle->index==7)//随机信号
        {
            moudle->output_number[i]=double(rand())/RAND_MAX*(moudle->param[1]-moudle->param[0])+moudle->param[0];
        }
        //moudle->output_number[i]=moudle->param[2]*sin(time*0.01);
        moudle->graph_value.push_back(moudle->output_number[i]);
    }
}
void Run_Simu::run_socket(Simulation_Moudle* moudle)
{
    if(moudle->bind_interface->front<moudle->bind_interface->receive_data.size())
    {
        for(int i=0;i<moudle->output_number.size();i++)
            moudle->output_number[i]=moudle->bind_interface->receive_data[moudle->bind_interface->front];
        run_simulation(moudle);
        moudle->bind_interface->front++;
    }
}
void Run_Simu::run_simulation(Simulation_Moudle* moudle)
{
        for(int j=0;j<moudle->output.size();j++)
        {            
            moudle_param* param=moudle->output[j];
            for(int m=0;m<param->next.size();m++)
            {
                if(check_input(param->next[m].moudle,param->next[m].index,moudle->output_number[j]))
                {
                    run_simulation(param->next[m].moudle);
                }
            }
        }
}
bool Run_Simu::check_input(Simulation_Moudle* moudle,int index,double value)
{
    bool flag=true;
    moudle->input_flag[index]=true;
    moudle->input_number[index]=value;
    for(int i=0;i<moudle->input_flag.size();i++)
    {
        if(moudle->input_flag[i]!=true&&moudle->input_loop[i]!=true)
        {
            flag=false;
            break;
        }
    }
    if(flag)
    {       
        for(int i=0;i<moudle->input_flag.size();i++)
            moudle->input_flag[i]=false;
        calculation(moudle);
        return true;
    }
    return false;

}
void Run_Simu::calculation(Simulation_Moudle* moudle)
{    
    double value=0;
    for(int i=0;i<moudle->input_number.size();i++)
    {
        value+=moudle->input_number[i];
    }
    if(moudle->output_number.size()!=0)
    {
        if(moudle->index==12)//惯性
        {
            double k1=0,k2=0,k3=0,k4=0;
            for(int i=0;i<moudle->output_number.size();i++)
            {
                //y'=(x-y)/k
                //moudle->output_number[i]=value;
                //四阶龙格-库塔算法
                /*
                if(this->time.simu_count==0)
                {
                    moudle->output_number[0]=0;
                }
                else
                {
                    k1=(this->time.simu_step*this->time.simu_count-moudle->output_number[0])/moudle->param[1];
                    k2=(this->time.simu_step*this->time.simu_count+0.5*this->time.simu_step-(moudle->output_number[0]+k1*this->time.simu_step/2))/moudle->param[1];
                    k3=(this->time.simu_step*this->time.simu_count+0.5*this->time.simu_step-(moudle->output_number[0]+k2*this->time.simu_step/2))/moudle->param[1];
                    k4=(this->time.simu_step*this->time.simu_count+this->time.simu_step-(moudle->output_number[0]+k3*this->time.simu_step))/moudle->param[1];
                    moudle->output_number[0]=moudle->output_number[0]+this->time.simu_step*(k1+2*k2+2*k3+k4)/6;
                }
                */

                //改进欧拉算法
                double temp;
                temp=moudle->output_number[0]/moudle->param[0];
                moudle->output_number[0]=temp+this->time.simu_step*(moudle->param[2]-temp)/moudle->param[1];
                moudle->output_number[0]=temp+this->time.simu_step/2*(moudle->param[2]-temp+value-moudle->output_number[0])/moudle->param[1];
                //moudle->output_number[i]=(moudle->param[1]*moudle->output_number[i]+moudle->param[0]*value)/(1+moudle->param[1]);
               // moudle->output_number[i]=value*(1-exp(-1/moudle->param[1]*this->time.simu_step*this->time.simu_count));
              /*  moudle->process_value.push_back(moudle->output_number[0]);
                if(moudle->process_value.size()>=101)
                {
                    moudle->process_value.removeAt(0);
                }
                //QThread::sleep(1);
                //Sleep(1000);
                */           
                moudle->param[2]=value;//使用前需要清零
                //qDebug()<<moudle->output_number[0]<<moudle->id;
            }
            moudle->output_number[0]=moudle->output_number[0]*moudle->param[0];
        }
        else if(moudle->index==13)//n阶惯性
        {
            for(int i=0;i<moudle->output_number.size();i++)
            {
                for(int j=0;j<int(moudle->param[2]);j++)
                {
                    //改进欧拉算法
                    moudle->output_number[0]=moudle->temp[j]+this->time.simu_step*(moudle->param_temp[j]-moudle->temp[j])/moudle->param[1];
                    moudle->output_number[0]=moudle->temp[j]+this->time.simu_step/2*(moudle->param_temp[j]-moudle->temp[j]+value-moudle->output_number[0])/moudle->param[1];
                    moudle->param_temp[j]=value;//使用前需要清零
                    moudle->temp[j]=moudle->output_number[0];
                    value=moudle->output_number[0];
                }
                moudle->output_number[0]=moudle->output_number[0]*moudle->param[0];
            }
        }
        else if(moudle->index==8)//常数
        {
            moudle->output_number[0]=moudle->param[0]*value;
        }
        else if(moudle->index==9)//延时
        {
            moudle->process_value.push_back(value);
            if(moudle->process_value.size()>=moudle->param[0]/this->time.simu_step)
            {
                moudle->output_number[0]=moudle->process_value[0];
                moudle->process_value.removeAt(0);
            }
            else
            {
                moudle->output_number[0]=0;
            }
        }
        else if(moudle->index==10)//积分
        {
            moudle->output_number[0]+=value*moudle->param[0]*time.simu_step;
        }
        else if(moudle->index==11)//微分
        {
            double temp=value;
            moudle->output_number[0]=(value-moudle->param[0])/time.simu_step;
            moudle->param[0]=temp;
        }
        else if(moudle->index==19)//倒数
        {
            if(int(value)!=0)
                moudle->output_number[0]=1/value;
            else
                moudle->output_number[0]=0;
        }
        else if(moudle->index==20)//正三角
        {
            if(int(moudle->param[0])==0)
            {
                moudle->output_number[0]=sin(value);
            }
            else if(int(moudle->param[0])==1)
                moudle->output_number[0]=cos(value);
            else if(int(moudle->param[0])==2)
                moudle->output_number[0]=tan(value);
        }
        else if(moudle->index==21)//反三角
        {
            if(int(moudle->param[0])==0)
                moudle->output_number[0]=asin(value);
            else if(int(moudle->param[0])==1)
                moudle->output_number[0]=acos(value);
            else if(int(moudle->param[0])==2)
                moudle->output_number[0]=atan(value);
        }
        else if(moudle->index==22)//绝对值
        {
            moudle->output_number[0]=abs(value);
        }
        else if(moudle->index==23)//绝符号
        {
            moudle->output_number[0]=value>0?1:(value==0.0?0:-1);
        }
        else if(moudle->index==24)//自然对数 e
        {
            if(value>0)
                moudle->output_number[0]=log(value);
            else
                moudle->output_number[0]=value;
        }
        else if(moudle->index==25)//常用对数 10
        {
            if(value>0)
                moudle->output_number[0]=log10(value);
            else
                moudle->output_number[0]=value;
        }
        else if(moudle->index==26)//指数e
        {
            moudle->output_number[0]=exp(value);
        }
        else if(moudle->index==27)//幂函数
        {
            moudle->output_number[0]=pow(value,int(moudle->param[0]));
        }
        else if(moudle->index==28)//开方
        {
            if(value>=0)
                moudle->output_number[0]=sqrt(value);
            else
                moudle->output_number[0]=value;
        }
        else if(moudle->index==29)//加法器
        {
            moudle->output_number[0]=value;
        }
        else if(moudle->index==30)//乘法器
        {
            if(int(moudle->param[0])==0)
                moudle->output_number[0]=moudle->input_number[0]*moudle->input_number[1];
            else if(int(moudle->param[0])==1&&int(moudle->input_number[1])!=0)
            {
                moudle->output_number[0]=moudle->input_number[0]/moudle->input_number[1];
            }

        }
        else if(moudle->index==31)//比例偏置 kx+b
        {
            moudle->output_number[0]=moudle->param[0]*value+moudle->param[1];
        }
        else if(moudle->index==32)//逻辑运算> <
        {
            if(int(moudle->param[0])==0)
                moudle->output_number[0]=(moudle->input_number[0]>moudle->input_number[1]);
            else if(int(moudle->param[0])==1)
                moudle->output_number[0]=(moudle->input_number[0]<moudle->input_number[1]);
            else if(int(moudle->param[0])==2)
                moudle->output_number[0]=(int(moudle->input_number[0])==int(moudle->input_number[1]));
            else if(int(moudle->param[0])==3)
                moudle->output_number[0]=(int(moudle->input_number[0])&&int(moudle->input_number[1]));
            else if(int(moudle->param[0])==4)
                moudle->output_number[0]=(int(moudle->input_number[0])||int(moudle->input_number[1]));
            else if(int(moudle->param[0])==5)
            {
                if(int(moudle->input_number[0])!=0)
                    moudle->output_number[0]=0;
                else
                    moudle->output_number[0]=1;
            }
        }
        else if(moudle->index==33)//逻辑& | ~
        {
            if(int(moudle->param[0])==0)
                moudle->output_number[0]=(int(moudle->input_number[0])&int(moudle->input_number[1]));
            else if(int(moudle->param[0])==1)
                moudle->output_number[0]=(int(moudle->input_number[0])|int(moudle->input_number[1]));
            else if(int(moudle->param[0])==2)
                moudle->output_number[0]=(~int(moudle->input_number[0]));
        }
        else if(moudle->index==34)//取最值
        {
            if(int(moudle->param[1])==0) //最大值
            {
                double max=moudle->input_number[0];
                for(int i=1;i<moudle->input_number.size();i++)
                {
                    if(max<moudle->input_number[i])
                        max=moudle->input_number[i];
                }
                moudle->output_number[0]=max;

            }
            else if(int(moudle->param[1])==1) //MIN
            {
                double min=moudle->input_number[0];
                for(int i=1;i<moudle->input_number.size();i++)
                {
                    if(min>moudle->input_number[i])
                        min=moudle->input_number[i];
                }
                moudle->output_number[0]=min;
            }
        }
        else if(moudle->index==35)//出多选一
        {
            if(int(moudle->input_number[1])<moudle->output_size)
            {
                for(int i=0;i<moudle->output_size;i++)
                {
                    if(i==int(moudle->input_number[1]))
                        moudle->output_number[i]=moudle->input_number[0];
                    else
                        moudle->output_number[i]=0;
                }
            }
            else
            {
                for(int i=0;i<moudle->output_size;i++)
                {
                    moudle->output_number[i]=0;
                }

            }
        }
        else if(moudle->index==36)//入多选一
        {
            if(int(moudle->input_number[moudle->input_size-1])<moudle->input_size-1)
                moudle->output_number[0]=moudle->input_number[int(moudle->input_number[moudle->input_size-1])];
            else
                moudle->output_number[0]=0;
        }
        else if(moudle->index==38)//接口模块专属
        {
            for(int m=0;m<moudle->output_number.size();m++)
                moudle->output_number[m]=value;
        }
        else if(moudle->index==39)//tag_bind模块专属
        {
            for(int m=0;m<moudle->output_number.size();m++)
                moudle->output_number[m]=value;
        }

    }
    else
    {
        if(moudle->index==38)//接口模块专属
        {
            if(moudle->bind_interface->output_success==true)//是否与服务器连接成功
            {
                QString str=QString::number(value);
                moudle->bind_interface->output_socket->write(str.toLatin1(),str.length());
            }
            else
            {
                QString str=QString::number(moudle->bind_interface->output_ip[0])+"."+QString::number(moudle->bind_interface->output_ip[1])+"."+QString::number(moudle->bind_interface->output_ip[2])+"."+QString::number(moudle->bind_interface->output_ip[3]);
                parent->statr_message(moudle->name+" output reconnect from local to "+str+":"+QString::number(moudle->bind_interface->output_port),1000);
                QHostAddress ip(str);
                moudle->bind_interface->output_socket->connectToHost(ip,quint16(moudle->bind_interface->output_port));
                return;
            }
        }
        else if(moudle->index==39)//tag_bind模块专属
        {

            if(this->window_parent->sys_flag->success_flag==false)//断开连接
            {
                this->parent->statr_message("main_socket connect failed,try to reconnect",1000);
                //this->window_parent->reconnect_main_socket();
                return;
            }
            this->window_parent->sys_flag->finish_socket->output[moudle->socket_id_output]=true;
            this->window_parent->sys_flag->output_buf+=(moudle->tag_bind->output_tag+" "+QString::number(value));
            //this->window_parent->sys_flag->output_bind_count--;
            int m=0;
            for(m=0;m<this->window_parent->sys_flag->finish_socket->output.size();m++)
            {
                if(this->window_parent->sys_flag->finish_socket->output[m]==false)
                    break;
            }
            if(m==this->window_parent->sys_flag->finish_socket->output.size())//所有输出至外部接口的数据打包完成 开始发送
            {
                this->window_parent->sys_flag->output_bind_count=this->window_parent->sys_flag->output_bind.size();
                this->window_parent->sys_flag->socket_main->write(this->window_parent->sys_flag->output_buf.toLatin1(),this->window_parent->sys_flag->output_buf.size());
                this->window_parent->sys_flag->output_buf="";
                this->window_parent->send_clock->stop();
                this->window_parent->clear_finish_flag(1);
            }
        }
        else if(moudle->index==37)//图表
            moudle->graph_value.push_back(value);
        /*
        if(moudle->graph_value.size()>=101)
        {
            moudle->graph_value.removeAt(0);
        }
        */
        //qDebug()<<value;
    }

   // qDebug()<<moudle->output_number[0];
}
void Run_Simu::clear_process_value()
{
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        int count=this->simulation_group->group[i]->process_value.size();
        for(int j=0;j<count;j++)
            this->simulation_group->group[i]->process_value.removeAt(0);
    }

    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        if(this->simulation_group->group[i]->index==5)//清楚分段折线序列数据
        {
            Simulation_Moudle* moudle=this->simulation_group->group[i];//过程数据清零
            moudle->param[2]=0;
        }
        else if(this->simulation_group->group[i]->index==11)//微分环节
        {
            Simulation_Moudle* moudle=this->simulation_group->group[i];//过程数据清零
            moudle->param[0]=0;
        }
        else if(this->simulation_group->group[i]->index==12)//一阶惯性环节
        {
            Simulation_Moudle* moudle=this->simulation_group->group[i];//过程数据清零
            moudle->param[2]=0;
        }
        else if(this->simulation_group->group[i]->index==13||this->simulation_group->group[i]->index==14||this->simulation_group->group[i]->index==15)//高阶环节中间值清零
        {
            int count=this->simulation_group->group[i]->param_temp.size();
            for(int j=0;j<count;j++)
            {
                this->simulation_group->group[i]->param_temp.removeAt(0);
                this->simulation_group->group[i]->temp.removeAt(0);
            }
            for(int j=0;j<this->simulation_group->group[i]->param[2];j++)
            {
                this->simulation_group->group[i]->param_temp.push_back(0);
                this->simulation_group->group[i]->temp.push_back(0);
            }

        }
        else if(this->simulation_group->group[i]->index==38)//接口模块专属
        {
            this->simulation_group->group[i]->bind_interface->front=0;
            this->simulation_group->group[i]->bind_interface->receive_data.clear();
        }
    }
}
void Run_Simu::form()
{
    delete this->moudle_generator;
    this->moudle_generator=new moudel_group();
    for(int i=0;i<this->simulation_group->group.size();i++)
        if(this->simulation_group->group[i]->index==0||this->simulation_group->group[i]->index==1||this->simulation_group->group[i]->index==2||this->simulation_group->group[i]->index==3||this->simulation_group->group[i]->index==4||this->simulation_group->group[i]->index==5||this->simulation_group->group[i]->index==6||this->simulation_group->group[i]->index==7)
            this->moudle_generator->group.push_back(this->simulation_group->group[i]);
    for(int i=0;i<this->moudle_generator->group.size();i++)
    {
        int count=this->moudle_generator->group[i]->graph_value.size();
        for(int j=0;j<count;j++)
            this->moudle_generator->group[i]->graph_value.removeAt(0);//原始信号数据清零
    }    
    moudle_socket->group.clear();//输入实物模块
    for(int i=0;i<this->simulation_group->group.size();i++)
        if(this->simulation_group->group[i]->index==38&&this->simulation_group->group[i]->bind_interface->input_flag==true&&this->simulation_group->group[i]->bind_interface->output_flag==false)//输入接入实物，输出为虚拟仿真
            this->moudle_socket->group.push_back(this->simulation_group->group[i]);

}
void Run_Simu::form_graph()
{
    delete this->moudle_graph;
    this->moudle_graph=new moudel_group();
    for(int i=0;i<this->simulation_group->group.size();i++)
        if(this->simulation_group->group[i]->index==37)
            this->moudle_graph->group.push_back(this->simulation_group->group[i]);
    for(int i=0;i<this->moudle_graph->group.size();i++)
    {
        int count=this->moudle_graph->group[i]->graph_value.size();
        for(int j=0;j<count;j++)
            this->moudle_graph->group[i]->graph_value.removeAt(0);//仿真数据清零
    }

}
void Run_Simu::graph_button()
{
    QPushButton* button;
    QLabel* label;
    int count=this->ui->graph_group.size();
    for(int i=0;i<count;i++)
    {
        delete this->ui->graph_group[0];
        this->ui->graph_group.removeAt(0);
        this->ui->current_value.removeAt(0);
    }
    for(int i=0;i<this->moudle_graph->group.size();i++)
    {
        this->moudle_graph->group[i]->grapg_flag=true;
        button=new QPushButton(this);
        button->setObjectName("&plot"+QString::number(i));
        button->setText(this->moudle_graph->group[i]->name);
        button->setGeometry(this->width()-160,50*i,50,30);
        button->setVisible(true);
        connect(button, &QAbstractButton::clicked, this, &Run_Simu::change);
        this->ui->graph_group.push_back(button);

        label=new QLabel(this);
        label->setGeometry(button->x()+button->width(),button->y(),button->width(),button->height());
        label->setVisible(true);
        this->ui->current_value.push_back(label);
    }
}
void Run_Simu::get_max(int start,int end)
{
    this->value_min=0;
    this->value_max=0;
    this->value_limit=0;
    for(int i=0;i<this->moudle_graph->group.size();i++)
    {
        Simulation_Moudle* moudle=this->moudle_graph->group[i];
        if(moudle->grapg_flag==true&&moudle->graph_value.size()!=0)
        {
            for(int j=start;j<end;j++)
            {
                double value=moudle->graph_value[j];
                if(value<this->value_min)
                {
                    this->value_min=value;
                }
                if(value>this->value_max)
                    this->value_max=value;
                //qDebug()<<this->value_limit;
            }
        }
    }
    if(qAbs(this->value_min)>qAbs(this->value_max))
    {
        this->value_limit=qAbs(this->value_min);
    }
    else
    {
        this->value_limit=qAbs(this->value_max);
    }
}
void Run_Simu::loadmindindow(QMdiSubWindow* midwindow)
{
    this->midwindow=midwindow;
    this->midwindow->resize(ui->x_axia_precision*ui->x_interval_point*(ui->x_count-1)+200+ui->x_start,400);
    this->resize(ui->x_axia_precision*ui->x_interval_point*(ui->x_count-1)+200+ui->x_start,400);
}
void Run_Simu::update_size()//坐标系自适应窗口大小
{
    this->resize(this->midwindow->size().width(),this->midwindow->size().height()-60);
    //if((this->width()-200-this->ui->x_start)%(ui->x_count-1)!=0)//确保x轴分度为整数
    //    return;
    //qDebug()<<11;
    //if((this->width()-200-this->ui->x_start)/(ui->x_count-1)%this->ui->x_interval_point!=0)
    //    return;
    this->ui->y_start=this->height()/2;
    //x_axia_precision*x_interval_point*(x_count-1)
    //this->ui->x_length=this->ui->x_axia_precision*this->ui->x_interval_point*(this->ui->x_count-1);
    this->ui->y_axis_length=this->height()/2-80;
    this->ui->x_axia_precision=(this->width()-200-this->ui->x_start)/(ui->x_count-1)/ui->x_interval_point;
    if(this->ui->x_axia_precision==0)
    {
        this->ui->x_axia_precision=1;
        ui->x_interval_point=(this->width()-200-this->ui->x_start)/(ui->x_count-1);
    }
    this->ui->x_length=this->ui->x_axia_precision*this->ui->x_interval_point*(this->ui->x_count-1);
    this->ui->x_interview_length=this->ui->x_length/(ui->x_count-1);
    for(int i=0;i<ui->x_count;i++)
    {
        time_label[i]->setGeometry(ui->x_start+ui->x_axia_precision*ui->x_interval_point*i,ui->y_start+2,ui->x_axia_precision*ui->x_interval_point-3,20);
    }

    for(int i=0;i<this->ui->y_count;i++)
    {
        value_label[i*2]->setGeometry(ui->x_start-40,ui->y_start-12-ui->y_axis_length/ui->y_count*(i+1),35,20);
        value_label[i*2+1]->setGeometry(ui->x_start-40,ui->y_start-12+ui->y_axis_length/ui->y_count*(i+1),35,20);
    }
    for(int i=0;i<this->moudle_graph->group.size();i++)
    {
        this->ui->graph_group[i]->setGeometry(this->width()-160,50*i+40,50,30);
        this->ui->current_value[i]->setGeometry(this->ui->graph_group[i]->x()+this->ui->graph_group[i]->width()+10,this->ui->graph_group[i]->y(),this->ui->graph_group[i]->width(),this->ui->graph_group[i]->height());
    }
    start_stop->setGeometry(this->width()-160,0,50,30);//设定仿真按钮位置
}
int Run_Simu::check_focus()
{
    QRect rect(ui->x_start,ui->y_start-ui->y_axis_length,ui->x_length,ui->y_axis_length*2);
    if(rect.contains(this->mapFromGlobal(QCursor::pos())))
    {
        return (this->mapFromGlobal(QCursor::pos()).x()-this->ui->x_start)/this->ui->x_axia_precision;
    }
    return -1;
}
void Run_Simu::check_data()
{
    //适用与半实物仿真时，如果网络输出传输周期较长（低于仿真步距），就是需要将中间时间差内的数据清零
    for(int i=0;i<this->moudle_graph->group.size();i++)
    {
        Simulation_Moudle* moudle=this->moudle_graph->group[i];
        if(moudle->graph_value.size()<this->time.simu_count)
        {
            if(this->time.simu_count==1)
            {
                moudle->graph_value.push_back(0);
            }
            else
            {
                int count=moudle->graph_value.size();
                for(int j=0;j<this->time.simu_count-count;j++)
                {
                    moudle->graph_value.push_back(moudle->graph_value[moudle->graph_value.size()-1]);
                }
            }
            //qDebug()<<moudle->graph_value.size()<<time.simu_count;
        }
    }
}
void Run_Simu::set_shadow(QWidget *widget)
{
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(5, 5);
    shadow_effect->setColor(QColor(50, 50, 50));
    shadow_effect->setBlurRadius(8);

    widget->setGraphicsEffect(shadow_effect);

}
void Run_Simu::remove_shadow(QWidget *widget)
{
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(5, 5);
    shadow_effect->setColor(QColor(255, 255, 255));
    shadow_effect->setBlurRadius(8);

    widget->setGraphicsEffect(shadow_effect);

}
void Run_Simu::clear_save_flag()
{
    for(int i=0;i<this->save_complete.size();i++)
        this->save_complete[i]=false;
}
void Run_Simu::save_graph_date()
{
    int count=this->graph_name.size();
    for(int i=0;i<count;i++)
    {
        this->graph_name.removeAt(0);
    }
    for(int i=0;i<this->moudle_graph->group.size();i++)
    {
        this->graph_name.push_back(this->moudle_graph->group[i]->name);
    }
    if(this->real_flag==false&&this->run_stop_state)
        this->mDataTimer.stop();//关闭仿真
    this->parent->save_graph_date();
    if(this->real_flag==false&&this->run_stop_state)
        this->mDataTimer.start(10);//开启仿真
}
void Run_Simu::save_data(QFile* file,int index)
{
    //QFile* file=new QFile("data.txt");
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"error";
        return;
    }
    //仿真数据写入格式
    //仿真数据大小
    //仿真步距
    //仿真数据
    file->write(QByteArray::number(this->moudle_graph->group[index]->graph_value.size()));
    file->write("\n");
    file->write(QByteArray::number(this->time.simu_step));
    file->write("\n");
    for(int i=0;i<this->moudle_graph->group[index]->graph_value.size();i++)
    {
        file->write(QByteArray::number(this->moudle_graph->group[index]->graph_value[i]));
        file->write("\n");
    }
    file->close();
}
