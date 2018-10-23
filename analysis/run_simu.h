#ifndef RUN_SIMU_H
#define RUN_SIMU_H
#include "moudel_group.h"
#include <QWidget>
#include <QtWidgets>
#include <QDebug>
#include <QThread>
class analysis;
class MainWindow;
struct UI_run
{
    QList<QPushButton*> graph_group;
    QList<QLabel*> current_value;
    int x_start=50;
    int y_start=200;//y_start=midwindow.hight/2
    int x_length=600;//x_axia_precision*x_interval_point*(x_count-1)
    int x_count=11;//x坐标轴标度数量
    int x_interval_point=20;//x轴每两个标度间的点数
    int y_axis_length=80;
    int x_axia_precision=3;

    int x_interview_length;

    int y_count=4;
    int y_invalid=10;

    bool start_drag=false;
    int drag_x_start=0;//鼠标拖动起始位置
};
struct time_param
{
    double simu_time;
    double simu_step;
    int simu_count=0;
    int simu_count_max;

    int time_temp;
    int time_drag;//用于拖动曲线时时间显示
};
class Run_Simu : public QMainWindow
{
    Q_OBJECT
public:
    explicit Run_Simu(QWidget *parent = nullptr,moudel_group* group=nullptr,double time_length=0,double time_step=0,bool real_flag=true);
    void moudle_relation();//将多个moudle根据输入输出进行连接
    void realtime_simulation();
    void loadmindindow(QMdiSubWindow* midwindow);
    void save_data(QFile* file,int index);
    void save_graph_date();
    void statusBar_show();
    bool getstate();
    void run_simulation(Simulation_Moudle* moudle);
    bool run_end_flag=false;
    bool real_flag=false;//是否接入外部设备 如果接入,则无法暂停
    analysis* parent;
    QList<QString> graph_name;//存放图表标签
    QList<bool> save_complete;
    int current_graph_id;
    QList<QString> url;//存放图表数据存储地址
    QTimer mDataTimer;
    MainWindow* window_parent;
private:
    //窗口状态栏
    QStatusBar *statusBar;
    QPushButton* start_stop;
    bool run_stop_state=false;
    void statusBar_init();
    void simu_run();


    bool flag_real=false;
    bool draw_point_flag=false;
    struct time_param time;
    QTime time_before;
    double value_min=0;
    double value_max=0;
    double value_limit=0;
    UI_run* ui=new UI_run();
    moudel_group* simulation_group=new moudel_group();
    moudel_group* moudle_generator=new moudel_group();//信号发生器
    moudel_group* moudle_graph=new moudel_group();//图表
    moudel_group* moudle_socket=new moudel_group();//输入端绑定实际接口
    QList<QLabel*> time_label;
    QList<QLabel*> value_label;    
    QMdiSubWindow* midwindow;   
    void init();
    void change();
    void paintEvent(QPaintEvent *);  
    void relation_init();
    void detect_loop();
    void loop_check(Simulation_Moudle* moudle,int index);//
    bool check_input(Simulation_Moudle* moudle,int index,double value);//检测模块所有输入是否准备完毕
    void calculation(Simulation_Moudle* moudle);
    void run_socket(Simulation_Moudle* moudle);
    void form();//将信号源组织起
    void form_graph();
    void clear_process_value();
    void output_generator(Simulation_Moudle* moudle,int time);//信号源数据输出
    void get_max(int start,int end);
    void graph_button();
    void set_shadow(QWidget *widget);
    void remove_shadow(QWidget *widget);
    bool check_signal();//检查信号完整性 模块引脚是否全部连接
    void update_size();
    int check_focus();//检查鼠标光标是否在坐标系中   
    void clear_save_flag();
    void check_data();//检查图表数据长度是否等于 当前时间/步距
signals:

public slots:

private slots:
    void timerSlot();
protected slots:
    void mousePressEvent(QMouseEvent* event);//按下
    void mouseMoveEvent(QMouseEvent* event);//按下移动
    void mouseReleaseEvent(QMouseEvent* event);//松开
    //void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent* event);//滚轮
};

#endif // RUN_SIMU_H
