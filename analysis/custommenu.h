#ifndef CUSTOMMENU_H
#define CUSTOMMENU_H
#include <QtWidgets>
#include "custombutton.h"
class custommenu
{
public:
    int group_x_start=150;
    int group_y_start=10;
    int group_interval=6;//moudle node position detect error
    int point_error=3;//moudle 自动连接line 偏差
    int line_error=4;//line Branch error
    int area=10;//drag position
    int scale_factor=100;//模块内部图案缩放因子
    QList<QPushButton*> pushbutton;
    QList<QButtonGroup*> buttom_group;
    QList<QAction*> action_group;
    QMenu* fileMenu;
    QMenu* edit;
    QMenu* moudlegroup;
    QMenu* run;
    QMenu* window;
    QMenu* helpMenu;
    QMenu* closeMenu;
    QMenu* pop_up_menu;//弹出式菜单
    QList<int> button_index;
    QGraphicsEffect* shadow;
    custommenu();
};

#endif // CUSTOMMENU_H
