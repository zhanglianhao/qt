#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <QtWidgets>
#include <qtextcodec.h>
#include <QtNetwork>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "moudel_group.h"
class algorithm_file;
class algorithm;
struct ui_socket
{
    QList<QLineEdit*> address;//输入接口绑定ip
    QLineEdit *port;
    Simulation_Moudle* moudle=nullptr;
    int way;//0 input 1 output
};
class algorithm_file:public QObject
{   Q_OBJECT
public:
    algorithm_file(QObject *parent = nullptr);
private:
    moudel_group* simulation_group=new moudel_group();
    bool start_run=false;
    int simu_step;
    QTimer* send_clock=new QTimer();//用于判定规定时间内是否所有接口模块（38，39）输出端信号全部发送完毕
    QTimer* rece_clock=new QTimer();//用于判定规定时间内是否所有接口模块（38，39）输入端信号全部接收完毕
    void init();
    void readdata();
    QString getstr(QString str);
    void run_();

    void run_simulation(Simulation_Moudle* moudle);
    bool check_input(Simulation_Moudle* moudle,int index,double value);
    void calculation(Simulation_Moudle* moudle);
    void clear_finish_flag(int way);
    Simulation_Moudle* finished_flag(int id,int way);
    void data_process(QString key,QString value);
    void send_data_torun(int index,double value);
    int find_moudle_with_socket(QTcpSocket* socket,int flag);
    void reconnect(int index);
    QStringList url_to_name(QString fileName);//地址转文件名

    /*
    void socket_connect();
    void socket_disconnect();
    */
    void socket_receive();
private slots:
    /*
    void rece_Timeout();
    void send_Timeout();
    */
};
class algorithm:public QDialog
{
public:
    algorithm(QWidget *parent = nullptr);
    void init(moudel_group* group);
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
    bool stop_flag=false;
    QStringList tag;//存储所有机柜中节点的标签
    QList<QList<int>> tag_number_group;
    QStringList tag_temp;//存储所有机柜中节点的标签
    QMap<QComboBox*,Simulation_Moudle*> box_to_moudle;
    QMap<QComboBox*,bool> box_to_flag;
    QMap<QPushButton*,ui_socket*> button_to_ui;
    ui_socket* socket_main=new ui_socket();
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

    QPushButton* find_with_socket(QTcpSocket* socket);
    void socket_connect();
    void socket_disconnect();
    void socket_receive();

    void remove_tag(QString tag);//为了避免多个模块绑定同一标签，增加标签删除、插入功能
    void insert_tag(QString tag);
    QList<int> getnum(QString tag);//获取tag对应的number
    int sort_tag(QList<int> num,int index,int start);

    void run_analysis();
    bool detect_connect();
};

#endif // ALGORITHM_H
