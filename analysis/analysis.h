#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <QMainWindow>
#include "custommenu.h"
#include "ui.h"
#include "copygroup.h"
#include <QCloseEvent>
#include "run_simu.h"
#include "customtreewidget.h"
#include "data_dialog.h"
#include "fault_dialog.h"
#include "paramdialog.h"
#include "algorithm.h"
#define format ".ifg"//保存格式
#define autosave 1//是否开启自动保存
class MainWindow;
class analysis;
class scoll;
class Run_Simu;
class QTreeWidget2;
struct childwindow
{
    bool place_flag=false;
    bool paste_flag=false;
    int index=0;
};
class QTreeWidget2:public QTreeWidget
{
    Q_OBJECT
public:
    explicit QTreeWidget2(QWidget *parent =nullptr);
    void init(analysis* parent);
protected:
    void mouseReleaseEvent(QMouseEvent *event);
private:
    analysis* parent;
    void double_click();
};
class scoll:public QScrollArea
{
public:
    analysis* parent;
    explicit scoll(QWidget *pare,analysis* par);
public:
    void closeEvent(QCloseEvent *event);
};
class analysis : public QMainWindow
{
    Q_OBJECT
    friend class scoll;
public:
    MainWindow* mainwindow_current=nullptr;
    explicit analysis(QWidget *parent = nullptr);
    childwindow* child=new childwindow();
    QList<MainWindow*> mainwindow_group;   
    copygroup* copy_moudle_group=new copygroup();
    Run_Simu* run_current;
    bool draw_flag=false;
    bool select_flag=false;  
    void save_as(int way);//way=0:保存组态框图至.ifg way=1:保存仿真数据至.txt
    bool openfile(QString fileName,int way,int openway);//是否跳过文件存在性检验 是否由工程打开
    int  message_box_main(MainWindow* window,int flag);
    int  custom_message_box(QString title,QStringList lis);//自定义弹出式菜单
    void save_graph_date();
    void save_graph(int index);
    void save_state();
    int  close_acess(int index);//关闭窗口时访问return 0:save 1:not save 2:cancel
    void addfile(QString url);
    void remove_file_project(int way);
    void removefile(QString url,int way);
    void remove_file();
    void removeproject(int index);
    void remove_project();
    void whitch_project(QString url);
    int find_with_url(QString url);
    void project_event();
    void update_tree(QString name);
    void statr_message(QString message,int time);//状态栏信息显示
    int run_to_mainwindow(Run_Simu* run);
    QList<QStringList> url_group;
    QStringList url_group_temp;
    QMap<QString,QTreeWidgetItem*> str_to_map;
    paramdialog* dialog;
signals:

public slots:
    void on_pressed();
private slots:
    void timerSlot();
protected slots:
    void mousePressEvent(QMouseEvent* event);//按下
private:
    QTreeWidget2* project;
    UI *ui;
    CustomTreeWidget* customtree;
    custommenu* custom_menu=new custommenu();
    int windowid=1;
    int openway=0;//0：打开文件 1：打开工程
    QList<scoll*> scoll_group;
    Run_Simu* run;
    QList<scoll*> run_scoll;
    QList<Run_Simu*> run_group;
    QList<QMdiSubWindow*> mid_group;
    QTimer mDataTimer;
    QWidget* helpwindow;
    QStringList project_url;
    int current_project_id=0;//记录当前project id
    int current_file_id=0;//记录当前file id
    bool open_way=false;

    void init();
    void menu();//set menu
    void pop_menu();
    void group();
    void tool();
    void init_button();
    void findgroup();
    void findgroup_menu();
    void findgroup_way(int index);
    QAbstractButton* findbutton(int index);
    void set_position(int index,bool flag);
    void setbutton_position(QAbstractButton* button,int x,int y);
    void set_shadow(QWidget *widget);
    void remove_shadow(QWidget *widget);
    bool find(QList<int> group,int index);
    void newwindow();
    void fault_window();
    int findindex_button(QPushButton* button);
    void clonemoudle();//复制或剪切当前模块
    void cutmoudle();
    void pastemoudle();//粘贴临时模块
    void deleteany();
    void newproject();
    void openproject();
    void rename();
    void close();
    void help();   
    void paintEvent(QPaintEvent *);
    void data_analysis();
    void export_algorithm();
    void test_algorithm();
    void test();
    void test_simulation();
    void start_simu(bool flag);
    void dialog_simu();
    void open();
    void open_files();
    void save();
    void saveall();
    void auto_save();
    QStringList url_to_name(QString fileName);   
    QPoint* transform_position(QWidget* w1,QWidget* w2,QPoint* pos);
    friend QDataStream &operator<<(QDataStream & , QStringList&);
    friend QDataStream &operator>>(QDataStream & , QStringList&);

    void create_empty_project(QString fileName);
    QString exist_project(QString fileName);
    void modify_name(QString oldname,QString newname,int way);
    void write_project();//将当前project数据写入文件
    void addnewfile();
    void addexistfile();
    void project_files_ope(QString url);
    int find_file_project(QString url);//-1 未从当前打开工程中找到文件
protected slots:
    //void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);
protected:
    void closeEvent(QCloseEvent *event);
};


#endif // ANALYSIS_H
