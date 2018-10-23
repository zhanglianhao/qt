#include "simulation_moudle.h"

Simulation_Moudle::Simulation_Moudle(QObject *parent) : QObject(parent)
{

}
/*
    QList<moudle_param*> input;
    QList<moudle_param*> output;
    QList<double> input_number;
    QList<double> output_number;
    QList<bool>   input_flag;
    QList<bool>   output_flag;
*/
Simulation_Moudle::~Simulation_Moudle()
{
    int count=this->input.size();
    for(int i=0;i<count;i++)
        delete this->input[i];
    count=this->output.size();
    for(int i=0;i<count;i++)
        delete this->output[i];
}
void Simulation_Moudle::setRect()
{
    this->input[0]->x_min=this->x;
    this->input[0]->x_max=this->x+5;
    this->input[0]->y_min=this->y+10;
    this->input[0]->y_max=this->y+20;

    this->output[0]->x_min=this->x+25;
    this->output[0]->x_max=this->x+31;
    this->output[0]->y_min=this->y+10;
    this->output[0]->y_max=this->y+20;

}
void Simulation_Moudle::setposition()
{
    x=this->button->geometry().x();
    y=this->button->geometry().y();
}
interface_bind::interface_bind()
{

}
interface_bind::interface_bind(interface_bind& inter)
{
    this->input_flag=inter.input_flag;
    this->input_ip=inter.input_ip;
    this->input_port=inter.input_port;
    this->input_success=false;
    this->input_socket=nullptr;
    //qDebug()<<this->input_flag<<this->input_ip[0]<<this->input_ip[1];
    this->output_flag=inter.output_flag;
    this->output_ip=inter.output_ip;
    this->output_port=inter.output_port;
    this->output_success=false;
    this->output_socket=nullptr;
}
bind_tag::bind_tag()
{

}
bind_tag::bind_tag(bind_tag& bind)
{
    input_flag=bind.input_flag;//输入是否绑定接口
    output_flag=bind.output_flag;//输出是否绑定接口
    input_tag="-1";//输入绑定接口的标签
    output_tag="-1";//输出绑定接口的标签
    input_tag_temp=bind.input_tag;
    output_tag_temp=bind.output_tag;
}
