#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
class algorithm_file;
class algorithm;
class Simulation_Moudle;
class bind_tag;
class interface_bind;
class moudel_group;
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
};

struct moudle_relation
{
    Simulation_Moudle* moudle;
    int index;
    int id;
};

struct moudle_param
{
    QList<moudle_relation> next;
};
class Simulation_Moudle : public QObject
{
    Q_OBJECT
public:
    QList<double> param;//模块参数

    QList<double> param_temp;//高阶控制对象临时参数存储
    QList<double> temp;

    QList<double> time_sequence;//分段折线波专有
    QList<double> value_sequence;
    int index;//index of param table  param count
    int id;
    QString name;

    interface_bind* bind_interface;//接口绑定模块专属 index=38
    bind_tag* tag_bind;

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

    int socket_id_input;//半实物仿真时使用，每个接口模块在所有接口模块集合中的id编号，方便统计数据传输是否完整
    int socket_id_output;
signals:

public slots:
};
class moudel_group
{
public:
    QList<Simulation_Moudle*> group;
    moudel_group();
    Simulation_Moudle* find_with_id(int id);
};
struct ui_socket
{
    QList<QLineEdit*> address;//输入接口绑定ip
    QLineEdit *port;
    Simulation_Moudle* moudle=nullptr;
    int way;//0 input 1 output
};
class algorithm_file:public QWidget
{   Q_OBJECT
public:
    algorithm_file(QWidget *parent = nullptr);
private:
    moudel_group* simulation_group=new moudel_group();
    bool start_run=false;
    int simu_step;
    algorithm* alg;
    system_flag* sys_flag=new system_flag();
    QTimer* send_clock=new QTimer();//用于判定规定时间内是否所有接口模块（38，39）输出端信号全部发送完毕
    QTimer* rece_clock=new QTimer();//用于判定规定时间内是否所有接口模块（38，39）输入端信号全部接收完毕
    QString url="";
    void init();
    void run_();
    void readdata();
    QString getstr(QString str);
    void save_algorithm();

    void relation_init();
    void detect_loop();
    void loop_check(Simulation_Moudle* moudle,int index);
    void run_simulation(Simulation_Moudle* moudle);
    bool check_input(Simulation_Moudle* moudle,int index,double value);
    void calculation(Simulation_Moudle* moudle);
    void init_finished_flag();
    void clear_finish_flag(int way);
    Simulation_Moudle* finished_flag(int id,int way);
    void data_process(QString key,QString value);
    void send_data_torun(int index,double value);
    int find_moudle_with_socket(QTcpSocket* socket,int flag);
    void reconnect(int index);
    QStringList url_to_name(QString fileName);//地址转文件名
    void remove_tag(QString tag);
    void socket_connect();
    void socket_disconnect();
    void socket_receive();
private slots:
    void rece_Timeout();
    void send_Timeout();
protected slots:
    void keyPressEvent(QKeyEvent *event);
};
class algorithm:public QDialog
{
public:
    algorithm(QWidget *parent = nullptr);
    void init(moudel_group* group);
    QPushButton* find_with_socket(QTcpSocket* socket);
    QMap<QPushButton*,ui_socket*> button_to_ui;
    system_flag* sys_flag;
    ui_socket* socket_main=new ui_socket();
    QPushButton* main_connect=new QPushButton("connect");
private:
    QTabWidget* tab_widget;
    QScrollArea* tag_scoll;
    QScrollArea* socket_scoll;
    QDialog* tag_dialog;
    QDialog* socket_dialog;
    QLineEdit* text_edit;
    moudel_group* moudle;
    moudel_group* tag_group=new moudel_group();
    moudel_group* socket_group=new moudel_group();
    bool stop_flag;
    QMap<QComboBox*,Simulation_Moudle*> box_to_moudle;
    QMap<QComboBox*,bool> box_to_flag;
    QPushButton* run_button=new QPushButton("run");

    void init_moudle();
    void init_ui();
    void init_ui_tag();
    void init_ui_socket();
    void combbox_change(QString str);
    void layout(QVBoxLayout* vbox,ui_socket* ui);


    bool page_change=false;
    void tab_change();
    void clicked_button();

    void remove_tag(QString tag);//为了避免多个模块绑定同一标签，增加标签删除、插入功能
    void insert_tag(QString tag);
    QList<int> getnum(QString tag);//获取tag对应的number
    int sort_tag(QList<int> num,int index,int start);

    void run_analysis();
    bool detect_connect();
};

#endif // MAINWINDOW_H
