#ifndef SIMULATION_MOUDLE_H
#define SIMULATION_MOUDLE_H
#include <QtWidgets>
#include <QObject>
#include "line_group.h"
#include "button.h"
#include <QtNetwork>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
/*
struct line
{
QPushButton* start;
QPushButton* end;
};
*/
//class Simulation_Moudle;
class Simulation_Moudle;
class bind_tag //直接绑定实际接口的标签
{
    public:
    bind_tag();
    bind_tag(bind_tag& bind);
    bool input_flag=false;//输入是否绑定接口
    bool output_flag=false;//输出是否绑定接口
    QString input_tag="";//输入绑定接口的标签
    QString output_tag="";//输出绑定接口的标签

    QString input_tag_temp;
    QString output_tag_temp;
};
class interface_bind//用于绑定实际接口
{
public:
    interface_bind();
    interface_bind(interface_bind& inter);
    bool input_flag=true;//输入是否绑定接口
    bool input_success=false;//连接成功标志
    QTcpSocket* input_socket;
    QList<int> input_ip;
    int input_port;

    bool output_success=false;//绑定成功标志
    bool output_flag=true;//输出是否绑定接口
    QTcpSocket* output_socket;
    QList<int> output_ip;
    int output_port;

    QList<double> receive_data;//当输入绑定接口时接收到的数据
    int front=0;//指示当前数据中用于仿真的位置
};

struct moudle_relation
{
    Simulation_Moudle* moudle;
    int index;
};

struct moudle_param
{
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    QList<Line*> connect_line;
    QList<moudle_relation> next;

    QList<int> line_id;//用来记录所连Line的id;保存文件或打开文件使用
    QList<int> point_id;//用来记录所连Line的起端或始端id;

};
class Simulation_Moudle : public QObject
{
    Q_OBJECT
public:
    Button* button=new Button();
    QLabel* label;//模块标签
    QIcon* icon;
    QList<double> param;//模块参数

    QList<double> param_temp;//高阶控制对象临时参数存储
    QList<double> temp;

    QList<double> time_sequence;//分段折线波专有
    QList<double> value_sequence;
    QString time="1";
    QString value="1";

    QLabel* fenzi;//惯性环节传递函数显示
    QLabel* fenmu;

    int index;//index of param table  param count
    int id;
    int x;
    int y;
    QString name;

    interface_bind* bind_interface;//接口绑定模块专属 index=38
    bind_tag* tag_bind;

    double spacing=0;//node 间距
    //模块输入输出通道数量及准备完毕标志
    int input_size=0;
    int output_size=0;
    QList<moudle_param*> input;
    QList<moudle_param*> output;
    QList<double> input_number;
    QList<double> output_number;
    QList<double> process_value;//存储模块仿真过程中产生的中间数据
    QList<double> graph_value;//图表模块与信号源模块专用
    QList<bool>   input_flag;
    QList<bool>   output_flag;
    QList<bool>   input_loop;//模块是否形成闭环
    bool   loop_flag;//标记已经走过
    bool   grapg_flag=false;//是否显示
    explicit Simulation_Moudle(QObject *parent = nullptr);
    ~Simulation_Moudle();
    void setRect();//set node rect position
    void setposition();

    int socket_id_input=0;//半实物仿真时使用，每个接口模块在所有接口模块集合中的id编号，方便统计数据传输是否完整
    int socket_id_output=0;
signals:

public slots:
};

#endif // SIMULATION_MOUDLE_H
