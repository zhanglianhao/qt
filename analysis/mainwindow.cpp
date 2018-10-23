#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "custombuttongroup.h"
#include<QGraphicsDropShadowEffect>
#include<QTimer>
#include "analysis.h"
#include <math.h>
#include "run_simu.h"
MainWindow::MainWindow(QWidget* parent):QMainWindow(parent)
{
    init();
}

MainWindow::~MainWindow()
{
}
void MainWindow::init()
{
    MainWindow::param_init();
    MainWindow::image();
    MainWindow::pattern_init();
    MainWindow::time_init();
}
void MainWindow::time_init()
{
    connect(this->rece_clock, SIGNAL(timeout()), this, SLOT(rece_Timeout()));
    connect(this->send_clock, SIGNAL(timeout()), this, SLOT(send_Timeout()));
}
void MainWindow::param_init()
{   //qDebug()<<this->metaObject()->className();//输出类名

    //信号
    this->sys_flag->param[0]=1;//线性信号源
    this->sys_flag->param[1]=1;//阶跃信号
    this->sys_flag->param[2]=2;//正弦信号
    this->sys_flag->param[3]=3;//方波信号
    this->sys_flag->param[4]=3;//三角波信号 波峰波谷波长
    this->sys_flag->param[5]=3;//分段折线波信号
    this->sys_flag->param[6]=2;//分段矩形波信号
    this->sys_flag->param[7]=2;//随机信号 信号上下限
    //对象
    this->sys_flag->param[8]=1;//常数
    this->sys_flag->param[9]=1;//延时环节
    this->sys_flag->param[10]=2;//积分
    this->sys_flag->param[11]=1;//微分
    this->sys_flag->param[12]=3;//一阶惯性
    this->sys_flag->param[13]=4;//n阶惯性
    this->sys_flag->param[14]=1;//自定义参数环节
    this->sys_flag->param[15]=2;

    //函数
    this->sys_flag->param[19]=0;//倒数
    this->sys_flag->param[20]=1;//正三角函数
    this->sys_flag->param[21]=1;//反三角函数
    this->sys_flag->param[22]=0;//绝对值函数
    this->sys_flag->param[23]=0;//取符号
    this->sys_flag->param[24]=0;//自然对数 e
    this->sys_flag->param[25]=0;//常用对数 10
    this->sys_flag->param[26]=0;//指数 e
    this->sys_flag->param[27]=1;//幂函数
    this->sys_flag->param[28]=0;//开平方


    //综合
    this->sys_flag->param[29]=1;//加法器
    this->sys_flag->param[30]=1;//乘法器
    this->sys_flag->param[31]=2;//比例偏置
    this->sys_flag->param[32]=1;//逻辑函数 > < = && || !
    this->sys_flag->param[33]=1;//逻辑运算 与或非 & | ~
    this->sys_flag->param[34]=2;//取最值 Min Max
    this->sys_flag->param[35]=1;//开关一 多输出
    this->sys_flag->param[36]=1;//开关二 多输入
    this->sys_flag->param[37]=0;//图表

    this->sys_flag->param[38]=0;//AD 输入绑定 输出绑定 地址绑定
    this->sys_flag->param[39]=0;//DA 标签绑定
    this->sys_flag->param[40]=0;//DI
    this->sys_flag->param[41]=0;//DO

    this->sys_flag->name[0]="斜坡";
    this->sys_flag->name[1]="阶跃";
    this->sys_flag->name[2]="正弦";
    this->sys_flag->name[3]="方波";//内部绘制
    this->sys_flag->name[4]="Triangle";
    this->sys_flag->name[5]="custom";
    this->sys_flag->name[7]="随机信号";
    this->sys_flag->name[8]="常数";
    this->sys_flag->name[9]="延时";
    this->sys_flag->name[10]="积分";
    this->sys_flag->name[11]="微分";
    this->sys_flag->name[12]="inertia";
    this->sys_flag->name[13]="n-inertia";
    this->sys_flag->name[14]="振荡";
    this->sys_flag->name[15]="振荡";//传递函数分母分子展开后赋值

    this->sys_flag->name[19]="倒数";
    this->sys_flag->name[20]="triangle";//内部绘制
    this->sys_flag->name[21]="Anti-triangle";//内部绘制
    this->sys_flag->name[22]="Abs";
    this->sys_flag->name[23]="SGN";
    this->sys_flag->name[24]="自然对数";
    this->sys_flag->name[25]="常用对数";
    this->sys_flag->name[26]="指数";
    this->sys_flag->name[27]="Power";
    this->sys_flag->name[28]="sqrt";

    this->sys_flag->name[29]="ADD";
    this->sys_flag->name[30]="乘法";
    this->sys_flag->name[31]="比例偏置";
    this->sys_flag->name[32]="逻辑运算";
    this->sys_flag->name[33]="单目运算";
    this->sys_flag->name[34]="Maximum";
    this->sys_flag->name[35]="出多选一";//内部绘制
    this->sys_flag->name[36]="入多选一";//内部绘制
    this->sys_flag->name[37]="图表1";

    this->sys_flag->name[38]="interface";
    this->sys_flag->name[39]="bind";
    this->sys_flag->name[40]="DI";
    this->sys_flag->name[41]="DO";
    for(int i=0;i<8;i++)
        for(int j=0;j<50;j++)
        {
            QList<int> num;
            num.push_back(i);
            num.push_back(j);
            this->sys_flag->tag_number_group.push_back(num);
            this->sys_flag->tag_group.push_back(QString::number(i)+"-"+QString::number(j));
        }
    this->sys_flag->tag_group_temp=this->sys_flag->tag_group;
}
void MainWindow::pattern_init()
{
    int scale=this->custom_menu->scale_factor;
    this->sys_flag->draw_pattern[0].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.1)),QPoint(int(scale*0.1),int(scale*0.9))));
    this->sys_flag->draw_pattern[0].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.9)),QPoint(int(scale*0.9),int(scale*0.9))));
    this->sys_flag->draw_pattern[0].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.9)),QPoint(int(scale*0.9),int(scale*0.1))));

    this->sys_flag->draw_pattern[1].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.1)),QPoint(int(scale*0.1),int(scale*0.9))));
    this->sys_flag->draw_pattern[1].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.9)),QPoint(int(scale*0.9),int(scale*0.9))));
    this->sys_flag->draw_pattern[1].push_back(point_to_pattern(QPoint(int(scale*0.2),int(scale*0.9)),QPoint(int(scale*0.2),int(scale*0.3))));
    this->sys_flag->draw_pattern[1].push_back(point_to_pattern(QPoint(int(scale*0.2),int(scale*0.3)),QPoint(int(scale*0.7),int(scale*0.3))));

    this->sys_flag->draw_pattern[3].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.1)),QPoint(int(scale*0.1),int(scale*0.9))));
    this->sys_flag->draw_pattern[3].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.9)),QPoint(int(scale*0.9),int(scale*0.9))));
    this->sys_flag->draw_pattern[3].push_back(point_to_pattern(QPoint(int(scale*0.2),int(scale*0.8)),QPoint(int(scale*0.4),int(scale*0.8))));
    this->sys_flag->draw_pattern[3].push_back(point_to_pattern(QPoint(int(scale*0.4),int(scale*0.2)),QPoint(int(scale*0.4),int(scale*0.8))));
    this->sys_flag->draw_pattern[3].push_back(point_to_pattern(QPoint(int(scale*0.4),int(scale*0.2)),QPoint(int(scale*0.6),int(scale*0.2))));
    this->sys_flag->draw_pattern[3].push_back(point_to_pattern(QPoint(int(scale*0.6),int(scale*0.2)),QPoint(int(scale*0.6),int(scale*0.8))));
    this->sys_flag->draw_pattern[3].push_back(point_to_pattern(QPoint(int(scale*0.6),int(scale*0.8)),QPoint(int(scale*0.8),int(scale*0.8))));

    this->sys_flag->draw_pattern[4].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.1)),QPoint(int(scale*0.1),int(scale*0.9))));
    this->sys_flag->draw_pattern[4].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.9)),QPoint(int(scale*0.9),int(scale*0.9))));
    this->sys_flag->draw_pattern[4].push_back(point_to_pattern(QPoint(int(scale*0.2),int(scale*0.8)),QPoint(int(scale*0.4),int(scale*0.3))));
    this->sys_flag->draw_pattern[4].push_back(point_to_pattern(QPoint(int(scale*0.4),int(scale*0.3)),QPoint(int(scale*0.4),int(scale*0.8))));
    this->sys_flag->draw_pattern[4].push_back(point_to_pattern(QPoint(int(scale*0.4),int(scale*0.8)),QPoint(int(scale*0.6),int(scale*0.3))));

    this->sys_flag->draw_pattern[5].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.1)),QPoint(int(scale*0.1),int(scale*0.9))));
    this->sys_flag->draw_pattern[5].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.9)),QPoint(int(scale*0.9),int(scale*0.9))));
    this->sys_flag->draw_pattern[5].push_back(point_to_pattern(QPoint(int(scale*0.2),int(scale*0.8)),QPoint(int(scale*0.4),int(scale*0.5))));
    this->sys_flag->draw_pattern[5].push_back(point_to_pattern(QPoint(int(scale*0.4),int(scale*0.5)),QPoint(int(scale*0.6),int(scale*0.8))));
    this->sys_flag->draw_pattern[5].push_back(point_to_pattern(QPoint(int(scale*0.6),int(scale*0.8)),QPoint(int(scale*0.9),int(scale*0.2))));

    this->sys_flag->draw_pattern[7].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.1)),QPoint(int(scale*0.1),int(scale*0.9))));
    this->sys_flag->draw_pattern[7].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.5)),QPoint(int(scale*0.9),int(scale*0.5))));
    this->sys_flag->draw_pattern[7].push_back(point_to_pattern(QPoint(int(scale*0.2),int(scale*0.4)),QPoint(int(scale*0.3),int(scale*0.2))));
    this->sys_flag->draw_pattern[7].push_back(point_to_pattern(QPoint(int(scale*0.3),int(scale*0.2)),QPoint(int(scale*0.5),int(scale*0.8))));
    this->sys_flag->draw_pattern[7].push_back(point_to_pattern(QPoint(int(scale*0.5),int(scale*0.8)),QPoint(int(scale*0.7),int(scale*0.6))));
    this->sys_flag->draw_pattern[7].push_back(point_to_pattern(QPoint(int(scale*0.7),int(scale*0.6)),QPoint(int(scale*0.8),int(scale*0.8))));

    this->sys_flag->draw_pattern[35].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.5)),QPoint(int(scale*0.3),int(scale*0.5))));
    this->sys_flag->draw_pattern[35].push_back(point_to_pattern(QPoint(int(scale*0.3),int(scale*0.5)),QPoint(int(scale*0.6),int(scale*0.2))));
    this->sys_flag->draw_pattern[35].push_back(point_to_pattern(QPoint(int(scale*0.7),int(scale*0.3)),QPoint(int(scale*0.9),int(scale*0.3))));
    this->sys_flag->draw_pattern[35].push_back(point_to_pattern(QPoint(int(scale*0.7),int(scale*0.7)),QPoint(int(scale*0.9),int(scale*0.7))));

    this->sys_flag->draw_pattern[36].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.7)),QPoint(int(scale*0.3),int(scale*0.7))));
    this->sys_flag->draw_pattern[36].push_back(point_to_pattern(QPoint(int(scale*0.1),int(scale*0.3)),QPoint(int(scale*0.3),int(scale*0.3))));
    this->sys_flag->draw_pattern[36].push_back(point_to_pattern(QPoint(int(scale*0.4),int(scale*0.2)),QPoint(int(scale*0.7),int(scale*0.5))));
    this->sys_flag->draw_pattern[36].push_back(point_to_pattern(QPoint(int(scale*0.7),int(scale*0.5)),QPoint(int(scale*0.9),int(scale*0.5))));
}
pattern MainWindow::point_to_pattern(QPoint pos1,QPoint pos2)
{
    pattern pat;
    pat.start=pos1;
    pat.end=pos2;
    return pat;
}
void MainWindow::image()
{
    int count=0;
    for(int i=0;i<this->custom_menu->buttom_group.size();i++)
        count+=this->custom_menu->buttom_group[i]->buttons().size();
    Interface->prefix="border-image:url";
    //icon按顺序排列后，优化如下
    /*
    for(int i=0;i<count;i++)
    {
        Interface->url.push_back("(:/new/prefix1/icon/"+QString::number(i+1)+".png)");
    }
    */
    Interface->url.push_back("(:/new/prefix1/icon/1.png)");
    Interface->url.push_back("(:/new/prefix1/icon/2.png)");
    Interface->url.push_back("(:/new/prefix1/icon/3.png)");
    Interface->url.push_back("(:/new/prefix1/icon/4.png)");
    Interface->url.push_back("(:/new/prefix1/icon/5.png)");
    Interface->url.push_back("(:/new/prefix1/icon/6.png)");
    Interface->url.push_back("(:/new/prefix1/icon/7.png)");
    Interface->url.push_back("(:/new/prefix1/icon/8.png)");
    Interface->url.push_back("(:/new/prefix1/icon/9.png)");
    Interface->url.push_back("(:/new/prefix1/icon/10.png)");
    Interface->url.push_back("(:/new/prefix1/icon/11.png)");
    Interface->url.push_back("(:/new/prefix1/icon/12.png)");
    Interface->url.push_back("(:/new/prefix1/icon/13.png)");
    Interface->url.push_back("(:/new/prefix1/icon/14.png)");
    Interface->url.push_back("(:/new/prefix1/icon/15.png)");
    Interface->url.push_back("(:/new/prefix1/icon/16.png)");
    Interface->url.push_back("(:/new/prefix1/icon/17.png)");
    Interface->url.push_back("(:/new/prefix1/icon/18.png)");
    Interface->url.push_back("(:/new/prefix1/icon/19.png)");
    //Interface->url.push_back("(:/new/prefix1/icon/20.png)");
    Interface->url.push_back("(:/new/prefix1/icon/27.png)");
    Interface->url.push_back("(:/new/prefix1/icon/28.png)");
    Interface->url.push_back("(:/new/prefix1/icon/29.png)");
    Interface->url.push_back("(:/new/prefix1/icon/30.png)");
    Interface->url.push_back("(:/new/prefix1/icon/31.png)");
    Interface->url.push_back("(:/new/prefix1/icon/32.png)");
    Interface->url.push_back("(:/new/prefix1/icon/33.png)");
    Interface->url.push_back("(:/new/prefix1/icon/34.png)");
    Interface->url.push_back("(:/new/prefix1/icon/35.png)");
    Interface->url.push_back("(:/new/prefix1/icon/36.png)");
    Interface->url.push_back("(:/new/prefix1/icon/37.png)");
    Interface->url.push_back("(:/new/prefix1/icon/38.png)");
    Interface->url.push_back("(:/new/prefix1/icon/39.png)");
    Interface->url.push_back("(:/new/prefix1/icon/40.png)");
    Interface->url.push_back("(:/new/prefix1/icon/41.png)");
    Interface->url.push_back("(:/new/prefix1/icon/42.png)");
    Interface->url.push_back("(:/new/prefix1/icon/43.png)");
    Interface->url.push_back("(:/new/prefix1/icon/44.png)");
    Interface->url.push_back("(:/new/prefix1/icon/45.png)");
    Interface->url.push_back("(:/new/prefix1/icon/46.png)");
    Interface->url.push_back("(:/new/prefix1/icon/47a.png)");
    Interface->url.push_back("(:/new/prefix1/icon/48a.png)");
    Interface->url.push_back("(:/new/prefix1/icon/49a.png)");
    Interface->url.push_back("(:/new/prefix1/icon/50a.png)");
}
void MainWindow::analysis()
{
custombutton->setVisible(true);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    //resert_flag();
    this->setFocusPolicy(Qt::StrongFocus);

    QPoint position=this->mapFromGlobal(event->globalPos());
    if(this->check_button_pos(position))
    {
        this->sys_flag->click_flag=false;
        QTimer::singleShot(300,this, SLOT(animateTimeout()));
        this->mmove();
        return;
    }

    this->parent->mainwindow_current=this;
    this->parent->select_flag=false;
    foreach(MainWindow* win,this->parent->mainwindow_group)
    {
        if(win!=this)
        {
            win->update();
        }
    }

    if(this->parent->child->place_flag)
    {       
        QPoint pos=this->mapFromGlobal(cursor().pos());
        sys_flag->move=new Button();
        //sys_flag->move=new custombutton();//自定义button,便于重写paint
       // sys_flag->move->setIcon(*Interface->image[0]);
        //sys_flag->move->setStyleSheet(Interface->prefix+Interface->url[this->parent->child->index]);
        sys_flag->move->setVisible(true);
        sys_flag->move->setGeometry(pos.x(),pos.y(),init_size,init_size);
        moudletogroup(sys_flag->move,this->parent->child->index,false);
        this->parent->child->place_flag=false;
        this->parent->draw_flag=false;
        this->parent->update();
        update();
        return;
    }

    if(this->parent->child->paste_flag)
    {
        pastemoudle();
        this->parent->child->paste_flag=false;
        return;
    }   
    this->sys_flag->start->setX(position.x());
    this->sys_flag->start->setY(position.y());
    this->sys_flag->end->setX(this->sys_flag->start->x());
    this->sys_flag->end->setY(this->sys_flag->start->y());
    if(this->line->group.size()!=0&&this->line->line_exist(this->sys_flag->start,this->custom_menu->line_error))
    {

        this->sys_flag->draw_flag=true;
        if(this->parent->select_flag)
        {
            this->parent->select_flag=false;
            update();
        }
        if(this->line->delete_flag)
        {
            this->line->delete_flag=false;
            find_selected_point();
        }

    }
    else
    {
        this->sys_flag->copy_group=true;
        this->copy_group->start.setX(position.x());
        this->copy_group->start.setY(position.y());
        this->copy_group->end.setX(position.x());
        this->copy_group->end.setY(position.y());

        this->sys_flag->draw_flag=false;
        if(this->line->delete_flag)
        {
            this->line->delete_flag=false;
            find_selected_point();
            update();
        }
        if(this->parent->select_flag)
        {
            this->parent->select_flag=false;
            update();
        }

    }

}//按下
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{   
    QPoint* oldpoint=new QPoint();
    QPoint pos;
    Simulation_Moudle* moudle=this->simulation_group->findwithbutton(this->sys_flag->move);
    int width,height;    
    if(sys_flag->move_flag)
    {
        //sys_flag->move->setGeometry(ui->centralWidget->mapFromGlobal(event->globalPos()).x()+5,ui->centralWidget->mapFromGlobal(event->globalPos()).y()+5,31,31);
        setbutton_position(sys_flag->move,this->mapFromGlobal(event->globalPos()).x()-this->sys_flag->move->width()/2,this->mapFromGlobal(event->globalPos()).y()-this->sys_flag->move->height()/2);
        oldpoint->setX(sys_flag->move->geometry().x());
        oldpoint->setY(sys_flag->move->geometry().y());
        this->line->changeline(sys_flag->move,oldpoint,moudle->input_size,moudle->output_size);
        update();
        update_label_pos(sys_flag->move);
      // qDebug()<<this->simulation_group->findwithbutton(this->sys_flag->move)->x;
      // qDebug()<<sys_flag->move->geometry();
      // qDebug()<<ui->centralWidget->mapFromGlobal(event->globalPos());
    }
    if(sys_flag->draw_flag)
    {
      //  painter.drawLine(this->simulation_moudle->x,this->simulation_moudle->y,ui->centralWidget->mapFromGlobal(event->globalPos()).x(),this->simulation_moudle->y);//draw line
        //qDebug()<<111;        
        if(draw_way==1)
        {
            this->sys_flag->end->setX(this->mapFromGlobal(event->globalPos()).x());
            this->sys_flag->end->setY(this->mapFromGlobal(event->globalPos()).y());
        }
        else if(draw_way==2)
        {
            checkdraw(this->mapFromGlobal(event->globalPos()).x(),this->mapFromGlobal(event->globalPos()).y());
        }
       // this->sys_flag->end->setY(this->sys_flag->start->y());
       // painter.drawEllipse(20,20,200,200);
        update();
        this->modify=true;
    }
    if(sys_flag->drag_flag)
    {
        pos=cursor().pos();
        if(this->sys_flag->button_width+pos.x()-this->sys_flag->start_point.x()>=this->sys_flag->width_min)
        {
            width=pos.x()-this->sys_flag->start_point.x();
              // qDebug()<<"zhangjianyu";
        }
        else
            width=this->sys_flag->width_min-this->sys_flag->button_width;
        if(this->sys_flag->button_height+pos.y()-this->sys_flag->start_point.y()>=this->sys_flag->height_min)
        {
            height=pos.y()-this->sys_flag->start_point.y();
        }
        else
            height=this->sys_flag->height_min-this->sys_flag->button_height;;
        setsize(this->sys_flag->move,width,height);
        Simulation_Moudle* moudle=this->simulation_group->findwithbutton(this->sys_flag->move);
        if(moudle->index==29)
            interface_expand(moudle,0);
        else if((moudle->index==38&&moudle->bind_interface->output_flag==false)||(moudle->index==39&&moudle->tag_bind->output_flag==false))
            interface_expand(moudle,1);
        updatenode(moudle);
        update_label_pos(moudle->button);
    }
    if(this->sys_flag->copy_group)
    {
        this->copy_group->end.setX(this->mapFromGlobal(event->globalPos()).x());
        this->copy_group->end.setY(this->mapFromGlobal(event->globalPos()).y());
        update();
    }
    if(this->parent->select_flag)
    {
        this->sys_flag->current.setX(this->mapFromGlobal(event->globalPos()).x()+5);
        this->sys_flag->current.setY(this->mapFromGlobal(event->globalPos()).y()+5);
        for(int i=0;i<this->copy_group->moudle_group.size();i++)
        {
            if(i==0)
            {   this->copy_group->moudle_group[i]->button->move(this->sys_flag->current.x(),this->sys_flag->current.y());
            }
            else
            {
                this->copy_group->moudle_group[i]->button->move(this->sys_flag->current.x()+this->copy_group->distance[i].x(),this->sys_flag->current.y()+this->copy_group->distance[i].y());
            }
            oldpoint->setX(this->copy_group->moudle_group[i]->button->geometry().x());
            oldpoint->setY(this->copy_group->moudle_group[i]->button->geometry().y());
            update_label_pos(this->copy_group->moudle_group[i]->button);
            this->line->changeline(this->copy_group->moudle_group[i]->button,oldpoint,this->copy_group->moudle_group[i]->input_size,this->copy_group->moudle_group[i]->output_size);

        }
        update();
    }

}//按下移动
void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if(this->sys_flag->click_flag==false)//单击button
    {
        this->sys_flag->click_flag=true;
        this->single_click();
        return;
    }

    Simulation_Moudle* moudle=this->simulation_group->findwithbutton(this->sys_flag->move);
    QPoint* newpos=new QPoint();
    int y;
    if(sys_flag->move_flag)
    {        
        sys_flag->move_flag=0;
        moudle->setposition();//update simulation_moudle position
       // this->simulation_group->findwithbutton(this->sys_flag->move)->setRect();
        for(int i=0;i<moudle->input_size;i++)
        {
            y=moudle->button->y()+int((i+0.5)*moudle->button->height()/(moudle->input_size));
            newpos->setX(this->sys_flag->move->x());
            newpos->setY(y);
            if(checkpos(moudle,newpos,i,true))
                this->detect_line_connect(this->line->group[this->line->current_id]);
        }        
        for(int i=0;i<moudle->output_size;i++)
        {
            y=moudle->button->y()+int((i+0.5)*moudle->button->height()/(moudle->output_size));
            newpos->setX(this->sys_flag->move->x()+this->sys_flag->move->width());
            newpos->setY(y);
            if(checkpos(moudle,newpos,i,false))
                this->detect_line_connect(this->line->group[this->line->current_id]);
        }       
    }
    if(sys_flag->draw_flag)
    {
        bool insert=false;
        sys_flag->draw_flag=false;

        insert=this->line->insertline(this->sys_flag->start,this->sys_flag->end);
        if(insert)
        {
            if(this->line->group[this->line->current_id]->line.size()==1)
            {
                this->line->group[this->line->current_id]->startindex.push_back(this->sys_flag->current_node);
            }
            if(this->line->group[this->line->current_id]->startbutton.size()==0)
            {
                if(findmoudle(this->sys_flag->end,true))
                    detect_line_connect(this->line->group[this->line->current_id]);
            }
            else
            {
                if(findmoudle(this->sys_flag->end,false))
                    detect_line_connect(this->line->group[this->line->current_id]);
            }

        }
    }
    if(sys_flag->drag_flag)
    {
        this->simulation_group->findwithbutton(this->sys_flag->move)->setposition();//update simulation_moudle position
        sys_flag->drag_flag=false;

    }
    if(this->parent->select_flag)
    {
        moudle->setposition();
        //sys_flag->select_flag=false;
        update();
    }
    if(this->sys_flag->copy_group)
    {
        sys_flag->copy_group=false;
        selectall(this->copy_group->start.x(),this->copy_group->start.y(),this->copy_group->end.x(),this->copy_group->end.y());
        update();
    }

    //qDebug()<<"zhangjianyu";
    //resert_flag();

}//松开
void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint pos=this->mapFromGlobal(cursor().pos());
    if(this->check_button_pos(pos))
    {
        this->double_click();
        return;
    }

    if(this->parent->select_flag)
        this->parent->select_flag=false;
    point* poi=this->line->deleteline(this->sys_flag->end,this->custom_menu->line_error);
    if(poi!=nullptr)
    {
        this->line->select_point=poi;
        poi->selected_flag=true;
        Iteration_line(poi);
    }
    else
        this->line->select_point=nullptr;
    update();
    if(this->sys_flag->drag_flag)
        this->sys_flag->drag_flag=false;
}//双击
void MainWindow::Iteration_line(point* poi)
{
    for(int i=0;i<poi->branch.size();i++)
    {
        poi->branch[i]->selected_flag=true;
        Iteration_line(poi->branch[i]);
    }
}
//pressed
void MainWindow::mmove()
{
    //qDebug()<<QThread::currentThreadId();
    if(bug==1&&this->sys_flag->move_flag||this->sys_flag->drag_flag||this->sys_flag->draw_flag)
        return;

   QPoint pos=this->mapFromGlobal(cursor().pos());
   //sys_flag->move=qobject_cast<QPushButton*>(sender());
   int y;
   bool flag=false;
   //qDebug()<<this->sys_flag->move->geometry();
   Simulation_Moudle* moudle=this->simulation_group->findwithbutton(sys_flag->move);
   /* if(sys_flag->move_flag!=1&&(pos.x()>=moudle->node[0]->x_min&&pos.x()<=moudle->node[0]->x_max&&pos.y()>=moudle->node[0]->y_min&&pos.y()<=moudle->node[0]->y_max))
   {
       this->sys_flag->draw_flag=true;
      // this->sys_flag->start->setX(moudle->x);
      // this->sys_flag->start->setY(moudle->y+15);
       this->sys_flag->start=transform_position(this->ui->centralWidget,this,new QPoint(moudle->x,moudle->y+15));
       this->line->startline(sys_flag->move);

   }
   */
   if(this->line->delete_flag)
   {
       this->line->delete_flag=false;
       find_selected_point();
       update();
   }
   if(this->parent->select_flag)
   {
       if(this->copy_group->moudle_group.indexOf(moudle)!=-1&&moudle->button->geometry().contains(pos))
       {
           resort(this->copy_group->moudle_group.indexOf(moudle));
           return;
       }
       else
       {
           this->parent->select_flag=false;
           update();
       }
   }
   //this->sys_flag->draw_flag=false;
   //moudle input&output
   //if(sys_flag->move_flag!=1&&sys_flag->drag_flag!=true&&(pos.x()>=(moudle->button->geometry().x()+moudle->button->geometry().width()-this->custom_menu->group_interval)&&pos.x()<=(moudle->button->geometry().x()+moudle->button->geometry().width())&&pos.y()>=(moudle->button->height()/2-this->custom_menu->group_interval/2+moudle->button->y())&&pos.y()<=(moudle->button->height()/2+this->custom_menu->group_interval/2+moudle->button->y())))
   for(int i=0;i<moudle->output_size;i++)
   {
       y=moudle->button->y()+int((i+0.5)*moudle->button->height()/(moudle->output_size));
       //qDebug()<<y<<moudle->button->geometry();
       if((pos.x()>=(moudle->button->geometry().x()+moudle->button->geometry().width())&&pos.x()<=(moudle->button->geometry().x()+moudle->button->geometry().width()+this->custom_menu->group_interval)&&pos.y()>=y-this->custom_menu->group_interval&&pos.y()<=y+this->custom_menu->group_interval))
       {
           flag=true;
           this->sys_flag->current_node=i;
           this->sys_flag->draw_flag=true;
          // this->sys_flag->start->setX(moudle->x+31);
          // this->sys_flag->start->setY(moudle->y+15);
           this->sys_flag->start=new QPoint(moudle->button->x()+moudle->button->width(),y);
           this->sys_flag->end->setX(this->sys_flag->start->x());
           this->sys_flag->end->setY(this->sys_flag->start->y());
           this->line->startline(sys_flag->move);
           moudle->output[i]->connect_line.push_back(this->line->group[this->line->group.size()-1]);//output node insert line
       }
   }   
   if(flag==false)
//   else if(sys_flag->move_flag!=1&&sys_flag->draw_flag!=true&&(pos.x()>=(moudle->button->geometry().x()+moudle->button->geometry().width()-this->custom_menu->area)&&pos.x()<=(moudle->button->geometry().x()+moudle->button->geometry().width())&&pos.y()>=(moudle->button->height()-this->custom_menu->area+moudle->button->y())&&pos.y()<=(moudle->button->height()+moudle->button->y())))
   {
       if((pos.x()>=(moudle->button->geometry().x()+moudle->button->geometry().width()-this->custom_menu->area)&&pos.x()<=(moudle->button->geometry().x()+moudle->button->geometry().width())&&pos.y()>=(moudle->button->height()-this->custom_menu->area+moudle->button->y())&&pos.y()<=(moudle->button->height()+moudle->button->y())))
       {
           this->sys_flag->drag_flag=true;
           this->sys_flag->start_point=cursor().pos();
           this->sys_flag->button_width=this->sys_flag->move->width();
           this->sys_flag->button_height=this->sys_flag->move->height();
       }
       else
       {          
      // if(sys_flag->draw_flag!=true&&sys_flag->drag_flag!=true)
           this->sys_flag->draw_flag=false;
           this->sys_flag->drag_flag=false;
           sys_flag->move_flag=1;          
       }
   }
}
//released
void MainWindow::mreleased()
{

}
//键盘单击事件
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Delete&&this->line->delete_flag)
    {
        if(delete_way==0)
            delete_line();
        else
            delete_line_way2();
        update();
    }
    if(event->key()==Qt::Key_Delete&&this->parent->select_flag)
    {
        delete_moudle();
        update();
    }

}
//键盘组合键事件
void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_C))
    {
        clonemoudle();
    }//copy
    if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_X))
    {
        clonemoudle();
        delete_moudle();
        cut_tag();
        update();
    }//cut
    if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_V))
    {
        pastemoudle();
    }//paste
    if(event->modifiers() == Qt::ControlModifier&&(event->key() == Qt::Key_S))
    {
        save();
    }

}
void MainWindow::clonemoudle()
{
     if(this->parent->select_flag)
     {
         //清空剪切板上的临时数据
         int count=this->parent->copy_moudle_group->moudle_group.size();
         for(int i=0;i<count;i++)
         {
             delete this->parent->copy_moudle_group->moudle_group[0];
             this->parent->copy_moudle_group->moudle_group.removeAt(0);
             this->parent->copy_moudle_group->distance.removeAt(0);
             this->parent->copy_moudle_group->width.removeAt(0);
             this->parent->copy_moudle_group->height.removeAt(0);
         }
         //复制新数据
         for(int i=0;i<this->copy_group->moudle_group.size();i++)
         {
             this->parent->copy_moudle_group->moudle_group.push_back(clone_moudle(this->copy_group->moudle_group[i]));
             this->parent->copy_moudle_group->distance.push_back(this->copy_group->distance[i]);
             this->parent->copy_moudle_group->width.push_back(this->copy_group->moudle_group[i]->button->width());
             this->parent->copy_moudle_group->height.push_back(this->copy_group->moudle_group[i]->button->height());
         }

         update();
     }

}
Simulation_Moudle* MainWindow::clone_moudle(Simulation_Moudle* moudle)
{
    Simulation_Moudle* newmoudle=new Simulation_Moudle();
    //newmoudle->button->setGeometry(moudle->button->geometry());
    newmoudle->index=moudle->index;
    newmoudle->name=moudle->name;
    newmoudle->input_size=moudle->input_size;
    newmoudle->output_size=moudle->output_size;
    for(int i=0;i<moudle->param.size();i++)
        newmoudle->param.push_back(moudle->param[i]);

    //专属模块
    if(moudle->index==5||moudle->index==14||moudle->index==15)//折线或传递函数自定义环节
    {
        newmoudle->time=moudle->time;
        newmoudle->value=moudle->value;
        newmoudle->time_sequence=moudle->time_sequence;
        newmoudle->value_sequence=moudle->value_sequence;
    }
    else if(moudle->index==12||moudle->index==13)//惯性环节额外参数
    {
        newmoudle->time=moudle->time;
        newmoudle->value=moudle->value;
    }
    else if(moudle->index==38)//接口模块
    {
        newmoudle->value=moudle->value;
        newmoudle->bind_interface=new interface_bind(*moudle->bind_interface);
    }
    else if(moudle->index==39)//tag_bind
    {
        newmoudle->value=moudle->value;
        newmoudle->tag_bind=new bind_tag(*moudle->tag_bind);
    }
    else
    {
        newmoudle->value=moudle->value;
    }
    return newmoudle;
}
void MainWindow::cut_tag()
{
    for(int i=0;i<this->parent->copy_moudle_group->moudle_group.size();i++)
    {
        Simulation_Moudle* moudle=this->parent->copy_moudle_group->moudle_group[i];
        if(moudle->index==39)
        {
            moudle->tag_bind->input_tag=moudle->tag_bind->input_tag_temp;
            moudle->tag_bind->output_tag=moudle->tag_bind->output_tag_temp;
        }
    }
}
void MainWindow::remove_tag(QString tag)
{
    if(this->sys_flag->tag_group.contains(tag)==true)
    {
        int index=this->sys_flag->tag_group.indexOf(tag);
        this->sys_flag->tag_number_group.removeAt(index);
        this->sys_flag->tag_group.removeOne(tag);
    }
}
void MainWindow::insert_tag(QString tag)
{
    if(this->sys_flag->tag_group.contains(tag)==false)
    {
        QList<int> num=getnum(tag);
        int index=sort_tag(num,0,0);
        this->sys_flag->tag_group.insert(index,tag);
        this->sys_flag->tag_number_group.insert(index,num);
    }
}
int MainWindow::sort_tag(QList<int> num,int index,int start)
{
    for(int i=start;i<this->sys_flag->tag_group.size();i++)
    {
        if(num[index]<this->sys_flag->tag_number_group[i][index])
        {
            return i;
        }
        else if(num[index]==this->sys_flag->tag_number_group[i][index])
        {
            return sort_tag(num,index+1,i);
        }
        else
        {
            if(index>=1&&i>=1)
                if(this->sys_flag->tag_number_group[i][index-1]!=this->sys_flag->tag_number_group[i-1][index-1])
                    return i-1;
        }
    }
    return this->sys_flag->tag_group.size();
}
QList<int> MainWindow::getnum(QString tag)
{
    QList<int> num;
    QString tag_child="";
    for(int i=0;i<tag.size();i++)
    {
        if(tag[i]=='-')
        {
            num.push_back(tag_child.toInt());
            tag_child="";
        }
        else
        {
            tag_child+=tag[i];
        }
    }
    num.push_back(tag_child.toInt());
    return num;
}
void MainWindow::cutmoudle()
{
    clonemoudle();
    delete_moudle();
    cut_tag();
    this->parent->select_flag=false;    
    update();
}
void MainWindow::pastemoudle()
{

    QPoint pos=this->mapFromGlobal(cursor().pos());
    for(int i=0;i<this->parent->copy_moudle_group->moudle_group.size();i++)
    {
        //Simulation_Moudle* moudle=this->parent->copy_moudle_group->moudle_group[i];
        sys_flag->move=new Button();
        //sys_flag->move->setStyleSheet(Interface->prefix+Interface->url[moudle->index]);
        sys_flag->move->setVisible(true);
        if(i==0)
        {
            sys_flag->move->setGeometry(pos.x(),pos.y(),this->parent->copy_moudle_group->width[i],this->parent->copy_moudle_group->height[i]);
        }
        else
        {
            sys_flag->move->setGeometry(pos.x()+this->parent->copy_moudle_group->distance[i].x(),pos.y()+this->parent->copy_moudle_group->distance[i].y(),this->parent->copy_moudle_group->width[i],this->parent->copy_moudle_group->height[i]);
        }
        //connect(sys_flag->move, &QAbstractButton::pressed, this, &MainWindow::mmove);
        //connect(sys_flag->move, &QAbstractButton::clicked, this, &MainWindow::button_click);
        //connect(sys_flag->move, &QAbstractButton::released, this, &MainWindow::mreleased);
        moudletogroup(sys_flag->move,i,true);
    }
    update();
}
void MainWindow::deleteany()
{
    if(delete_way==0)
        delete_line();
    else
        delete_line_way2();
    delete_moudle();
    update();
}
void MainWindow::delete_line()
{
    if(this->line->delete_flag==false)
        return;
    Line* line=this->line->group[this->line->delete_id];
    Simulation_Moudle* moudle;

    for(int i=0;i<line->startbutton.size();i++)
    {
        moudle=simulation_group->findwithbutton(line->startbutton[i]);
        moudle->output[line->startindex[i]]->connect_line.removeOne(line);
    }
    for(int i=0;i<line->endbutton.size();i++)
    {
        moudle=simulation_group->findwithbutton(line->endbutton[i]);
        moudle->input[line->endindex[i]]->connect_line.removeOne(line);
    }
    this->line->group.removeOne(line);
    delete line;
    this->line->delete_flag=false;
    this->modify=true;//删除line也是修改文件
}
void MainWindow::delete_line_way2()
{
    if(this->line->delete_flag==false)
        return;

    QList<int> point_group;
    Line* linee=this->line->group[this->line->current_id];
    for(int i=0;i<linee->line.size();i++)
    {
        if(linee->line[i].selected_flag)
        {
            delete_line_process(linee,&linee->line[i]);
            point_group.push_back(i);
        }
    }
    if(this->line->select_point->parent_line!=nullptr)
    {
        this->line->select_point->parent_line->branch.removeOne(this->line->select_point);
        if(this->line->select_point->parent_start_end==1)//判断是否从父line的start或end引出
        {
            this->line->select_point->parent_line->start_point.removeOne(this->line->select_point);
            if(this->line->select_point->parent_line->start_point.size()==0)
                this->line->select_point->parent_line->start_flag=false;
        }
        else if(this->line->select_point->parent_start_end==2)
        {
            this->line->select_point->parent_line->end_point.removeOne(this->line->select_point);
            if(this->line->select_point->parent_line->end_point.size()==0)
            this->line->select_point->parent_line->end_flag=false;
        }
    }
    for(int i=0;i<point_group.size();i++)
    {
        linee->line.removeAt(point_group[i]);
        for(int j=i+1;j<point_group.size();j++)
            point_group[j]--;
    }
    if(linee->line.size()==0)
    {
        this->line->group.removeOne(linee);
        delete linee;
    }
    else
    {
        this->detect_line_connect(linee);
    }
    this->line->delete_flag=false;
    this->modify=true;//删除line也是修改文件

}
void MainWindow::delete_line_process(Line* linee,point* poi)
{
    //寻找startbutton
    for(int i=0;i<linee->startbutton.size();i++)
    {
        if(linee->startline[i]==poi)
        {
            Simulation_Moudle* moudle=simulation_group->findwithbutton(linee->startbutton[i]);
            moudle->output[linee->startindex[i]]->connect_line.removeOne(linee);
            linee->startbutton.removeAt(i);
            linee->startindex.removeAt(i);
            linee->startline.removeAt(i);
            break;
        }
    }
    //寻找endbutton
    for(int i=0;i<linee->endbutton.size();i++)
    {
        if(linee->endline[i]==poi)
        {
            Simulation_Moudle* moudle=simulation_group->findwithbutton(linee->endbutton[i]);
            moudle->input[linee->endindex[i]]->connect_line.removeOne(linee);
            linee->endbutton.removeAt(i);
            linee->endindex.removeAt(i);
            linee->endline.removeAt(i);
            break;
        }
    }
}
void MainWindow::find_selected_point()
{
    for(int j=0;j<this->line->group.size();j++)
    {
        Line* linee=this->line->group[j];
        for(int i=0;i<linee->line.size();i++)
        {
            if(linee->line[i].selected_flag)
            {
                linee->line[i].selected_flag=false;
                resume_line(&linee->line[i]);
            }
        }
    }
}
void MainWindow::resume_line(point* poi)
{
    for(int i=0;i<poi->branch.size();i++)
    {
        poi->branch[i]->selected_flag=false;
        resume_line(poi->branch[i]);
    }
}
void MainWindow::delete_moudle()
{
    if(this->parent->select_flag==false)
        return;
    int count=this->copy_group->moudle_group.size();
    for(int i=0;i<count;i++)
    {
        Simulation_Moudle* moudle=this->copy_group->moudle_group[i];
        Line* linee;
        if(moudle==nullptr)
            return;

        for(int j=0;j<moudle->input_size;j++)
        {
            for(int i=0;i<moudle->input[j]->connect_line.size();i++)
            {
                linee=moudle->input[j]->connect_line[i];
                this->line->remove_output(moudle->button,linee);
                detect_line_connect(linee);
            }
        }
        for(int j=0;j<moudle->output_size;j++)
        {
            for(int i=0;i<moudle->output[j]->connect_line.size();i++)
            {
                linee=moudle->output[j]->connect_line[i];
                this->line->remove_input(linee);
                detect_line_connect(linee);
            }
        }        
        this->simulation_group->group.removeOne(moudle);        
        delete moudle->button;
        delete moudle->label;
        if(moudle->index==12||moudle->index==13||moudle->index==14||moudle->index==15)
        {
            delete moudle->fenmu;
            delete moudle->fenzi;
        }
        else if(moudle->index==8||moudle->index==9||moudle->index==10||moudle->index==11||moudle->index==19||moudle->index==22||moudle->index==23||moudle->index==24||moudle->index==25||moudle->index==26||moudle->index==27||moudle->index==28||moudle->index==29||moudle->index==30||moudle->index==31||moudle->index==32||moudle->index==33||moudle->index==34||moudle->index==40||moudle->index==41)
            delete moudle->fenzi;
        else if(moudle->index==38)//删除接口模块 断开服务器连接
        {
            delete moudle->fenzi;
            delete moudle->bind_interface->input_socket;
            delete moudle->bind_interface->output_socket;
        }
        else if(moudle->index==39)//bind_tag 从字典中移除
        {
            delete moudle->fenzi;
            QString str=this->sys_flag->input_bind.key(moudle);
            if(str!="")
            {
                this->insert_tag(str);
                this->sys_flag->input_bind.remove(str);
            }
            str=this->sys_flag->output_bind.key(moudle);
            if(str!="")
            {
                this->insert_tag(str);
                this->sys_flag->output_bind.remove(str);
            }

        }
        delete moudle;
        //destroyed(this->sys_flag->move);//删除控件用delete
    }
    for(int i=0;i<count;i++)
    {
        this->copy_group->moudle_group.removeAt(0);
        this->copy_group->distance.removeAt(0);
        this->copy_group->height.removeAt(0);
        this->copy_group->width.removeAt(0);
    }
    this->parent->select_flag=false;   
    this->modify=true;//删除模块也是修改文件
}
void MainWindow::animateTimeout()
{
    if(sys_flag->click_flag==false)
        this->sys_flag->click_flag=true;
    /*
    if(sys_flag->click_flag==true)
    {
        sys_flag->click_flag=false;
        single_click();
    }
    */
}
void MainWindow::button_click()
{
   // qDebug()<<"single";
    if(sys_flag->click_flag==false)
    {
        QTimer::singleShot(300,this, SLOT(animateTimeout()));
        sys_flag->click_flag=true;
    }
    else
    {
        sys_flag->click_flag=false;
        double_click();
    }
}
void MainWindow::paintEvent(QPaintEvent *)
{
    //qDebug()<<111;
    QPainter painter(this);//painter画笔只能是从属于当前类
    //qDebug()<<QThread::currentThreadId();
    paintline(&painter);
    paintmoudle(&painter);
  //  painter.drawEllipse(20,20,200,200);//draw ellipse
  //  painter.drawRect(20,20,200,200);//draw rect
}

void MainWindow::paintline(QPainter* painter)
{   
    //painter->setPen(QPen(Qt::black,2));//set the painter style
    for(int i=0;i<this->line->group.size();i++)
    {
        painter->setPen(QPen(Qt::black,2));//set the painter style
        Line* llin=this->line->group[i];
        int flag=0;
        /*if(delete_way==0)
        {
            if(this->line->delete_flag&&i==this->line->delete_id)
                painter->setPen(QPen(Qt::red,2));
            else
                painter->setPen(QPen(Qt::black,2));
        }
        */
        if(this->line->delete_flag&&delete_way==0&&i==this->line->delete_id)
        {
            painter->setPen(QPen(Qt::red,2));
            flag=1;
        }
        for(int j=0;j<llin->line.size();j++)
        {
            //if(delete_way==1)
            //{
            if(delete_way==1&&llin->line[j].selected_flag==true)
                painter->setPen(QPen(Qt::red,2));
            else if(flag==0)
            {
                if(llin->no_single==false)
                {
                    if(llin->line[j].start_flag==false||llin->line[j].end_flag==false)
                        painter->setPen(QPen(Qt::blue,2));
                    else
                        painter->setPen(QPen(Qt::black,2));
                }
                else//信号不完整
                    painter->setPen(QPen(Qt::blue,2));
            }
            //else if(delete_way==1)
            //    painter->setPen(QPen(Qt::black,2));
            //}
            painter->drawLine(llin->line[j].start.x(),llin->line[j].start.y(),llin->line[j].end.x(),llin->line[j].end.y());
        }

    }
   // qDebug()<<this->sys_flag->draw_flag;
  //  QPoint pos=ui->centralWidget->mapFromGlobal(cursor().pos());   
    if(this->sys_flag->draw_flag)
    {
        painter->drawLine(this->sys_flag->start->x(),this->sys_flag->start->y(),this->sys_flag->end->x(),this->sys_flag->end->y());//draw line

    }
    //绘制选中区域
    if(this->sys_flag->copy_group)
    {
        painter->setPen(Qt::PenStyle::DashLine);
        painter->drawLine(this->copy_group->start.x(),this->copy_group->start.y(),this->copy_group->start.x(),this->copy_group->end.y());
        painter->drawLine(this->copy_group->start.x(),this->copy_group->end.y(),this->copy_group->end.x(),this->copy_group->end.y());
        painter->drawLine(this->copy_group->end.x(),this->copy_group->end.y(),this->copy_group->end.x(),this->copy_group->start.y());
        painter->drawLine(this->copy_group->end.x(),this->copy_group->start.y(),this->copy_group->start.x(),this->copy_group->start.y());
    }
}//draw line
void MainWindow::paintmoudle(QPainter* painter)
{
    int x,y;
    QPoint* oldpos=new QPoint();
    painter->setPen(QPen(Qt::black,2));
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        if(this->parent->select_flag&&this->copy_group->findmoudle(moudle->button))
        {
            painter->setPen(QPen(Qt::red,2));
        }
        else
        {
            painter->setPen(QPen(Qt::black,2));
        }
        painter->drawRect(moudle->button->geometry());
        for(int j=0;j<moudle->input.size();j++)//输入端口绘制
        {
            if(moudle->input[j]->connect_line.size()==0)
                painter->setPen(QPen(Qt::blue,1));
            else
                painter->setPen(QPen(Qt::black,1));
            x=moudle->button->x();
            y=moudle->button->y()+int((j+0.5)*moudle->button->height()/(moudle->input.size()));
            //moudle->spacing=moudle->button->height()/(moudle->input.size()+1)-3;
            moudle->spacing=this->custom_menu->group_interval;
            oldpos->setX(x);
            oldpos->setY(y);
            painter->drawLine(oldpos->x(),int(oldpos->y()-moudle->spacing),int(oldpos->x()+moudle->spacing),oldpos->y());
            painter->drawLine(oldpos->x(),int(oldpos->y()+moudle->spacing),int(oldpos->x()+moudle->spacing),oldpos->y());

        }
        for(int j=0;j<moudle->output.size();j++)//输出端口绘制
        {
            if(moudle->output[j]->connect_line.size()==0)
                painter->setPen(QPen(Qt::blue,1));
            else
                painter->setPen(QPen(Qt::black,1));
           //moudle->spacing=moudle->button->height()/(moudle->output.size()+1)-3;
            moudle->spacing=6;
            x=moudle->button->x()+moudle->button->width();
            y=moudle->button->y()+int((j+0.5)*moudle->button->height()/(moudle->output.size()));
            oldpos->setX(x);
            oldpos->setY(y);
            painter->drawLine(oldpos->x(),int(oldpos->y()-moudle->spacing),int(oldpos->x()+moudle->spacing),oldpos->y());
            painter->drawLine(oldpos->x(),int(oldpos->y()+moudle->spacing),int(oldpos->x()+moudle->spacing),oldpos->y());
        }
        if(moudle->index==12||moudle->index==13||moudle->index==14||moudle->index==15)
        {
            painter->setPen(QPen(Qt::black,1));
            int length=int(moudle->time.size()*7>moudle->fenmu->width()?moudle->fenmu->width():moudle->time.size()*7);
            painter->drawLine(moudle->button->x()+moudle->button->width()/2-length/2,moudle->button->y()+moudle->button->height()/2,moudle->button->x()+moudle->button->width()/2+length/2,moudle->button->y()+moudle->button->height()/2);
        }

        //moudle内部图案绘制
        painter->setPen(QPen(Qt::black,1));
        for(int j=0;j<this->sys_flag->draw_pattern[moudle->index].size();j++)
        {
            pattern pat=this->sys_flag->draw_pattern[moudle->index][j];
            painter->drawLine(moudle->button->x()+int(pat.start.x()*moudle->button->width()/this->custom_menu->scale_factor),moudle->button->y()+int(pat.start.y()*moudle->button->height()/this->custom_menu->scale_factor),moudle->button->x()+int(pat.end.x()*moudle->button->width()/this->custom_menu->scale_factor),moudle->button->y()+int(pat.end.y()*moudle->button->height()/this->custom_menu->scale_factor));

        }
        //绘制sin,cos等模块的内部图案
        if(moudle->index==2)//正弦函数发生器
        {
            painter->drawLine(moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+moudle->button->height()/2,moudle->button->x()+int(0.9*moudle->button->width()),moudle->button->y()+moudle->button->height()/2);
            painter->drawLine(moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+int(0.1*moudle->button->height()),moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+int(0.9*moudle->button->height()));
            for(int j=0;j<int(moudle->button->width()*0.8);j++)
                painter->drawPoint(QPoint(moudle->button->x()+int(0.1*moudle->button->width())+j,moudle->button->y()+moudle->button->height()/2-int(moudle->button->height()/2*sin(double(j)*2*PI/int(moudle->button->width()*0.8)))));
        }
        else if(moudle->index==37)//曲线
        {
            painter->drawRect(QRect(moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+int(0.1*moudle->button->height()),int(moudle->button->width()*0.8),int(moudle->button->height()*0.8)));
            painter->drawLine(moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+moudle->button->height()/2,moudle->button->x()+int(0.9*moudle->button->width()),moudle->button->y()+moudle->button->height()/2);
            painter->drawLine(moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+int(0.1*moudle->button->height()),moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+int(0.9*moudle->button->height()));
            for(int j=0;j<int(moudle->button->width()*0.8);j++)
                painter->drawPoint(QPoint(moudle->button->x()+int(0.1*moudle->button->width())+j,moudle->button->y()+moudle->button->height()/2-int(moudle->button->height()/2*0.8*sin(double(j)*2*PI/int(moudle->button->width()*0.8)))));
        }       
        else if(moudle->index==20)//三角
        {
            painter->drawLine(moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+moudle->button->height()/2,moudle->button->x()+int(0.9*moudle->button->width()),moudle->button->y()+moudle->button->height()/2);
            painter->drawLine(moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+int(0.1*moudle->button->height()),moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+int(0.9*moudle->button->height()));
            for(int j=0;j<int(moudle->button->width()*0.8);j++)
            {
                if(int(moudle->param[0])==0)
                    painter->drawPoint(QPoint(moudle->button->x()+int(0.1*moudle->button->width())+j,moudle->button->y()+moudle->button->height()/2-int(moudle->button->height()/2*sin(double(j)*2*PI/int(moudle->button->width()*0.8)))));
                else if(int(moudle->param[0])==1)
                    painter->drawPoint(QPoint(moudle->button->x()+int(0.1*moudle->button->width())+j,moudle->button->y()+moudle->button->height()/2-int(moudle->button->height()/2*cos(double(j)*2*PI/int(moudle->button->width()*0.8)))));
                else if(int(moudle->param[0])==2)
                {
                    if(j!=int(moudle->button->width()*0.8)/2)
                        painter->drawPoint(QPoint(moudle->button->x()+int(0.1*moudle->button->width())+j,moudle->button->y()+moudle->button->height()/2-int(moudle->button->height()/2*tan(double(j)*PI/int(moudle->button->width()*0.8))/tan((0.5-1.0/int(moudle->button->width()*0.8))*PI))));
                }
            }
        }
        else if(moudle->index==21)//反三角
        {
            painter->drawLine(moudle->button->x()+int(0.1*moudle->button->width()),moudle->button->y()+moudle->button->height()/2,moudle->button->x()+int(0.9*moudle->button->width()),moudle->button->y()+moudle->button->height()/2);
            painter->drawLine(moudle->button->x()+int(0.5*moudle->button->width()),moudle->button->y()+int(0.1*moudle->button->height()),moudle->button->x()+int(0.5*moudle->button->width()),moudle->button->y()+int(0.9*moudle->button->height()));
            for(int j=0;j<int(moudle->button->height()*0.8);j++)
            {
                if(int(moudle->param[0])==0)
                    painter->drawPoint(QPoint(moudle->button->x()+moudle->button->width()/2+int(moudle->button->width()/2*sin(double(j)*2*PI/int(moudle->button->height()*0.8))),moudle->button->y()+int(0.1*moudle->button->height())+j));
                else if(int(moudle->param[0])==1)
                    painter->drawPoint(QPoint(moudle->button->x()+moudle->button->width()/2+int(moudle->button->width()/2*cos(double(j)*2*PI/int(moudle->button->height()*0.8))),moudle->button->y()+int(0.1*moudle->button->height())+j));
                else if(int(moudle->param[0])==2)
                {
                    if(j!=int(moudle->button->height()*0.8)/2)
                        painter->drawPoint(QPoint(moudle->button->x()+moudle->button->width()/2+int(moudle->button->width()/2*tan(double(j)*PI/int(moudle->button->height()*0.8))/tan((0.5-1.0/int(moudle->button->height()*0.8))*PI)),moudle->button->y()+int(0.1*moudle->button->height())+j));
                }
            }
        }
    }
}//draw moudle node
bool MainWindow::detect_line_connect(Line* linee)
{
    if(linee->startbutton.size()!=0&&linee->endbutton.size()!=0)
    {
        linee->no_single=false;
        return false;
    }
    else if(display_error==1||this->sys_flag->signal_detect_flag==true)
    {
        linee->no_single=true;
        return true;
    }
    return false;
}
bool MainWindow::check_signal()
{
    int flag=0;
    if(this->simulation_group->group.size()==0)
    {
        this->parent->statr_message("signal error",1000);
        return false;
    }
    this->sys_flag->signal_detect_flag=true;
    for(int i=0;i<this->line->group.size();i++)
        if(detect_line_connect(this->line->group[i])==true)
            flag=1;
    this->sys_flag->signal_detect_flag=false;
    if(flag==1)
    {
        this->parent->statr_message("signal error",1000);
        return false;
    }
    for(int i=0;i<this->line->group.size();i++)
    {
        Line* linee=this->line->group[i];
        for(int j=0;j<linee->line.size();j++)
        {
            if(linee->line[j].start_flag==false||linee->line[j].end_flag==false)
            {
                flag=1;
                break;
            }
        }
    }
    if(flag==1)
    {
        this->parent->statr_message("signal error",1000);
        return false;
    }

    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        for(int j=0;j<moudle->input_size;j++)//检查模块输入引脚全部接入信号
        {
            moudle_param* param=moudle->input[j];
            if(param->connect_line.size()==0)
            {
                this->parent->statr_message("signal error",1000);
                return false;
            }
        }

        for(int j=0;j<moudle->output_size;j++)//检查模块输出引脚是否信号完整
        {
            moudle_param* param=moudle->output[j];
            if(param->connect_line.size()==0)
            {
                this->parent->statr_message("signal error",1000);
                return false;
            }
        }     
        if(moudle->index==38)//针对接口模块检测是否已与实际接口连接成功
        {
            if(moudle->bind_interface->input_flag==true&&moudle->bind_interface->input_success==false)
            {
                this->parent->statr_message(moudle->name+" input disonnect to server",1000);
                return false;
            }
            if(moudle->bind_interface->output_flag==true&&moudle->bind_interface->output_success==false)
            {
                this->parent->statr_message(moudle->name+" output disonnect to server",1000);
                return false;
            }
            //qDebug()<<2;
        }
        if(moudle->index==39)
        {
            if(moudle->tag_bind->input_flag==true&&moudle->tag_bind->input_tag=="-1")
            {
                this->parent->statr_message(moudle->name+" input not bind tag",1000);
                return false;
            }
            if(moudle->tag_bind->output_flag==true&&moudle->tag_bind->output_tag=="-1")
            {
                this->parent->statr_message(moudle->name+" output not bind tag",1000);
                return false;
            }
        }
    }
    return true;
}
bool MainWindow::findmoudle(QPoint* pos,bool flag)
{
    Simulation_Moudle* moudle;
    Flag result;
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        moudle=this->simulation_group->group[i];
        result=checkposinput(moudle,pos);        
        if(result.flag)
        {
            //qDebug()<<this->simulation_group->group.size();
            this->line->endline(moudle->button,this->line->group[this->line->current_id]->line.size()-1,true,result.result);
            moudle->input[result.result]->connect_line.push_back(this->line->group[this->line->current_id]);//input node
            return true;
        }
    }//检测line是否连接在moudle的input端
    if(flag)
    {
        for(int i=0;i<this->simulation_group->group.size();i++)
        {
            moudle=this->simulation_group->group[i];
            result=checkposoutput(moudle,pos);
            if(result.flag)
            {
                //qDebug()<<this->simulation_group->group.size();
                this->line->group[this->line->current_id]->startindex.push_back(result.result);
                this->line->start_line(moudle->button);
                moudle->output[result.result]->connect_line.push_back(this->line->group[this->line->current_id]);//input node
                return true;
            }
        }//检测line是否连接在moudle的output端

    }
    return false;
}
Flag MainWindow::checkposinput(Simulation_Moudle* moudle,QPoint* pos)
{
    int y;
    Flag result;
    for(int i=0;i<moudle->input_size;i++)
    {
        y=moudle->button->y()+int((i+0.5)*moudle->button->height()/(moudle->input_size));
        if(moudle->input[i]->connect_line.size()==0&&pos->x()>=(moudle->button->x()-this->custom_menu->group_interval)&&pos->x()<=(moudle->button->x()+this->custom_menu->group_interval)&&pos->y()>=(y-this->custom_menu->group_interval/2)&&pos->y()<=(y+this->custom_menu->group_interval/2))
        {
            result.flag=true;
            result.result=i;            
            return result;
        }
    }
    result.flag=false;
    return result;
}
Flag MainWindow::checkposoutput(Simulation_Moudle* moudle,QPoint* pos)
{
    Flag result;
    int y;

    for(int i=0;i<moudle->output_size;i++)
    {
        y=moudle->button->y()+int((i+0.5)*moudle->button->height()/(moudle->output_size));
        if(pos->x()>=(moudle->button->x()-this->custom_menu->group_interval+moudle->button->width())&&pos->x()<=(moudle->button->x()+moudle->button->width()+this->custom_menu->group_interval)&&pos->y()>=(y-this->custom_menu->group_interval/2)&&pos->y()<=(y+this->custom_menu->group_interval/2))
        {
            result.flag=true;
            result.result=i;
            return result;

        }
        //qDebug()<<*pos<<moudle->button->geometry()<<y;
    }
    result.flag=false;
    return result;
}
bool MainWindow::checkpos(Simulation_Moudle* moudle,QPoint* oldpos,int index,bool turn)
{
    int flag;
    if(turn)
    {
        if(moudle->input[index]->connect_line.size()==0)//模块输入结点只含有一个输入通道
            flag=this->line->moudle_point(this->sys_flag->move,oldpos,this->custom_menu->group_interval,true,index,true);
        else
            flag=this->line->moudle_point(this->sys_flag->move,oldpos,this->custom_menu->group_interval,false,index,true);
    }
    else
    {
        flag=this->line->moudle_point(this->sys_flag->move,oldpos,this->custom_menu->group_interval,true,index,false);
    }
    if(flag==1)
    {
        moudle->input[index]->connect_line.push_back(this->line->group[this->line->current_id]);//input node
        return true;
    }
    else if(flag==2)
    {
        moudle->output[index]->connect_line.push_back(this->line->group[this->line->current_id]);//output node
        return true;
    }
    else
        return false;
}
//detect the node of moudle while be chosened
void MainWindow::Rect_detect()
{
    selectall(this->sys_flag->move->x()-1,this->sys_flag->move->y()-1,this->sys_flag->move->x()+this->sys_flag->move->width()+1,this->sys_flag->move->y()+this->sys_flag->move->height()+1);
}
//draw line
void MainWindow::single_click()
{
    Rect_detect();
    update();
    if(this->sys_flag->move_flag)
        this->sys_flag->move_flag=0;
    if(this->sys_flag->draw_flag)
        this->sys_flag->draw_flag=false;
    //qDebug()<<this->sys_flag->draw_flag;
    //resert_flag();
}//按钮单击事件
void MainWindow::double_click()
{
    Simulation_Moudle* moudle=this->simulation_group->findwithbutton(this->sys_flag->move);
    dialog=new paramdialog(this,moudle,sys_flag);
    this->parent->select_flag=false;//调用对话框后，系统会调用每个类的update
    //qDebug()<<this->sys_flag->tag_group[0]<<dialog->tag_group[0];
    if(dialog->exec())
    {
        moudle->name=dialog->nameText->text();
        update_label_pos(moudle->button);
        if(moudle->index==0)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
        }
        else if(moudle->index==1)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
        }
        else if(moudle->index==2)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->param[1]=dialog->param[1]->text().toDouble();
        }
        else if(moudle->index==3)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->param[1]=dialog->param[1]->text().toDouble();
        }
        else if(moudle->index==4)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->param[1]=dialog->param[1]->text().toDouble();
            moudle->param[2]=dialog->param[2]->text().toDouble();
        }
        else if(moudle->index==5||moudle->index==14||moudle->index==15)
        {
            int count=moudle->time_sequence.size();
            for(int j=0;j<count;j++)
                moudle->time_sequence.removeAt(0);
            count=moudle->value_sequence.size();
            for(int j=0;j<count;j++)
                moudle->value_sequence.removeAt(0);

            moudle->time=dialog->param[0]->text();
            moudle->value=dialog->param[1]->text();
            QString time,value;
            time="";
            value="";
            for(int i=0;i<moudle->time.size();i++)
            {
                if(moudle->time.at(i)!=',')
                {
                    time+=moudle->time.at(i);
                }
                else
                {
                    moudle->time_sequence.push_back(time.toDouble());
                    time="";
                }
            }
            if(time!="")
                moudle->time_sequence.push_back(time.toDouble());
            for(int i=0;i<moudle->value.size();i++)
            {
                if(moudle->value.at(i)!=',')
                {
                    value+=moudle->value.at(i);
                }
                else
                {
                    //qDebug()<<value.toDouble();
                    moudle->value_sequence.push_back(value.toDouble());
                    value="";
                }
            }
            if(value!="")
            {
                moudle->value_sequence.push_back(value.toDouble());
                //qDebug()<<value.toDouble();
            }
            if(moudle->index==14)
            {
                QString display="";
                int index=0;//记录重复位置
                int cou=0;//记录重复个数
                for(int i=0;i<moudle->time_sequence.size()/2;i++)
                {
                    if((moudle->time_sequence[2*i])!=0.0)
                    {
                        QString temp;
                        if((moudle->time_sequence[2*i])!=1.0)
                        {
                            temp=QString::number(moudle->time_sequence[2*i])+"s";
                        }
                        else
                           temp="s";
                        display+="("+temp;
                        if((moudle->time_sequence[2*i+1])!=0.0)
                        {
                            if(cou>=2)
                                display.insert(index,"^"+QString::number(cou));
                            display+="+"+QString::number(moudle->time_sequence[2*i+1])+")";
                            index=0;
                            cou=0;
                        }
                        else
                        {
                            if(cou==0)
                            {
                                display.remove(display.size()-1-temp.size(),1);
                                index=display.size();
                            }
                            else
                            {
                                display.remove(display.size()-2-temp.size(),2);
                            }
                            cou++;
                        }
                    }
                    else
                    {
                        if(cou>=2)
                            display.insert(index,"^"+QString::number(cou));
                        index=0;
                        cou=0;

                        if((moudle->time_sequence[2*i+1])!=0.0)
                            display+=QString::number(moudle->time_sequence[2*i+1]);
                    }
                }
                if(cou>=2)
                    display.insert(index,"^"+QString::number(cou));
                index=0;
                cou=0;

                moudle->time=display;
                moudle->fenmu->setText(moudle->time);
                display="";
                for(int i=0;i<moudle->value_sequence.size()/2;i++)
                {
                    if((moudle->value_sequence[2*i])!=0.0)
                    {
                        QString temp;
                        if((moudle->value_sequence[2*i])!=1.0)
                        {
                            temp=QString::number(moudle->value_sequence[2*i])+"s";
                        }
                        else
                           temp="s";
                        display+="("+temp;
                        if((moudle->value_sequence[2*i+1])!=0.0)
                        {
                            if(cou>=2)
                                display.insert(index,"^"+QString::number(cou));
                            display+="+"+QString::number(moudle->value_sequence[2*i+1])+")";
                            index=0;
                            cou=0;
                        }
                        else
                        {
                            if(cou==0)
                            {
                                display.remove(display.size()-1-temp.size(),1);
                                index=display.size();
                            }
                            else
                            {
                                display.remove(display.size()-2-temp.size(),2);
                            }
                            cou++;
                        }
                    }
                    else
                    {
                        if(cou>=2)
                            display.insert(index,"^"+QString::number(cou));
                        index=0;
                        cou=0;

                        if((moudle->value_sequence[2*i+1])!=0.0)
                            display+=QString::number(moudle->value_sequence[2*i+1]);
                    }
                }
                if(cou>=2)
                    display.insert(index,"^"+QString::number(cou));
                index=0;
                cou=0;

                moudle->value=display;
                moudle->fenzi->setText(moudle->value);
            }
            else if(moudle->index==15)//传递函数分母分子展开式
            {
                QString display="";
                for(int i=0;i<moudle->time_sequence.size();i++)
                {
                    int index=moudle->time_sequence.size()-1-i;
                    if((moudle->time_sequence[index])!=0.0)
                    {
                        if(index>=2)
                        {
                            if((moudle->time_sequence[index])!=1.0)
                                display+=QString::number(moudle->time_sequence[index])+"s^"+QString::number(index)+"+";
                            else
                                display+="s^"+QString::number(index)+"+";
                        }
                        else if(index>=1)
                        {
                            if((moudle->time_sequence[index])!=1.0)
                                display+=QString::number(moudle->time_sequence[index])+"s+";
                            else
                                display+="s+";
                        }
                        else
                        {
                            display+=QString::number(moudle->time_sequence[index]);
                        }
                    }
                }
                if(display[display.size()-1]=='+')
                    display.remove(display.size()-1,1);
                moudle->time=display;
                moudle->fenmu->setText(moudle->time);

                display="";
                for(int i=0;i<moudle->value_sequence.size();i++)
                {
                    int index=moudle->value_sequence.size()-1-i;
                    if((moudle->value_sequence[index])!=0.0)
                    {
                        if(index>=2)
                        {
                            if((moudle->value_sequence[index])!=1.0)
                                display+=QString::number(moudle->value_sequence[index])+"s^"+QString::number(index)+"+";
                            else
                                display+="s^"+QString::number(index)+"+";
                        }
                        else if(index>=1)
                        {
                            display+=QString::number(moudle->value_sequence[index])+"s+";
                        }
                        else
                        {
                            display+=QString::number(moudle->value_sequence[index]);
                        }
                    }
                }
                if(display[display.size()-1]=='+')
                    display.remove(display.size()-1,1);
                moudle->value=display;
                moudle->fenzi->setText(moudle->value);
            }

        }
        else if(moudle->index==7)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->param[1]=dialog->param[1]->text().toDouble();
        }
        else if(moudle->index==8)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->value=QString::number(moudle->param[0]);
            moudle->fenzi->setText(moudle->value);
        }
        else if(moudle->index==9)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->value="e^"+QString::number(moudle->param[0])+"s";
            moudle->fenzi->setText(moudle->value);
        }
        else if(moudle->index==10)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->value=QString::number(moudle->param[0])+"/s";
            moudle->fenzi->setText(moudle->value);
        }
        else if(moudle->index==11)//微分
        {
        }
        else if(moudle->index==12)//一阶惯性
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->param[1]=dialog->param[1]->text().toDouble();
            moudle->value=QString::number(moudle->param[0]);
            if((moudle->param[1])!=1.0)
            {
                moudle->time=QString::number(moudle->param[1])+"s+1";
            }
            else
                moudle->time="s+1";

            moudle->fenzi->setText(moudle->value);
            moudle->fenmu->setText(moudle->time);
        }
        else if(moudle->index==13)//n阶惯性
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->param[1]=dialog->param[1]->text().toDouble();
            moudle->param[2]=dialog->param[2]->text().toDouble();//阶数
            moudle->value=QString::number(moudle->param[0]);
            if((moudle->param[1])!=1.0)
                moudle->time="("+QString::number(moudle->param[1])+"s+"+"1)";
            else
                moudle->time="(s+1)";
            if((moudle->param[2])!=1.0)
                moudle->time+="^"+QString::number(moudle->param[2]);
            moudle->fenzi->setText(moudle->value);
            moudle->fenmu->setText(moudle->time);
        }
        else if(moudle->index==20)//正三角
        {
            if(dialog->index!=-1)
                moudle->param[0]=dialog->index;
        }
        else if(moudle->index==21)//反三角
        {
            if(dialog->index!=-1)
                moudle->param[0]=dialog->index;
        }
        else if(moudle->index==27)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->value="x"+(moudle->param[0]==1.0?"":"^"+QString::number(moudle->param[0]));
            moudle->fenzi->setText(moudle->value);
        }
        else if(moudle->index==29)
        {
            if(change_input_count(moudle,int(dialog->param[0]->text().toDouble())))
            {
                moudle->param[0]=int(dialog->param[0]->text().toDouble());
                moudle->input_size=int(moudle->param[0]);
                updatenode(moudle);
            }
        }
        else if(moudle->index==30)//乘除
        {
            if(dialog->index!=-1)
                moudle->param[0]=dialog->index;
            if(int(moudle->param[0])==0)
                moudle->value="x";
            else
                moudle->value="/";
            moudle->fenzi->setText(moudle->value);
        }
        else if(moudle->index==31)
        {
            moudle->param[0]=dialog->param[0]->text().toDouble();
            moudle->param[1]=dialog->param[1]->text().toDouble();
            moudle->value=(moudle->param[0]==1.0?"":QString::number(moudle->param[0]))+"x+"+QString::number(moudle->param[1]);
            moudle->fenzi->setText(moudle->value);
        }
        else if(moudle->index==32)//逻辑运算> <
        {
            if(dialog->index!=-1)
            {
                if(int(dialog->index)!=5)
                {
                    if(change_input_count(moudle,2))
                    {
                        moudle->input_size=2;
                        moudle->param[0]=dialog->index;
                        updatenode(moudle);
                    }
                }
                else
                {
                    if(change_input_count(moudle,1))
                    {
                        moudle->input_size=1;
                        moudle->param[0]=dialog->index;
                        updatenode(moudle);
                    }
                }
                switch (int(moudle->param[0]))
                {
                case 0:{moudle->value=">";};break;
                case 1:{moudle->value="<";};break;
                case 2:{moudle->value="=";};break;
                case 3:{moudle->value="&&";};break;
                case 4:{moudle->value="||";};break;
                case 5:{moudle->value="!";};break;
                default:break;
                }
                moudle->fenzi->setText(moudle->value);
            }
        }
        else if(moudle->index==33)//逻辑& | ~
        {
            if(dialog->index!=-1)
            {
                if(int(dialog->index)!=2)
                {
                    if(change_input_count(moudle,2))
                    {
                        moudle->input_size=2;
                        moudle->param[0]=dialog->index;
                        updatenode(moudle);
                    }
                }
                else
                {
                    if(change_input_count(moudle,1))
                    {
                        moudle->input_size=1;
                        moudle->param[0]=dialog->index;
                        updatenode(moudle);
                    }
                }
                switch (int(moudle->param[0]))
                {
                case 0:{moudle->value="&";};break;
                case 1:{moudle->value="|";};break;
                case 2:{moudle->value="~";};break;
                default:break;
                }
                moudle->fenzi->setText(moudle->value);
            }
        }
        else if(moudle->index==34)//最值
        {
            if(change_input_count(moudle,int(dialog->param[0]->text().toDouble())))
            {
                moudle->param[0]=int(dialog->param[0]->text().toDouble());
                moudle->input_size=int(moudle->param[0]);
                updatenode(moudle);
            }
            if(dialog->index!=-1)
            {
                moudle->param[1]=dialog->index;
                if(int(moudle->param[1])==0)
                    moudle->value="MAX";
                else if(int(moudle->param[1])==1)
                    moudle->value="MIN";
                moudle->fenzi->setText(moudle->value);
            }
        }
        else if(moudle->index==35)
        {
            if(change_output_count(moudle,int(dialog->param[0]->text().toDouble())))
            {
                moudle->param[0]=int(dialog->param[0]->text().toDouble());
                moudle->output_size=int(moudle->param[0]);
                updatenode(moudle);
            }
        }
        else if(moudle->index==36)
        {
            if(change_input_count(moudle,int(dialog->param[0]->text().toDouble())+1))
            {
                moudle->param[0]=int(dialog->param[0]->text().toDouble());
                moudle->input_size=int(moudle->param[0])+1;
                updatenode(moudle);
            }
        }
        else if(moudle->index==38)//interface
        {

            for(int m=0;m<dialog->interface->address_input.size();m++)
                moudle->bind_interface->input_ip[m]=dialog->interface->address_input[m]->text().toInt();
            moudle->bind_interface->input_port=dialog->interface->port_input->text().toInt();
            for(int m=0;m<dialog->interface->address_output.size();m++)
                moudle->bind_interface->output_ip[m]=dialog->interface->address_output[m]->text().toInt();
            moudle->bind_interface->output_port=dialog->interface->port_output->text().toInt();

            if(dialog->interface->input_flag==false)
            {
                moudle->bind_interface->input_flag=false;
                if(moudle->input.size()==0)
                {
                    moudle->input_size=1;
                    moudle->input.push_back(new moudle_param());
                }
            }
            else
            {
                if(moudle->input.size()>=1)
                {
                    moudle->input_size=0;
                    //moudle->input.removeAt(0);
                    moudle->input.clear();
                }
                moudle->bind_interface->input_flag=true;
            }
            if(dialog->interface->output_flag==false)
            {
                moudle->bind_interface->output_flag=false;
                if(moudle->output.size()==0)
                {
                    moudle->output_size=1;
                    moudle->output.push_back(new moudle_param());
                }
            }
            else
            {
                if(moudle->output.size()>=1)
                {
                    moudle->output_size=0;
                    //moudle->output.removeAt(0);
                    moudle->output.clear();
                }
                moudle->bind_interface->output_flag=true;
            }

        }
        else if(moudle->index==39)
        {
            if(dialog->bind->input_tag==""||dialog->bind->input_tag=="-1")
                dialog->bind->input_tag="-1";
            if(dialog->bind->output_tag==""||dialog->bind->output_tag=="-1")
                dialog->bind->output_tag="-1";

            if(dialog->bind->input_flag==false)
            {
                moudle->tag_bind->input_tag=dialog->bind->input_tag;
                moudle->tag_bind->input_flag=false;
                if(moudle->input.size()==0)
                {
                    moudle->input_size=1;
                    moudle->input.push_back(new moudle_param());
                }
                QString str=this->sys_flag->input_bind.key(moudle);
                if(str!="")
                    this->sys_flag->input_bind.remove(str);
            }
            else
            {
                moudle->tag_bind->input_tag=dialog->bind->input_tag;
                if(moudle->tag_bind->input_tag!="-1")
                {
                    if(moudle->input.size()>=1)
                    {
                        moudle->input_size=0;
                        //moudle->input.removeAt(0);
                        moudle->input.clear();
                    }
                    moudle->tag_bind->input_flag=true;
                    QString str=this->sys_flag->input_bind.key(moudle);
                    if(str=="")
                    {
                        this->sys_flag->input_bind.insert(moudle->tag_bind->input_tag,moudle);
                    }
                    else
                    {
                        this->sys_flag->input_bind.remove(str);
                        this->sys_flag->input_bind.insert(moudle->tag_bind->input_tag,moudle);
                    }
                }
            }
            if(dialog->bind->output_flag==false)
            {
                moudle->tag_bind->output_tag=dialog->bind->output_tag;
                moudle->tag_bind->output_flag=false;
                if(moudle->output.size()==0)
                {
                    moudle->output_size=1;
                    moudle->output.push_back(new moudle_param());
                }
                QString str=this->sys_flag->output_bind.key(moudle);
                if(str!="")
                    this->sys_flag->output_bind.remove(str);
            }
            else
            {
                moudle->tag_bind->output_tag=dialog->bind->output_tag;
                if(moudle->tag_bind->output_tag!="-1")
                {
                    if(moudle->output.size()>=1)
                    {
                        moudle->output_size=0;
                        //moudle->output.removeAt(0);
                        moudle->output.clear();
                    }
                    moudle->tag_bind->output_flag=true;
                    QString str=this->sys_flag->output_bind.key(moudle);
                    if(str=="")
                    {
                        this->sys_flag->output_bind.insert(moudle->tag_bind->output_tag,moudle);
                    }
                    else
                    {
                        this->sys_flag->output_bind.remove(str);
                        this->sys_flag->output_bind.insert(moudle->tag_bind->output_tag,moudle);
                    }
                }
            }
            //qDebug()<<this->sys_flag->input_bind.size()<<this->sys_flag->output_bind.size();
        }
        else
        {
            if(this->sys_flag->param[moudle->index]>=2)
            {
                if(change_input_count(moudle,int(dialog->param[0]->text().toDouble())))
                {
                    moudle->param[0]=int(dialog->param[0]->text().toDouble());
                    moudle->input_size=int(moudle->param[0]);
                    updatenode(moudle);
                }
                if(change_output_count(moudle,int(dialog->param[1]->text().toDouble())))
                {
                    moudle->param[1]=int(dialog->param[1]->text().toDouble());
                    moudle->output_size=int(moudle->param[1]);
                    updatenode(moudle);
                }
            }

            for(int i=2;i<this->sys_flag->param[moudle->index];i++)
                moudle->param[i]=dialog->param[i]->text().toDouble();
        }

       // change_io_count(moudle,int(moudle->param[0]),int(moudle->param[1]));

    }
    delete dialog;
    dialog=nullptr;
    this->sys_flag->move_flag=false;
   // qDebug()<<sys_flag->move->geometry();
}//按钮双击事件
void MainWindow::interface_expand(Simulation_Moudle* moudle,int way)
{
    int count=moudle->button->height()/25;
    if(way==0||way==2)
        if(change_input_count(moudle,count))
        {
            if(moudle->index==29)
            {
                moudle->param[0]=int(count);
                moudle->input_size=int(moudle->param[0]);
            }
            updatenode(moudle);
        }
    if(way==1||way==2)
        if(change_output_count(moudle,count))
        {
            //moudle->param[1]=int(count);
            //moudle->output_size=int(moudle->param[1]);
            if(moudle->index==38||moudle->index==39)
                moudle->output_size=count;
            updatenode(moudle);
        }
}
QPoint* MainWindow::transform_position(QWidget* w1,QWidget* w2,QPoint* pos)
{
    int x;
    int y;
    x=w2->mapFromGlobal(w1->mapToGlobal(*pos)).x();
    y=w2->mapFromGlobal(w1->mapToGlobal(*pos)).y();
    return new QPoint(x,y);

}
void MainWindow::setsize(Button* button,int width,int height)
{
    int x=button->x();
    int y=button->y();
    button->setGeometry(x,y,this->sys_flag->button_width+width-10,this->sys_flag->button_height+height-10);
}
void MainWindow::on_linear_pressed()
{
    int index;
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    index=findindex_button(button);
    sys_flag->move_flag=1;
    sys_flag->move=new Button();
    //sys_flag->move=new custombutton();//自定义button,便于重写paint
   // sys_flag->move->setIcon(*Interface->image[0]);
    //sys_flag->move->setStyleSheet(Interface->prefix+Interface->url[index]);
    sys_flag->move->setVisible(true);
    //sys_flag->move->setText(tr("m1"));
    sys_flag->move->setGeometry(button->geometry());
    moudletogroup(sys_flag->move,index,false);
    //connect(new QPushButton(), &QAbstractButton::pressed, new MainWindow(this), &MainWindow::mmove);
    //connect(sys_flag->move, &QAbstractButton::clicked, this, &MainWindow::button_click);
    //connect(sys_flag->move, &QAbstractButton::released, this, &MainWindow::mreleased);
   // qDebug()<<(ui->centralWidget->mapFromGlobal(QCursor::pos()));
   // qDebug()<<(ui->centralWidget->mapFromGlobal(QCursor::pos()));
}
void MainWindow::update_label_pos(Button* button)//更新标签位置
{
    Simulation_Moudle* moudle=this->simulation_group->findwithbutton(button);
    QLabel* label=moudle->label;
    label->setText(moudle->name);
    label->setVisible(true);
    label->setAlignment(Qt::AlignHCenter);
    label->resize(60,20);
    label->setGeometry(moudle->button->x()+moudle->button->width()/2-label->width()/2,moudle->button->y()+moudle->button->height()+1,label->width(),label->height());
    if(moudle->index==12||moudle->index==13||moudle->index==14||moudle->index==15)
    {
        label=moudle->fenmu;
        label->setText(moudle->time);
        label->setVisible(true);
        label->setAlignment(Qt::AlignHCenter);
        label->resize(moudle->button->width()-2,20);
        label->setGeometry(moudle->button->x()+moudle->button->width()/2-label->width()/2,moudle->button->y()+moudle->button->height()/2+3,label->width(),label->height());
        label=moudle->fenzi;
        label->setText(moudle->value);
        label->setVisible(true);
        label->setAlignment(Qt::AlignHCenter);
        label->resize(moudle->button->width()-2,20);
        label->setGeometry(moudle->button->x()+moudle->button->width()/2-label->width()/2,moudle->button->y()+moudle->button->height()/2-label->height()/2-4,label->width(),label->height());
    }
    else if(moudle->index==8||moudle->index==9||moudle->index==10||moudle->index==11||moudle->index==19||moudle->index==22||moudle->index==23||moudle->index==24||moudle->index==25||moudle->index==26||moudle->index==27||moudle->index==28||moudle->index==29||moudle->index==30||moudle->index==31||moudle->index==32||moudle->index==33||moudle->index==34||moudle->index==39||moudle->index==40||moudle->index==41||moudle->index==38)
    {
        label=moudle->fenzi;
        label->setVisible(true);
        label->setAlignment(Qt::AlignHCenter);
        label->resize(moudle->button->width()-2,20);
        label->setGeometry(moudle->button->x()+moudle->button->width()/2-label->width()/2,moudle->button->y()+moudle->button->height()/2-label->height()/2+2,label->width(),label->height());
    }
    this->modify=true;//当前文件已经被修改
    //this->sys_flag->move->installEventFilter(this);
}
int MainWindow::findindex_button(QPushButton* button)
{
    int index=0;
    for(int i=0;i<this->custom_menu->buttom_group.size();i++)
    {
        QButtonGroup* group=this->custom_menu->buttom_group[i];
        foreach(QAbstractButton* but,group->buttons())
        {
            if(but==button)
                return index;
            index++;
        }
    }
    return 0;
}
void MainWindow::moudletogroup(Button* button,int index,bool flag)
{
    this->simulation_moudle=new Simulation_Moudle();
    this->simulation_moudle->button=button;
    this->simulation_moudle->setposition();
    this->simulation_moudle->id=this->sys_flag->button_id++;//唯一标识
    if(flag)
    {
        this->simulation_moudle->name=this->parent->copy_moudle_group->moudle_group[index]->name;
        this->simulation_moudle->label=new QLabel(this);
        this->simulation_moudle->index=this->parent->copy_moudle_group->moudle_group[index]->index;
        this->simulation_moudle->input_size=this->parent->copy_moudle_group->moudle_group[index]->input_size;
        this->simulation_moudle->output_size=this->parent->copy_moudle_group->moudle_group[index]->output_size;
        for(int i=0;i<this->parent->copy_moudle_group->moudle_group[index]->param.size();i++)
            this->simulation_moudle->param.push_back(this->parent->copy_moudle_group->moudle_group[index]->param[i]);
        if(this->simulation_moudle->index==5)//自定义输出序列
        {
            this->simulation_moudle->time=this->parent->copy_moudle_group->moudle_group[index]->time;
            this->simulation_moudle->value=this->parent->copy_moudle_group->moudle_group[index]->value;
            this->simulation_moudle->time_sequence=this->parent->copy_moudle_group->moudle_group[index]->time_sequence;
            this->simulation_moudle->value_sequence=this->parent->copy_moudle_group->moudle_group[index]->value_sequence;
            this->simulation_moudle->param[2]=0;
        }
        else if(this->simulation_moudle->index==12||this->simulation_moudle->index==13||this->simulation_moudle->index==14||this->simulation_moudle->index==15)
        {
            this->simulation_moudle->fenmu=new QLabel(this);
            this->simulation_moudle->fenmu->setVisible(true);
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->fenzi->setVisible(true);
            this->simulation_moudle->time=this->parent->copy_moudle_group->moudle_group[index]->time;
            this->simulation_moudle->value=this->parent->copy_moudle_group->moudle_group[index]->value;
            if(this->simulation_moudle->index==14||this->simulation_moudle->index==15)
            {
                this->simulation_moudle->time_sequence=this->parent->copy_moudle_group->moudle_group[index]->time_sequence;
                this->simulation_moudle->value_sequence=this->parent->copy_moudle_group->moudle_group[index]->value_sequence;
            }
        }
        else if(this->simulation_moudle->index==8||this->simulation_moudle->index==9||this->simulation_moudle->index==10||this->simulation_moudle->index==11||this->simulation_moudle->index==19||this->simulation_moudle->index==22||this->simulation_moudle->index==23||this->simulation_moudle->index==24||this->simulation_moudle->index==25||this->simulation_moudle->index==26||this->simulation_moudle->index==27||this->simulation_moudle->index==28||this->simulation_moudle->index==29||this->simulation_moudle->index==30||this->simulation_moudle->index==31||this->simulation_moudle->index==32||this->simulation_moudle->index==33||this->simulation_moudle->index==34||this->simulation_moudle->index==40||this->simulation_moudle->index==41)
        {
            this->simulation_moudle->value=this->parent->copy_moudle_group->moudle_group[index]->value;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
            this->simulation_moudle->fenzi->setVisible(true);
        }
        else if(this->simulation_moudle->index==38)//接口模块
        {
            this->simulation_moudle->value=this->parent->copy_moudle_group->moudle_group[index]->value;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
            this->simulation_moudle->fenzi->setVisible(true);
            this->simulation_moudle->bind_interface=new interface_bind(*this->parent->copy_moudle_group->moudle_group[index]->bind_interface);
            this->simulation_moudle->bind_interface->input_socket=new QTcpSocket(this);
            connect(this->simulation_moudle->bind_interface->input_socket,&QTcpSocket::connected,this,&MainWindow::socket_connect);
            connect(this->simulation_moudle->bind_interface->input_socket,&QTcpSocket::disconnected,this,&MainWindow::socket_disconnect);
            connect(this->simulation_moudle->bind_interface->input_socket,&QIODevice::readyRead,this,&MainWindow::socket_receive);
            this->simulation_moudle->bind_interface->output_socket=new QTcpSocket(this);
            connect(this->simulation_moudle->bind_interface->output_socket,&QTcpSocket::connected,this,&MainWindow::socket_connect);
            connect(this->simulation_moudle->bind_interface->output_socket,&QTcpSocket::disconnected,this,&MainWindow::socket_disconnect);
            //connect(this->simulation_moudle->bind_interface->output_socket,&QIODevice::readyRead,this,&MainWindow::socket_receive);
        }
        else if(this->simulation_moudle->index==39)//tag_bind
        {
            this->simulation_moudle->value=this->parent->copy_moudle_group->moudle_group[index]->value;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
            this->simulation_moudle->fenzi->setVisible(true);
            this->simulation_moudle->tag_bind=new bind_tag();
            Simulation_Moudle* moudle=this->parent->copy_moudle_group->moudle_group[index];
            this->simulation_moudle->tag_bind->input_flag=moudle->tag_bind->input_flag;
            this->simulation_moudle->tag_bind->output_flag=moudle->tag_bind->output_flag;
            this->simulation_moudle->tag_bind->input_tag=moudle->tag_bind->input_tag;
            this->simulation_moudle->tag_bind->output_tag=moudle->tag_bind->output_tag;
            if(this->simulation_moudle->tag_bind->input_flag==true&&this->simulation_moudle->tag_bind->input_tag!="-1")
            {
                this->remove_tag(this->simulation_moudle->tag_bind->input_tag);
                this->sys_flag->input_bind.insert(this->simulation_moudle->tag_bind->input_tag,this->simulation_moudle);
            }
            if(this->simulation_moudle->tag_bind->output_flag==true&&this->simulation_moudle->tag_bind->output_tag!="-1")
            {
                this->remove_tag(this->simulation_moudle->tag_bind->output_tag);
                this->sys_flag->output_bind.insert(this->simulation_moudle->tag_bind->output_tag,this->simulation_moudle);
            }
        }
       // qDebug()<<this->sys_flag->copy_moudle->param;
    }
    else
    {       
        /*
    this->sys_flag->param[0]=1;//线性信号源
    this->sys_flag->param[1]=1;//阶跃信号
    this->sys_flag->param[2]=2;//正弦信号
    this->sys_flag->param[8]=1;//常数
    this->sys_flag->param[9]=1;//延时环节
    this->sys_flag->param[10]=2;//积分
    this->sys_flag->param[12]=2;//一阶惯性
    this->sys_flag->param[37]=0;//图表
*/       
        this->simulation_moudle->index=index;
        this->simulation_moudle->label=new QLabel(this);
        //qDebug()<<this->sys_flag->label_count[0]<<this->sys_flag->label_count[index];
        this->simulation_moudle->name=this->sys_flag->name[index]+QString::number(this->sys_flag->label_count[index]++);
        for(int i=0;i<this->sys_flag->param[index];i++)
            this->simulation_moudle->param.push_back(1);
        if(this->simulation_moudle->index==0)
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;           
        }
        else if(this->simulation_moudle->index==1)
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;
        }
        else if(this->simulation_moudle->index==2)
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;
        }
        else if(this->simulation_moudle->index==3)
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;
        }
        else if(this->simulation_moudle->index==4)
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;
        }
        else if(this->simulation_moudle->index==5)
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->time="1,2,3,4,5";
            this->simulation_moudle->value="1,2,3,4,5";
        }
        else if(this->simulation_moudle->index==6)
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;
        }
        else if(this->simulation_moudle->index==7)
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;
        }
        else if(this->simulation_moudle->index==8)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->value=QString::number(this->simulation_moudle->param[0]);
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==9)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->value="e^"+QString::number(this->simulation_moudle->param[0])+"s";
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==10)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value=QString::number(this->simulation_moudle->param[0])+"/s";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==11)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="s";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==12)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->fenmu=new QLabel(this);
            this->simulation_moudle->value="1";
            this->simulation_moudle->time="s+1";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
            this->simulation_moudle->fenmu->setText(this->simulation_moudle->time);

        }
        else if(this->simulation_moudle->index==13)
        {
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->fenmu=new QLabel(this);
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->value="1";
            this->simulation_moudle->time="(s+1)";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
            this->simulation_moudle->fenmu->setText(this->simulation_moudle->time);
        }
        else if(this->simulation_moudle->index==14||this->simulation_moudle->index==15)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->fenmu=new QLabel(this);

            this->simulation_moudle->value="1";
            if(this->simulation_moudle->index==14)
            {
                this->simulation_moudle->value_sequence.push_back(0);
                this->simulation_moudle->value_sequence.push_back(1);
            }
            else
            {
                this->simulation_moudle->value_sequence.push_back(1);
                this->simulation_moudle->value_sequence.push_back(0);
            }
            this->simulation_moudle->time_sequence.push_back(1);
            this->simulation_moudle->time_sequence.push_back(1);
            this->simulation_moudle->time="s+1";

            this->simulation_moudle->fenzi->setText("1");
            this->simulation_moudle->fenmu->setText("s+1");
        }
        else if(this->simulation_moudle->index==19)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="1/x";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==20)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->param[0]=0;
        }
        else if(this->simulation_moudle->index==21)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->param[0]=0;
        }
        else if(this->simulation_moudle->index==22)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="|x|";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==23)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="SGN";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==24)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="ln";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==25)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="log10";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==26)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="e^x";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==27)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="x"+(this->simulation_moudle->param[0]==1.0?"":"^"+QString::number(this->simulation_moudle->param[0]));
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==28)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="sqrt(x)";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==29)
        {
            this->simulation_moudle->input_size=2;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->param[0]=2;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="+";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==30)
        {
            this->simulation_moudle->input_size=2;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->param[0]=0;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="x";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==31)
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="x+1";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==32)
        {
            this->simulation_moudle->input_size=2;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->param[0]=0;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value=">";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==33)
        {
            this->simulation_moudle->input_size=2;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->param[0]=0;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="&";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==34)
        {
            this->simulation_moudle->input_size=2;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->param[0]=2;
            this->simulation_moudle->param[1]=0;

            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="MAX";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==35)//输出多选一
        {
            this->simulation_moudle->input_size=2;
            this->simulation_moudle->output_size=2;
            this->simulation_moudle->param[0]=2;
        }
        else if(this->simulation_moudle->index==36)//输入多选一
        {
            this->simulation_moudle->input_size=3;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->param[0]=2;
        }
        else if(this->simulation_moudle->index==37)//曲线
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=0;
        }
        else if(this->simulation_moudle->index==38)//AD
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=0;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="interface";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);

            this->simulation_moudle->bind_interface=new interface_bind();
            this->simulation_moudle->bind_interface->input_socket=new QTcpSocket(this);
            connect(this->simulation_moudle->bind_interface->input_socket,&QTcpSocket::connected,this,&MainWindow::socket_connect);
            connect(this->simulation_moudle->bind_interface->input_socket,&QTcpSocket::disconnected,this,&MainWindow::socket_disconnect);
            connect(this->simulation_moudle->bind_interface->input_socket,&QIODevice::readyRead,this,&MainWindow::socket_receive);
            this->simulation_moudle->bind_interface->input_ip.push_back(192);
            this->simulation_moudle->bind_interface->input_ip.push_back(168);
            this->simulation_moudle->bind_interface->input_ip.push_back(1);
            this->simulation_moudle->bind_interface->input_ip.push_back(1);
            this->simulation_moudle->bind_interface->input_port=8080;

            this->simulation_moudle->bind_interface->output_socket=new QTcpSocket(this);
            connect(this->simulation_moudle->bind_interface->output_socket,&QTcpSocket::connected,this,&MainWindow::socket_connect);
            connect(this->simulation_moudle->bind_interface->output_socket,&QTcpSocket::disconnected,this,&MainWindow::socket_disconnect);
            //connect(this->simulation_moudle->bind_interface->output_socket,&QIODevice::readyRead,this,&MainWindow::socket_receive);
            this->simulation_moudle->bind_interface->output_ip.push_back(192);
            this->simulation_moudle->bind_interface->output_ip.push_back(168);
            this->simulation_moudle->bind_interface->output_ip.push_back(1);
            this->simulation_moudle->bind_interface->output_ip.push_back(1);
            this->simulation_moudle->bind_interface->output_port=8080;

        }
        else if(this->simulation_moudle->index==39)//DA
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="bind";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
            this->simulation_moudle->tag_bind=new bind_tag();
        }
        else if(this->simulation_moudle->index==40)//DI
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="DI";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else if(this->simulation_moudle->index==41)//DO
        {
            this->simulation_moudle->input_size=0;
            this->simulation_moudle->output_size=1;
            this->simulation_moudle->fenzi=new QLabel(this);
            this->simulation_moudle->value="DO";
            this->simulation_moudle->fenzi->setText(this->simulation_moudle->value);
        }
        else
        {
            this->simulation_moudle->input_size=1;
            this->simulation_moudle->output_size=1;
        }

    }
    for(int i=0;i<this->simulation_moudle->input_size;i++)
        this->simulation_moudle->input.push_back(new moudle_param());
    for(int i=0;i<this->simulation_moudle->output_size;i++)
        this->simulation_moudle->output.push_back(new moudle_param());
    this->simulation_group->group.append(this->simulation_moudle);

    update_label_pos(button);//更显标签位置
}
bool MainWindow::change_input_count(Simulation_Moudle* moudle,int input)
{
    io_count count;
    int index=0;
    moudle_param* param;
    int temp;
    count=get_io_count(moudle);
    if(count.input<=input)
    {
        for(int i=0;i<moudle->input_size;i++)
        {
            if(moudle->input[i]->connect_line.size()!=0)
            {
                if(index!=i)
                {
                    for(int j=0;j<moudle->input[i]->connect_line.size();j++)
                    {
                        temp=this->line->findindex_output(moudle->input[i]->connect_line[j],moudle->button);
                        moudle->input[i]->connect_line[j]->endindex[temp]=index;
                    }
                    param=moudle->input[index];
                    moudle->input[index]=moudle->input[i];
                    moudle->input[i]=param;
                }

                index++;
            }
        }
        if(moudle->input_size<input)
        {
            for(int i=0;i<(input-moudle->input_size);i++)
                moudle->input.push_back(new moudle_param());
        }
        else
        {
            for(int i=0;i<(moudle->input_size-input);i++)
            {
                moudle->input.pop_back();
            }
        }
        return true;
    }
    return false;
}
bool MainWindow::change_output_count(Simulation_Moudle* moudle,int output)
{
    io_count count;
    int index=0;
    moudle_param* param;
    int temp;
    count=get_io_count(moudle);  
    if(count.output<=output)
    {
        for(int i=0;i<moudle->output_size;i++)
        {
            if(moudle->output[i]->connect_line.size()!=0)
            {
                if(index!=i)
                {
                    for(int j=0;j<moudle->output[i]->connect_line.size();j++)
                    {
                        temp=this->line->findindex_input();
                        moudle->output[i]->connect_line[j]->startindex[temp]=index;
                    }
                    param=moudle->output[index];
                    moudle->output[index]=moudle->output[i];
                    moudle->output[i]=param;
                }

                index++;
            }
        }
        if(moudle->output_size<output)
        {
            for(int i=0;i<(output-moudle->output_size);i++)
                moudle->output.push_back(new moudle_param());
        }
        else
        {
            for(int i=0;i<(moudle->output_size-output);i++)
            {
                moudle->output.pop_back();
            }
        }
        return true;
    }
    return false;
}
io_count MainWindow::get_io_count(Simulation_Moudle* moudle)
{
    io_count count;
    count.input=0;
    count.output=0;
    for(int i=0;i<moudle->input_size;i++)
        if(moudle->input[i]->connect_line.size()!=0)
            count.input++;

    for(int i=0;i<moudle->output_size;i++)
        if(moudle->output[i]->connect_line.size()!=0)
            count.output++;
    return count;
}
void MainWindow::updatenode(Simulation_Moudle* moudle)
{
    QPoint* oldpos=new QPoint();
    oldpos->setX(sys_flag->move->geometry().x());
    oldpos->setY(sys_flag->move->geometry().y());
    this->line->changeline(moudle->button,oldpos,moudle->input_size,moudle->output_size);
    update();
}
void MainWindow::adaptive()
{
    QPoint* oldpoint=new QPoint();
    Simulation_Moudle* moudle;
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        moudle=this->simulation_group->group[i];
        oldpoint->setX(moudle->button->geometry().x());
        oldpoint->setY(moudle->button->geometry().y());
        this->line->changeline(moudle->button,oldpoint,moudle->input_size,moudle->output_size);
    }
    update();
}
void MainWindow::toolchange()
{
    adaptive();
}
void MainWindow::resert_flag()
{
    /*if(sys_flag->move_flag)
        sys_flag->move_flag=false;
    if(sys_flag->drag_flag)
        sys_flag->drag_flag=false;
    if(sys_flag->draw_flag)
        sys_flag->draw_flag=false;
    update();
    */
}
void MainWindow::checkdraw(int x,int y)
{
    int xs=this->sys_flag->start->x();
    int ys=this->sys_flag->start->y();
    int x_error=x-xs;
    int y_error=y-ys;
    if(x_error==0)
    {
        this->sys_flag->end->setX(x);
        this->sys_flag->end->setY(y);
        return;
    }
    double angle=abs(atan(y_error/x_error)/PI*180);
    if(angle<=30)
    {
        this->sys_flag->end->setY(ys);
        this->sys_flag->end->setX(x);
        return;
    }
    else if(angle>30&&angle<=60)
    {
        this->sys_flag->end->setX(x);
        this->sys_flag->end->setY(ys+(y>ys?abs(x_error):-1*abs(x_error)));
        return;
    }
    else if(angle>60&&angle<=90)
    {
        this->sys_flag->end->setY(y);
        this->sys_flag->end->setX(xs);
        return;
    }

}//平滑移动line
void MainWindow::setbutton_position(Button* button,int x,int y)
{
    int width=button->geometry().width();
    int height=button->geometry().height();
    button->setGeometry(x,y,width,height);
}
void MainWindow::selectall(int xs,int ys,int xe,int ye)
{
    int width=abs(xs-xe);
    int height=abs(ys-ye);
    QRect area;
    area.setX(xs<xe?xs:xe);
    area.setY(ys<ye?ys:ye);
    area.setWidth(width);
    area.setHeight(height);
    int count=this->copy_group->moudle_group.size();
    for(int i=0;i<count;i++)
        this->copy_group->moudle_group.removeAt(0);
    for(int i=0;i<count;i++)
        this->copy_group->distance.removeAt(0);

    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        if(area.contains(this->simulation_group->group[i]->button->geometry()))
        {
            this->parent->select_flag=true;
            this->copy_group->moudle_group.push_back(this->simulation_group->group[i]);
            this->copy_group->distance.push_back(QPoint(0,0));
        }
    }
    if(this->parent->select_flag)
    {
        resort(0);
        update();
    }
}
void MainWindow::resort(int index)
{
    Simulation_Moudle* moudle=this->copy_group->moudle_group[index];
    this->copy_group->moudle_group.removeAt(index);
    this->copy_group->moudle_group.insert(0,moudle);
    for(int i=0;i<this->copy_group->moudle_group.size();i++)
    {
        this->copy_group->distance.removeAt(0);
    }
    for(int i=0;i<this->copy_group->moudle_group.size();i++)
    {
        if(i==0)
        {
            this->copy_group->distance.push_back(QPoint(0,0));
        }
        else
        {
            this->copy_group->distance.push_back(QPoint(this->copy_group->moudle_group[i]->button->x()-this->copy_group->moudle_group[0]->button->x(),this->copy_group->moudle_group[i]->button->y()-this->copy_group->moudle_group[0]->button->y()));
        }
    }
}
moudel_group* MainWindow::getsimulation_group()
{
    return this->simulation_group;
}
bool MainWindow::check_button_pos(QPoint point)
{
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        if(moudle->button->extend_geometry().contains(point))
        {
            this->sys_flag->move=moudle->button;
            this->simulation_moudle=moudle;
            return true;
        }
    }
    return false;
}
//检查是否接入外部设备
bool MainWindow::check_connect()
{
    if(build_connect())
        return true;
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        if(moudle->index==38)
        {
            if(moudle->bind_interface->input_flag||moudle->bind_interface->output_flag)
                return true;
        }
    }
    return false;
}
bool MainWindow::build_connect()
{
    if(this->sys_flag->input_bind.size()!=0||this->sys_flag->output_bind.size()!=0)
    {
        this->sys_flag->main_socket_exist=true;
        this->sys_flag->input_bind_count=this->sys_flag->input_bind.size();
        this->sys_flag->output_bind_count=this->sys_flag->output_bind.size();
        return true;
    }
    this->sys_flag->main_socket_exist=false;
    return false;
}
void MainWindow::init_finished_flag()
{
    this->sys_flag->socket_id_input=0;
    this->sys_flag->socket_id_output=0;
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        if(moudle->index==39)
        {
            if(moudle->tag_bind->input_flag)
            {
                moudle->socket_id_input=this->sys_flag->socket_id_input++;
            }
            if(moudle->tag_bind->output_flag)
            {
                moudle->socket_id_output=this->sys_flag->socket_id_output++;
            }
        }
    }
    this->sys_flag->finish_socket->input.clear();
    this->sys_flag->finish_socket->input_size=this->sys_flag->socket_id_input;
    for(int i=0;i<this->sys_flag->finish_socket->input_size;i++)
        this->sys_flag->finish_socket->input.push_back(false);

    this->sys_flag->finish_socket->output.clear();
    this->sys_flag->finish_socket->output_size=this->sys_flag->socket_id_output;
    for(int i=0;i<this->sys_flag->finish_socket->output_size;i++)
        this->sys_flag->finish_socket->output.push_back(false);
}
Simulation_Moudle* MainWindow::finished_flag(int id,int way)
{
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        if(moudle->index==39)
        {
            if(way==0&&moudle->tag_bind->input_flag&&moudle->socket_id_input==id)
                return moudle;
            else if(way==1&&moudle->tag_bind->output_flag&&moudle->socket_id_output==id)
                return moudle;
        }
    }
    return nullptr;
}
void MainWindow::clear_finish_flag(int way)
{
    //数据传输完成标志位清除
    if(way==0)
    {
        for(int i=0;i<this->sys_flag->finish_socket->input.size();i++)
            this->sys_flag->finish_socket->input[i]=false;
        this->sys_flag->finish_socket->input_size=this->sys_flag->finish_socket->input.size();
    }
    if(way==1)
    {
        for(int i=0;i<this->sys_flag->finish_socket->output.size();i++)
            this->sys_flag->finish_socket->output[i]=false;
        this->sys_flag->finish_socket->output_size=this->sys_flag->finish_socket->output.size();
    }
}
void MainWindow::rece_Timeout()
{
    for(int i=0;i<this->sys_flag->finish_socket->input.size();i++)
        if(this->sys_flag->finish_socket->input[i]==false)
        {
            Simulation_Moudle* moudle=finished_flag(i,0);
            if(moudle->index==39&&this->sys_flag->success_flag==true)
            {
                this->data_process(moudle->tag_bind->input_tag,"0");
                this->parent->statr_message(moudle->name+" input not get tag",1000);
            }
        }
    clear_finish_flag(0);
    /*
    if(this->sys_flag->success_flag==false)
    {
        this->parent->statr_message("main_socket connect failed,try to reconnect",1000);
        this->reconnect_main_socket();
    }
    */
    this->rece_clock->stop();
}
void MainWindow::send_Timeout()
{
    bool flag=false;
    for(int i=0;i<this->sys_flag->finish_socket->output.size();i++)
        if(this->sys_flag->finish_socket->output[i]==false)
        {
            Simulation_Moudle* moudle=finished_flag(i,1);
            if(flag==false)
                flag=true;
            this->parent->statr_message(moudle->name+" output connect failed",1000);
        }
    if(flag==true)//标签绑定模块输出部分数据没有完全形成
    {
        this->sys_flag->socket_main->write(this->sys_flag->output_buf.toLatin1(),this->sys_flag->output_buf.size());
        this->sys_flag->output_buf="";
    }

    clear_finish_flag(1);
    this->send_clock->stop();
}
void MainWindow::new_socket_connect()
{
    if(this->sys_flag->socket_main!=nullptr)
        return;
    this->sys_flag->socket_main=new QTcpSocket();
    connect(this->sys_flag->socket_main,&QTcpSocket::connected,this,&MainWindow::socket_connect);
    connect(this->sys_flag->socket_main,&QTcpSocket::disconnected,this,&MainWindow::socket_disconnect);
    connect(this->sys_flag->socket_main,&QIODevice::readyRead,this,&MainWindow::socket_receive);
    //this->sys_flag->socket_main->connectToHost(address,quint16(port));
}
/* socket通讯*/
void MainWindow::socket_connect()
{
    qDebug()<<"connected";
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    int index=find_moudle_with_socket(socket,1);
    if(index!=-1)
    {
        dialog_change(index);
    }
    else
    {
        this->sys_flag->success_flag=true;
        if(parent->dialog!=nullptr)
        {          
           parent->dialog->interface->connect_input->setText("disconnect");
        }
    }
}
void MainWindow::reconnect_main_socket()
{
    QHostAddress ip(this->sys_flag->ip_main);
    this->sys_flag->socket_main->connectToHost(ip,this->sys_flag->port_main);
}
void MainWindow::reconnect(int index)
{
    Simulation_Moudle* moudle=this->simulation_group->group[index];
    if(moudle->bind_interface->input_flag==true&&moudle->bind_interface->input_success==false)
    {
        this->parent->statr_message(moudle->name+" input connect failed,try to reconnect",1000);
        QHostAddress ip(QString::number(moudle->bind_interface->input_ip[0])+"."+QString::number(moudle->bind_interface->input_ip[1])+"."+QString::number(moudle->bind_interface->input_ip[2])+"."+QString::number(moudle->bind_interface->input_ip[3]));
        moudle->bind_interface->input_socket->connectToHost(ip,quint16(moudle->bind_interface->input_port));
    }
    if(moudle->bind_interface->output_flag==true&&moudle->bind_interface->output_success==false)
    {
        this->parent->statr_message(moudle->name+" output connect failed,try to reconnect",1000);
        QHostAddress ip(QString::number(moudle->bind_interface->output_ip[0])+"."+QString::number(moudle->bind_interface->output_ip[1])+"."+QString::number(moudle->bind_interface->output_ip[2])+"."+QString::number(moudle->bind_interface->output_ip[3]));
        moudle->bind_interface->output_socket->connectToHost(ip,quint16(moudle->bind_interface->output_port));
    }
}
void MainWindow::socket_disconnect()
{
    qDebug()<<"disconnected";
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    int index=find_moudle_with_socket(socket,0);
    if(index!=-1)
        dialog_change(index);
    else
    {
        this->sys_flag->success_flag=false;
        if(parent->dialog!=nullptr)
        {
           parent->dialog->interface->connect_input->setText("connect");
        }
    }
    if(this->run==nullptr)//若运行窗口已经关闭，则不需要重新建立连接
        return;
    if(this->run->real_flag==true)//当前处于运行态，需要重新建立连接
    {
        if(index!=-1)
        {
            reconnect(index);
        }
        else
        {
            this->parent->statr_message("main_socket connect failed,try to reconnect",1000);
            socket->connectToHost(this->sys_flag->ip_main,this->sys_flag->port_main);
        }
    }
}
void MainWindow::socket_receive()
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    if(this->run==nullptr)
    {
        socket->readLine();
        return;
    }

    if(this->run->run_end_flag==true)//仿真结束
    {
        socket->disconnectFromHost();
        return;
    }       
    int index=find_moudle_with_socket(socket,1);
    if(index==-1)//main socket数据接收
    {
        if(this->rece_clock->isActive()==false)
        {
            this->rece_clock->start(10);
            this->send_clock->start(50);
        }
        QByteArray temp;
        temp=socket->readLine();
        QString str(temp);
        QString str_key="";
        QString str_value="";
        int change_flag=false;
        for(int n=0;n<str.size();n++)
        {
            if(str[n]==' ')
            {
                //send_data_torun(index,str_key.toDouble());
                //this->run->run_simulation(moudle);
                if(change_flag==false)
                    change_flag=true;
                else
                {
                    change_flag=false;
                    //qDebug()<<str_key<<str_value;                   
                    data_process(str_key,str_value);
                    str_key="";
                    str_value="";
                }
            }
            else
            {
                if(change_flag==false)
                    str_key+=str[n];
                else
                    str_value+=str[n];
            }
        }
        data_process(str_key,str_value);
        //qDebug()<<str;
        return;
    }   
    while(socket->bytesAvailable())
    {
        QByteArray temp;
        temp=socket->readLine();
        QString str(temp);
        QString str_child="";
        for(int n=0;n<str.size();n++)
        {
            if(str[n]==' ')
            {
                //qDebug()<<str_child.toDouble();
                this->simulation_group->group[index]->bind_interface->receive_data.push_back(str_child.toDouble());
                send_data_torun(index,str_child.toDouble());
                str_child="";
            }
            else
            {
                str_child+=str[n];
            }
        }
        if(str_child!="")
        {
            this->simulation_group->group[index]->bind_interface->receive_data.push_back(str_child.toDouble());
            send_data_torun(index,str_child.toDouble());
        }
        //qDebug()<<str_child.toDouble();

    }
}
void MainWindow::data_process(QString key,QString value)
{
    if(this->sys_flag->input_bind.contains(key)==false)
        return;
    Simulation_Moudle* moudle=*this->sys_flag->input_bind.find(key);
    this->sys_flag->finish_socket->input[moudle->socket_id_input]=true;
    if(moudle->tag_bind->output_flag==false)//虚拟仿真
    {
        for(int i=0;i<moudle->output_number.size();i++)
            moudle->output_number[i]=value.toDouble();
        this->run->run_simulation(moudle);
    }
    else//输出端口实物连接
    {
        //qDebug()<<1;
        this->sys_flag->finish_socket->output[moudle->socket_id_output]=true;
        this->sys_flag->output_buf+=(moudle->tag_bind->output_tag+" "+value);
        //qDebug()<<key+" "+value;
        //this->sys_flag->output_bind_count--;
        int i=0;
        for(i=0;i<this->sys_flag->finish_socket->output.size();i++)
        {
            if(this->sys_flag->finish_socket->output[i]==false)
                break;
        }
        if(i==this->sys_flag->finish_socket->output.size())//所有输出至外部接口的数据打包完成 开始发送
        {
            this->sys_flag->output_bind_count=this->sys_flag->output_bind.size();
            this->sys_flag->socket_main->write(this->sys_flag->output_buf.toLatin1(),this->sys_flag->output_buf.size());
            this->sys_flag->output_buf="";
            this->send_clock->stop();
            clear_finish_flag(1);
        }
    }
}
void MainWindow::send_data_torun(int index,double value)
{
    Simulation_Moudle* moudle=this->simulation_group->group[index];
    //this->sys_flag->finish_socket->input[moudle->socket_id_input]=true;
    if(moudle->bind_interface->output_flag==true)//与实物连接
    {
        if(moudle->bind_interface->output_success==true)//是否与服务器连接成功
        {
            QString str=QString::number(value);
            moudle->bind_interface->output_socket->write(str.toLatin1(),str.length());
        }
        else
        {
            QString str=QString::number(moudle->bind_interface->output_ip[0])+"."+QString::number(moudle->bind_interface->output_ip[1])+"."+QString::number(moudle->bind_interface->output_ip[2])+"."+QString::number(moudle->bind_interface->output_ip[3]);
            parent->statr_message("reconnect from local to "+str+":"+QString::number(moudle->bind_interface->output_port),1000);
            QHostAddress ip(str);
            moudle->bind_interface->output_socket->connectToHost(ip,quint16(moudle->bind_interface->output_port));
            return;
        }
    }
    else
    {
        for(int i=0;i<moudle->output_number.size();i++)
            moudle->output_number[i]=value;
        //qDebug()<<value;
        this->run->run_simulation(moudle);
    }
}
void MainWindow::disconnect_input(int way)
{
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        if(moudle->index==38)
        {
            if(moudle->bind_interface->input_success==true)
                moudle->bind_interface->input_socket->disconnectFromHost();
            if(way==1)
                if(moudle->bind_interface->output_success==true)
                    moudle->bind_interface->output_socket->disconnectFromHost();

        }
    }
}
void MainWindow::dialog_change(int index)
{   
    if(dialog!=nullptr)
    {
        if(this->simulation_group->group[index]->bind_interface->input_success==true)
            dialog->interface->connect_input->setText("disconnect");
        else
            dialog->interface->connect_input->setText("connect");
        if(this->simulation_group->group[index]->bind_interface->output_success==true)
            dialog->interface->connect_output->setText("disconnect");
        else
            dialog->interface->connect_output->setText("connect");
    }
}
int MainWindow::find_moudle_with_socket(QTcpSocket* socket,int flag)
{
    int i=0;
    for(i=0;i<this->simulation_group->group.size();i++)
        if(this->simulation_group->group[i]->index==38)
        {
            if(this->simulation_group->group[i]->bind_interface->input_socket==socket)
            {
                if(flag==1)
                    this->simulation_group->group[i]->bind_interface->input_success=true;
                else
                    this->simulation_group->group[i]->bind_interface->input_success=false;
                break;
            }
            if(this->simulation_group->group[i]->bind_interface->output_socket==socket)
            {
                if(flag==1)
                    this->simulation_group->group[i]->bind_interface->output_success=true;
                else
                    this->simulation_group->group[i]->bind_interface->output_success=false;
                break;
            }
        }
    if(i==this->simulation_group->group.size())
        return -1;
    else
        return i;
}
int MainWindow::thirteen(int number)
{
    if(number==13)
        return -1;
    else
        return number;
}
int MainWindow::thirteen_read(int number)
{
    if(number==-1)
        return 13;
    else
        return number;
}
void MainWindow::moudle_with_line()
{
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        for(int j=0;j<moudle->input.size();j++)
        {            
            for(int m=0;m<moudle->input[j]->line_id.size();m++)
            {
                Line* linee=this->line->findwithid(moudle->input[j]->line_id[m]);
                moudle->input[j]->connect_line.push_back(linee);
                linee->endbutton.push_back(moudle->button);
                linee->endindex.push_back(j);              
                linee->endline.push_back(this->line->find_point_withid(linee,moudle->input[j]->point_id[m]));                
            }
        }
        for(int j=0;j<moudle->output.size();j++)
        {
            for(int m=0;m<moudle->output[j]->line_id.size();m++)
            {
                Line* linee=this->line->findwithid(moudle->output[j]->line_id[m]);
                moudle->output[j]->connect_line.push_back(linee);
                linee->startbutton.push_back(moudle->button);
                linee->startindex.push_back(j);
                linee->startline.push_back(this->line->find_point_withid(linee,moudle->output[j]->point_id[m]));
            }
        }
        if(moudle->index==38)//接口模块专属
        {
            moudle->bind_interface->input_socket=new QTcpSocket(this);
            connect(moudle->bind_interface->input_socket,&QTcpSocket::connected,this,&MainWindow::socket_connect);
            connect(moudle->bind_interface->input_socket,&QTcpSocket::disconnected,this,&MainWindow::socket_disconnect);
            connect(moudle->bind_interface->input_socket,&QIODevice::readyRead,this,&MainWindow::socket_receive);

            moudle->bind_interface->output_socket=new QTcpSocket(this);
            connect(moudle->bind_interface->output_socket,&QTcpSocket::connected,this,&MainWindow::socket_connect);
            connect(moudle->bind_interface->output_socket,&QTcpSocket::disconnected,this,&MainWindow::socket_disconnect);
            //connect(moudle->bind_interface->output_socket,&QIODevice::readyRead,this,&MainWindow::socket_receive);
        }
        if(moudle->index==39)//tag_bind
        {
            if(moudle->tag_bind->input_flag==true&&moudle->tag_bind->input_tag!="-1")
            {
                this->remove_tag(moudle->tag_bind->input_tag);
                this->sys_flag->input_bind.insert(moudle->tag_bind->input_tag,moudle);
            }
            if(moudle->tag_bind->output_flag==true&&moudle->tag_bind->output_tag!="-1")
            {
                this->remove_tag(moudle->tag_bind->output_tag);
                this->sys_flag->output_bind.insert(moudle->tag_bind->output_tag,moudle);
            }
        }
    }   
    //qDebug()<<this->sys_flag->input_bind.size()<<this->sys_flag->output_bind.size();
    for(int i=0;i<this->line->group.size();i++)
    {
        Line* linee=this->line->group[i];
        for(int j=0;j<linee->line.size();j++)
        {
            point* poi=&linee->line[j];
            for(int m=0;m<poi->branch_id.size();m++)
            {
                poi->branch.push_back(this->line->find_point_withid(linee,poi->branch_id[m]));
                this->line->find_point_withid(linee,poi->branch_id[m])->parent_line=poi;
            }
            for(int m=0;m<poi->start_id.size();m++)
            {
                poi->start_point.push_back(this->line->find_point_withid(linee,poi->start_id[m]));
            }
            for(int m=0;m<poi->end_id.size();m++)
            {
                poi->end_point.push_back(this->line->find_point_withid(linee,poi->end_id[m]));
            }
        }
    }

    //更新标签
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        //qDebug()<<moudle->time<<moudle->value;
        if(moudle->index==12||moudle->index==13||moudle->index==14||moudle->index==15)
        {
            moudle->fenmu=new QLabel(this);
            moudle->fenzi=new QLabel(this);
            //qDebug()<<moudle->time<<moudle->value;
        }
        else if(moudle->index==8||moudle->index==9||moudle->index==10||moudle->index==11||moudle->index==19||moudle->index==22||moudle->index==23||moudle->index==24||moudle->index==25||moudle->index==26||moudle->index==27||moudle->index==28||moudle->index==29||moudle->index==30||moudle->index==31||moudle->index==32||moudle->index==33||moudle->index==34||moudle->index==39||moudle->index==40||moudle->index==41||moudle->index==38)
        {
            moudle->fenzi=new QLabel(this);
            moudle->fenzi->setText(moudle->value);
        }
        this->update_label_pos(moudle->button);
        //qDebug()<<moudle->output_size<<moudle->output.size();
    }
    this->modify=false;
}
QDataStream& operator<<(QDataStream& output, MainWindow& obj)
{
    //注意：数据写入文件时最好以double类型写入，如果以Int类型写入，可能会导致读出数据不一致（比如写入13，读出0，影响后面数据的读出）
    output.setVersion(QDataStream::Qt_4_3);
    Button* button;

    QString stop="-1";
    //写入工程地址
    output<<obj.project_url;
    output<<stop;//工程地址校验截至符
    //sys_flag写入
    output<<obj.thirteen(obj.sys_flag->button_id);

    output<<moudle_count;
    for(int i=0;i<moudle_count;i++)
    {
        output<<obj.thirteen(obj.sys_flag->label_count[i]);
    }

    output<<obj.thirteen(obj.simulation_group->group.size());
    for(int i=0;i<obj.simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=obj.simulation_group->group[i];
        button=moudle->button;
        output<<obj.thirteen(button->x())<<obj.thirteen(button->y())<<obj.thirteen(button->width())<<obj.thirteen(button->height());

        output<<obj.thirteen(moudle->index);
        output<<obj.thirteen(moudle->id);

        output<<moudle->spacing;

        output<<obj.thirteen(moudle->input_size);
        output<<obj.thirteen(moudle->output_size);

        output<<moudle->name;
        output<<obj.thirteen(moudle->param.size());
        for(int j=0;j<moudle->param.size();j++)
        {
            output<<moudle->param[j];
        }

        output<<obj.thirteen(moudle->param_temp.size());
        for(int j=0;j<moudle->param_temp.size();j++)
            output<<moudle->param_temp[j];
        output<<obj.thirteen(moudle->temp.size());
        for(int j=0;j<moudle->temp.size();j++)
            output<<moudle->temp[j];

        output<<obj.thirteen(moudle->time_sequence.size());
        for(int j=0;j<moudle->time_sequence.size();j++)
        {
            //qDebug()<<moudle->time_sequence[j];
            output<<moudle->time_sequence[j];
        }
        output<<obj.thirteen(moudle->value_sequence.size());
        for(int j=0;j<moudle->value_sequence.size();j++)
        {
            output<<moudle->value_sequence[j];
        }

        output<<moudle->time;
        output<<moudle->value;

        output<<obj.thirteen(moudle->input.size());
        if(moudle->input.size()!=0)
        for(int j=0;j<moudle->input.size();j++)
        {
            output<<obj.thirteen(moudle->input[j]->connect_line.size());
            for(int m=0;m<moudle->input[j]->connect_line.size();m++)
            {
                Line* linee=moudle->input[j]->connect_line[m];
                moudle->input[j]->line_id.push_back(linee->id);
                output<<linee->id;
                for(int n=0;n<linee->endbutton.size();n++)
                {
                    if(linee->endbutton[n]==moudle->button&&linee->endindex[n]==j)
                    {
                        moudle->input[j]->point_id.push_back(linee->endline[n]->id);
                        output<<linee->endline[n]->id;
                    }
                }
            }
        }
        output<<obj.thirteen(moudle->output.size());
        if(moudle->output.size()!=0)
        for(int j=0;j<moudle->output.size();j++)
        {
            output<<obj.thirteen(moudle->output[j]->connect_line.size());
            for(int m=0;m<moudle->output[j]->connect_line.size();m++)
            {
                Line* linee=moudle->output[j]->connect_line[m];
                moudle->output[j]->line_id.push_back(linee->id);
                output<<linee->id;
                for(int n=0;n<linee->startbutton.size();n++)
                {
                    if(linee->startbutton[n]==moudle->button&&linee->startindex[n]==j)
                    {
                        moudle->output[j]->point_id.push_back(linee->startline[n]->id);
                        output<<linee->startline[n]->id;
                    }
                }
            }
        }
        if(moudle->index==38)//接口模块专属
        {
            output<<obj.thirteen(moudle->bind_interface->input_flag);
            output<<obj.thirteen(moudle->bind_interface->input_port);
            output<<obj.thirteen(moudle->bind_interface->input_ip.size());
            for(int m=0;m<moudle->bind_interface->input_ip.size();m++)
                output<<obj.thirteen(moudle->bind_interface->input_ip[m]);

            output<<obj.thirteen(moudle->bind_interface->output_flag);
            output<<obj.thirteen(moudle->bind_interface->output_port);
            output<<obj.thirteen(moudle->bind_interface->output_ip.size());
            for(int m=0;m<moudle->bind_interface->output_ip.size();m++)
                output<<obj.thirteen(moudle->bind_interface->output_ip[m]);
        }
        if(moudle->index==39)
        {
            output<<obj.thirteen(moudle->tag_bind->input_flag);
            output<<obj.thirteen(moudle->tag_bind->output_flag);
            output<<moudle->tag_bind->input_tag;
            output<<moudle->tag_bind->output_tag;
        }
    }   

    output<<obj.thirteen(obj.line->group.size());
    for(int i=0;i<obj.line->group.size();i++)//line写入
    {
        Line* linee=obj.line->group[i];
        output<<linee->id;
        output<<linee->point_current_id;
        output<<linee->no_single;
        output<<obj.thirteen(linee->line.size());
        for(int j=0;j<linee->line.size();j++)
        {
            output<<obj.thirteen(linee->line[j].start.x())<<obj.thirteen(linee->line[j].start.y())<<obj.thirteen(linee->line[j].end.x())<<obj.thirteen(linee->line[j].end.y());
            output<<linee->line[j].id<<obj.thirteen(linee->line[j].proportion)<<linee->line[j].turn_flag<<linee->line[j].start_flag<<linee->line[j].end_flag<<linee->line[j].flag<<obj.thirteen(linee->line[j].start_line)<<obj.thirteen(linee->line[j].end_line)<<linee->line[j].parent_start_end;

            output<<obj.thirteen(linee->line[j].branch.size());
            for(int m=0;m<linee->line[j].branch.size();m++)
            {
                output<<linee->line[j].branch[m]->id;
            }

            output<<obj.thirteen(linee->line[j].start_point.size());
            for(int m=0;m<linee->line[j].start_point.size();m++)
            {
                output<<linee->line[j].start_point[m]->id;
            }

            output<<obj.thirteen(linee->line[j].end_point.size());
            for(int m=0;m<linee->line[j].end_point.size();m++)
            {
                output<<linee->line[j].end_point[m]->id;
            }
        }
    }
    output<<obj.line->idcount<<obj.line->current_id<<obj.line->delete_id<<obj.thirteen(obj.line->current_proportion)<<obj.line->scale;
    //qDebug()<<obj.line->idcount<<obj.line->current_id;
    obj.modify=false;
    obj.parent->save_state();
    return output;
}
QDataStream& operator>>(QDataStream& input, MainWindow& obj)
{
    input.setVersion(QDataStream::Qt_4_3);
    int size;
    int s_size;
    int i_size;
    int temp[4];
    int i_temp;
    double d_temp;
    QString s_temp="";
    //读取project地址
    input>>obj.project_url;
    input>>s_temp;
    //sys_flag读取
    input>>i_temp;
    obj.sys_flag->button_id=obj.thirteen_read(i_temp);
    input>>size;
    for(int i=0;i<size;i++)
    {
        input>>i_temp;
        obj.sys_flag->label_count[i]=obj.thirteen_read(i_temp);
    }    
    input>>size;
    size=obj.thirteen_read(size);
    for(int i=0;i<size;i++)//simulation读取
    {
        Simulation_Moudle* moudle=new Simulation_Moudle();
        QLabel* label=new QLabel(&obj);
        label->setVisible(true);
        Button* button=new Button();
        input>>temp[0]>>temp[1]>>temp[2]>>temp[3];
        button->setGeometry(obj.thirteen_read(temp[0]),obj.thirteen_read(temp[1]),obj.thirteen_read(temp[2]),obj.thirteen_read(temp[3]));
        moudle->label=label;
        moudle->button=button;

        input>>i_temp;
        moudle->index=obj.thirteen_read(i_temp);

        input>>i_temp;
        moudle->id=obj.thirteen_read(i_temp);

        input>>moudle->spacing;

        input>>i_temp;
        moudle->input_size=obj.thirteen_read(i_temp);
        input>>i_temp;
        moudle->output_size=obj.thirteen_read(i_temp);

        input>>moudle->name;        
        //qDebug()<<moudle->name;
        input>>i_size;
        i_size=obj.thirteen_read(i_size);
        for(int j=0;j<i_size;j++)
        {
            input>>d_temp;
            moudle->param.push_back(d_temp);
        }

        input>>i_size;
        i_size=obj.thirteen_read(i_size);
        for(int j=0;j<i_size;j++)
        {
            input>>d_temp;
            moudle->param_temp.push_back(d_temp);
        }
        input>>i_size;
        i_size=obj.thirteen_read(i_size);
        for(int j=0;j<i_size;j++)
        {
            input>>d_temp;
            moudle->temp.push_back(d_temp);
        }

        input>>i_size;
        i_size=obj.thirteen_read(i_size);
        for(int j=0;j<i_size;j++)
        {
            input>>d_temp;
            moudle->time_sequence.push_back(d_temp);
            //qDebug()<<d_temp;
        }
        input>>i_size;
        i_size=obj.thirteen_read(i_size);
        for(int j=0;j<i_size;j++)
        {
            input>>d_temp;           
            moudle->value_sequence.push_back(d_temp);
        }

        input>>moudle->time;
        input>>moudle->value;

        obj.simulation_group->group.push_back(moudle);

        input>>s_size;//模块输入端
        s_size=obj.thirteen_read(s_size);
        if(s_size!=0)
        {

            for(int j=0;j<s_size;j++)
            {
                moudle_param* param=new moudle_param();
                input>>i_size;
                i_size=obj.thirteen_read(i_size);
                for(int m=0;m<i_size;m++)
                {
                    input>>i_temp;
                    param->line_id.push_back(i_temp);
                    input>>i_temp;
                    param->point_id.push_back(i_temp);
                }
                moudle->input.push_back(param);
            }
        }

        input>>s_size;//模块输出端
        s_size=obj.thirteen_read(s_size);
        if(s_size!=0)
        {
            for(int j=0;j<s_size;j++)
            {
                moudle_param* param=new moudle_param();
                input>>i_size;
                i_size=obj.thirteen_read(i_size);
                for(int m=0;m<i_size;m++)
                {
                    input>>i_temp;
                    param->line_id.push_back(i_temp);
                    input>>i_temp;
                    param->point_id.push_back(i_temp);
                }
                moudle->output.push_back(param);
            }
        }
        if(moudle->index==38)//接口模块专属
        {
            moudle->bind_interface=new interface_bind();
            input>>i_temp;
            moudle->bind_interface->input_flag=obj.thirteen_read(i_temp);
            input>>i_temp;
            moudle->bind_interface->input_port=obj.thirteen_read(i_temp);
            input>>i_size;
            i_size=obj.thirteen_read(i_size);
            for(int k=0;k<i_size;k++)
            {
                input>>i_temp;
                moudle->bind_interface->input_ip.push_back(obj.thirteen_read(i_temp));
            }

            input>>i_temp;
            moudle->bind_interface->output_flag=obj.thirteen_read(i_temp);
            input>>i_temp;
            moudle->bind_interface->output_port=obj.thirteen_read(i_temp);
            input>>i_size;
            i_size=obj.thirteen_read(i_size);
            for(int k=0;k<i_size;k++)
            {
                input>>i_temp;
                moudle->bind_interface->output_ip.push_back(obj.thirteen_read(i_temp));
            }
        }
        if(moudle->index==39)
        {
            moudle->tag_bind=new bind_tag();
            input>>i_temp;
            moudle->tag_bind->input_flag=obj.thirteen_read(i_temp);
            input>>i_temp;
            moudle->tag_bind->output_flag=obj.thirteen_read(i_temp);
            input>>moudle->tag_bind->input_tag;
            input>>moudle->tag_bind->output_tag;
        }

    }

    input>>size;
    size=obj.thirteen_read(size);
    for(int i=0;i<size;i++)//line读取
    {
        Line* linee=new Line();
        input>>linee->id;
        input>>linee->point_current_id;
        input>>linee->no_single;
        input>>i_size;
        i_size=obj.thirteen_read(i_size);
        for(int j=0;j<i_size;j++)
        {
            point poi;
            input>>i_temp;
            poi.start.setX(obj.thirteen_read(i_temp));
            input>>i_temp;
            poi.start.setY(obj.thirteen_read(i_temp));
            input>>i_temp;
            poi.end.setX(obj.thirteen_read(i_temp));
            input>>i_temp;
            poi.end.setY(obj.thirteen_read(i_temp));
            linee->line.push_back(poi);
            input>>linee->line[j].id;
            input>>linee->line[j].proportion;
            linee->line[j].proportion=obj.thirteen_read(linee->line[j].proportion);
            input>>linee->line[j].turn_flag>>linee->line[j].start_flag>>linee->line[j].end_flag>>linee->line[j].flag;
            input>>linee->line[j].start_line;
            linee->line[j].start_line=obj.thirteen_read(linee->line[j].start_line);
            input>>linee->line[j].end_line;
            linee->line[j].end_line=obj.thirteen_read(linee->line[j].end_line);
            input>>linee->line[j].parent_start_end;
            linee->line[j].parent_start_end=obj.thirteen_read(linee->line[j].parent_start_end);

            input>>s_size;
            s_size=obj.thirteen_read(s_size);
            for(int m=0;m<s_size;m++)
            {
                input>>i_temp;
                linee->line[j].branch_id.push_back(i_temp);
            }

            input>>s_size;
            s_size=obj.thirteen_read(s_size);
            for(int m=0;m<s_size;m++)
            {
                input>>i_temp;
                linee->line[j].start_id.push_back(i_temp);
            }

            input>>s_size;
            s_size=obj.thirteen_read(s_size);
            for(int m=0;m<s_size;m++)
            {
                input>>i_temp;
                linee->line[j].end_id.push_back(i_temp);
            }
        }        
        obj.line->group.push_back(linee);
    }   
    input>>obj.line->idcount>>obj.line->current_id>>obj.line->delete_id;
    input>>obj.line->current_proportion;
    obj.line->current_proportion=obj.thirteen_read(obj.line->current_proportion);
    input>>obj.line->scale;
    //qDebug()<<obj.line->idcount<<obj.line->current_id;
    return input;
}
void MainWindow::open(QFile* file)
{
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"error";
        return;
    }
    QDataStream ds(file);
    ds>>*this;

    file->close();   
    this->moudle_with_line();
}
void MainWindow::save()
{

    if(this->save_open==false)
    {
        //this->save_open=true;
        this->parent->save_as(0);
    }
    else
    {
        QFile file(this->url);
        save_as(&file,0);
    }
}
void MainWindow::save_as(QFile* file,int way)
{
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"error";
        return;
    }
    QDataStream ds(file);
    ds<<*this;
    file->close();
    if(way==0&&project_url=="-1")
    {
        this->parent->whitch_project(this->url);
    }
}
