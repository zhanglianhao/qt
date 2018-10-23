#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "custombuttongroup.h"
#include <QThread>
#include <QDebug>
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include "system_flag.h"
#include "custommenu.h"
#include "moudel_group.h"
#include "paramdialog.h"
#include "line_group.h"
#include "interface.h"
#include "custombutton.h"
#include <QCloseEvent>
#include "copygroup.h"
#include <QtNetwork>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
class analysis;
class Run_Simu;
namespace Ui {
class MainWindow;
}
#define draw_way 1//1:自由移动line 2:平滑移动line
#define delete_way 1//0:删除line_group 1:删除line及分支
#define init_size 45//moudle尺寸
#define bug 1//1: 2:
#define PI 3.1415926
//#define display_error 0//0:仿真前显示error 1:实时显示error
/*
class newmove:public QThread{
public:
    QPushButton* button;
    Ui::MainWindow* ui;
     newmove(QPushButton* but,Ui::MainWindow* UI)
{
         button=but;
         ui=UI;
}
    void run()
    {

        while(1)
        {
            qDebug()<<1;
         //   button->setGeometry(ui->centralWidget->mapFromGlobal(QCursor::pos()).x(),ui->centralWidget->mapFromGlobal(QCursor::pos()).y(),31,31);
            sleep(5);
        }
    }
};
*/
struct Flag{
    bool flag;
    int result;
};

struct io_count{
    int input;
    int output;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent);
    ~MainWindow();
    void clonemoudle();//复制或剪切当前模块
    void cutmoudle();
    void pastemoudle();//粘贴临时模块
    void deleteany();
    void moudle_relation();//将多个moudle根据输入输出进行连接
    void realtime_simulation();
    void open(QFile*);
    void save();
    void save_as(QFile*,int way);
    bool check_signal();//检查信号完整性 模块引脚是否全部连接
    void disconnect_input(int way);//断开所有输入接口的连接 way=1 断开所有输入输出接口的连接
    static int thirteen(int number);
    static int thirteen_read(int number);

    bool check_connect();
    bool build_connect();//检查是否需要建立与服务器之间的连接
    void new_socket_connect();
    void data_process(QString key,QString value);

    void init_finished_flag();//信号传输完成标志位初始化
    QTimer* send_clock=new QTimer();//用于判定规定时间内是否所有接口模块（38，39）输出端信号全部发送完毕
    QTimer* rece_clock=new QTimer();//用于判定规定时间内是否所有接口模块（38，39）输入端信号全部接收完毕
    void clear_finish_flag(int way);
    void reconnect_main_socket();//重新连接main_socket

    moudel_group* getsimulation_group();
    system_flag* sys_flag=new system_flag();
    analysis* parent;//指向主框架
    int id=0;//窗口编号
    bool save_open=false;
    QString name="";//窗口名称
    QString url="";//当前文件保存地址
    bool modify=false;//当前文件是否已经改动
    Run_Simu* run=nullptr;//当前已经运行的仿真界面
    //bool project_exist=false;//是否已存在于project中
    QString project_url="-1";//所在工程地址
private slots:
    void on_linear_pressed();
    void animateTimeout();
    void toolchange();
    void rece_Timeout();
    void send_Timeout();
private:
    CustomButtonGroup *custombutton=new CustomButtonGroup();
    custommenu* custom_menu=new custommenu();
    Simulation_Moudle* simulation_moudle=new Simulation_Moudle();//simulation moudle
    moudel_group* simulation_group=new moudel_group();
    paramdialog* dialog=nullptr;
    line_group* line=new line_group();
    interface_icon* Interface=new interface_icon();
    copygroup* copy_group=new copygroup();
    moudel_group* moudle_generator=new moudel_group();
    //QPushButton* move;
    //int move_flag;
    void analysis();
    void init();
    void time_init();
    void param_init();
    void pattern_init();//模块内部图案初始化
    pattern point_to_pattern(QPoint pos1,QPoint pos2);
    void image();//set const image url
    void mmove();//pressed
    void button_click();//clicked
    void mreleased();//released
    void setbutton_position(Button* button,int x,int y);//only set x,y not set width,height
    void setsize(Button* button,int width,int height);// only set button size
    void single_click();
    void double_click();
    void interface_expand(Simulation_Moudle* moudle,int way);//根据模块尺寸自动扩展端口数量 way=0:只扩展input way=1:只扩展output way=2:全部扩展
    bool find(QList<int> group,int index);
    void moudletogroup(Button* button,int index,bool flag);
    //bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *);
    void paintline(QPainter* painter);
    void paintmoudle(QPainter* painter);
    void Rect_detect();
    void resert_flag();
    bool findmoudle(QPoint* pos,bool flag);//the line to moudle
    bool detect_line_connect(Line* linee);//检测line是否始末位置均已接入moudle；
    bool checkpos(Simulation_Moudle* moudle,QPoint* oldpos,int index,bool turn);
    int findindex_button(QPushButton* button);
    Flag checkposinput(Simulation_Moudle* moudle,QPoint* pos);
    Flag checkposoutput(Simulation_Moudle* moudle,QPoint* pos);
    QPoint* transform_position(QWidget* w1=nullptr,QWidget* w2=nullptr,QPoint* pos=nullptr);
    void delete_line();//直接删除line group
    void delete_line_way2();//删除当前line及分支line
    void Iteration_line(point* poi);
    void find_selected_point();
    void resume_line(point* poi);
    void delete_line_process(Line* linee,point* poi);
    void delete_moudle();
    bool change_input_count(Simulation_Moudle* moudle,int input);
    bool change_output_count(Simulation_Moudle* moudle,int output);
    io_count get_io_count(Simulation_Moudle* moudle);
    void updatenode(Simulation_Moudle* moudle);
    void newwindow();
    void adaptive();//窗口变动时Line与moudle自适应变化
    void checkdraw(int x,int y);//平滑移动line
    void selectall(int xs,int ys,int xe,int ye);
    void resort(int index);
    Simulation_Moudle* clone_moudle(Simulation_Moudle* moudle);
    void update_label_pos(Button* button);
    bool check_button_pos(QPoint point);
    void moudle_with_line();//在打开文件后将moudle与line连接起来   

    void socket_connect();
    void socket_disconnect();//socket通讯槽
    void socket_receive();
    int find_moudle_with_socket(QTcpSocket* socket,int flag);
    void dialog_change(int index);
    void send_data_torun(int index,double value);
    void reconnect(int index);//重新连接

    void cut_tag();

    void remove_tag(QString tag);//为了避免多个模块绑定同一标签，增加标签删除、插入功能
    void insert_tag(QString tag);
    QList<int> getnum(QString tag);//获取tag对应的number
    int sort_tag(QList<int> num,int index,int start);

    Simulation_Moudle* finished_flag(int id,int way);//信号传输完成标志位置位

    friend QDataStream &operator<<(QDataStream & , MainWindow&);
    friend QDataStream &operator>>(QDataStream & , MainWindow&);
   // void animateTimeout();
protected slots:
    void mousePressEvent(QMouseEvent* event);//按下
    void mouseMoveEvent(QMouseEvent* event);//按下移动
    void mouseReleaseEvent(QMouseEvent* event);//松开
    void mouseDoubleClickEvent(QMouseEvent* event);//双击
    //void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);
protected:
    void closeEvent(QCloseEvent *event);
  //  void wheelEvent(QWheelEvent* event);//滚轮

};

#endif // MAINWINDOW_H
