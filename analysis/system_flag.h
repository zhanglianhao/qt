#ifndef SYSTEM_FLAG_H
#define SYSTEM_FLAG_H
#include <QtWidgets>
#include "custombutton.h"
#include "simulation_moudle.h"
#include "copygroup.h"
#define moudle_count 49
struct pattern
{
    QPoint start;
    QPoint end;
};
struct socket_finish
{
    int input_size=0;
    int output_size=0;
    QList<bool> input;
    QList<bool> output;
};
struct system_flag{

    Button* move;
    Simulation_Moudle* copy_moudle=nullptr;//存放复制或剪切后的临时模块
    Simulation_Moudle* copy_moudle_temp=new Simulation_Moudle();
    //Simulation_Moudle* moudle_temp;
    //copygroup* copy_moudle_group=new copygroup();
    int move_flag;
    int index=0;
    bool paste_flag=false;
    bool place_flag=false;
    bool click_flag=true;
    bool copy_group=false;
    //bool select_flag=false;//选中移动时位置记录
    QPoint previous;
    QPoint current;
    bool timeout_flag=false;
    bool draw_flag=false;
    bool drag_flag=false;

    bool signal_detect_flag=false;//用于display_error=0时的情况

    int button_width;
    int button_height;
    int width_min=20;
    int height_min=20;
    int button_id=0;//moudle编号 唯一标识
    int current_node;//
    QPoint start_point;
    QPoint* start=new QPoint();
    QPoint* end=new QPoint();
    int param[moudle_count]={2,3,3,6,4,1};//the paramter count of different simulation moudle
    int label_count[moudle_count]={0};
    QString name[moudle_count];
    QList<pattern> draw_pattern[moudle_count];
    QStringList tag_group;//存储所有机柜中节点的标签
    QStringList tag_group_temp;
    QList<QList<int>> tag_number_group;
    QMap<QString,Simulation_Moudle* > input_bind;//与相应标签绑定的模块
    int input_bind_count;//所有用于绑定输入接口的模块数量 用于同步数据
    //bool input_finish_flag=false;
    QMap<QString,Simulation_Moudle* > output_bind;
    QString output_buf="";//输出缓冲区
    int output_bind_count;
    bool main_socket_exist=false;
    QTcpSocket* socket_main=nullptr;
    bool success_flag=false;
    QString ip_main;
    quint16 port_main;
    socket_finish* finish_socket=new socket_finish();
    int socket_id_input=0;//半实物仿真时使用，每个接口模块在所有接口模块集合中的id编号，方便统计数据传输是否完整
    int socket_id_output=0;
};
#endif // SYSTEM_FLAG_H
