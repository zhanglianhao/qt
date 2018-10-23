#ifndef BUTTON_H
#define BUTTON_H
#include <QtWidgets>
class Button
{
public:
    Button();
    int x();
    int y();
    QPoint pos();
    QSize size();
    int width();
    int height();
    QRect rect();
    void resize(int w, int h);
    void resize(const QSize & size);
    void setGeometry(int x, int y, int w, int h);
    void setGeometry(const QRect& rect);
    QRect geometry();
    QRect extend_geometry();
    void setVisible(bool flag);
    void move(int x,int y);
private:
    QRect pos_rec;
    bool flag=true;
    int pos_x;
    int pos_y;
    int pos_width;
    int pos_height;
    int group_interval=6;//moudle node position detect error 与custommenu中一致
};

#endif // QPUSHBUTTON_H
