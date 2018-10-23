#ifndef LINE_GROUP_H
#define LINE_GROUP_H
#include <QtWidgets>
#include "button.h"
#define display_error 1//0:仿真前显示error 1:实时显示error
struct point{

    int id;
    QPoint start;
    QPoint end;

    bool selected_flag=false;//被选中标志

    int proportion=0;//取值范围（0，1）*100该line的start点在父line的位置，用于指示父line移动时子line的移动位置
    bool turn_flag=false;//当前line的父line是否start与end发生翻转
    bool start_flag=false;//当前line的起点是否已连接
    bool end_flag=false;//当前line的终点是否已连接
    bool flag=false;//check connnect
    int start_line=0;//指示line的start或end哪一端与moudle输出端相连
    int end_line=0;//指示line的start或end哪一端与moudle输入端相连
    point* parent_line=nullptr;//从parent line中引出
    int parent_start_end=0;//1:表示当前分支从父line的start引出 2:表示当前分支从父line的end引出
    QList<point*> start_point;//表示从当前line的strat点上引出的分支line
    QList<point*> end_point;//表示从当前line的end点上引出的分支line
    QList<int> start_id;//文件读取使用到
    QList<int> end_id;
    QList<point*> branch;//从当前Line引出的分支集合
    QList<int> branch_id;//分支id,文件读取使用到
};

struct Line{

    int id;
    int point_current_id=0;
    bool complete;
    bool no_single=display_error==1?true:false;
    QList<Button*> startbutton;
    QList<Button*> endbutton;
    QList<point> line;
    QList<point*> endline;
    QList<point*> startline;
    QList<int> endindex;
    QList<int> startindex;
};

class line_group
{
public:
    int idcount=0;
    int current_id=0;
    int delete_id;

    int current_proportion=0;
    int scale=100;//
    point* parent_line;

    bool delete_flag=false;
    QList<Line*> group;
    Button* current_button;

    point* select_point;//指示被选中的point

    int start_end=0;//1:表示当前分支从父line的start引出 2:表示当前分支从父line的end引出

    line_group();
    Line* findwithid(int id);
    void current_idwithid(int id);//通过id寻找line在vector中的顺序
    bool line_exist(QPoint* point,int error);
    int exist(QPoint* point,QPoint* start,QPoint* end,int error);
    void startline(Button* button);
    void endline(Button* button,int index,bool flag,int nodeindex);
    void start_line(Button* button);
    bool insertline(QPoint* start,QPoint* end);
    void changeline(Button* button,QPoint* position,int inputsize,int outputsize);
    int moudle_point(Button* button,QPoint* pos,int error,bool flag,int nodeindex,bool leftright);
    point* deleteline(QPoint* pos,int error);
    void remove_output(Button* button,Line* linee);
    void remove_input(Line* linee);
    void turn_state(point* parent);//切换branch line的turn状态
    void change_linegroup(point* ppoint);
    void change_brance(point* point_parent,point* point_child);
    int findindex_input();
    int findindex_output(Line* line,Button* button);
    point* find_point_withid(Line* line,int id);

};

#endif // LINE_GROUP_H
