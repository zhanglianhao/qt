#include "button.h"

Button::Button()
{

}
int Button::x()
{
    return this->pos_x;
}
int Button::y()
{
    return this->pos_y;
}
QPoint Button::pos()
{
    QPoint point;
    point.setX(this->pos_x);
    point.setY(this->pos_y);
    return point;
}
QSize Button::size()
{
    QSize size;
    size.setHeight(this->pos_height);
    size.setWidth(this->pos_width);
    return size;
}
int Button::width()
{
    return this->pos_width;
}
int Button::height()
{
    return this->pos_height;
}
QRect Button::rect()
{
    QRect rec;
    rec.setX(this->pos_x);
    rec.setY(this->pos_y);
    rec.setWidth(this->pos_width);
    rec.setHeight(this->pos_height);
    return rec;
}
void Button::resize(int w, int h)
{
    this->pos_width=w;
    this->pos_height=h;
}
void Button::resize(const QSize &size)
{
    this->pos_width=size.width();
    this->pos_height=size.height();
}
void Button::setGeometry(int x, int y, int w, int h)
{
    this->pos_x=x;
    this->pos_y=y;
    this->pos_width=w;
    this->pos_height=h;
}
void Button::setGeometry(const QRect& rect)
{
    this->pos_x=rect.x();
    this->pos_y=rect.y();
    this->pos_width=rect.width();
    this->pos_height=rect.height();
}
QRect Button::geometry()
{
    this->pos_rec.setX(this->pos_x);
    this->pos_rec.setY(this->pos_y);
    this->pos_rec.setWidth(this->pos_width);
    this->pos_rec.setHeight(this->pos_height);

    return this->pos_rec;
}
QRect Button::extend_geometry()
{
    this->pos_rec.setX(this->pos_x);
    this->pos_rec.setY(this->pos_y);
    this->pos_rec.setWidth(this->pos_width+this->group_interval);
    this->pos_rec.setHeight(this->pos_height);

    return this->pos_rec;
}
void Button::move(int x,int y)
{
    this->pos_x=x;
    this->pos_y=y;
}
void Button::setVisible(bool flag)
{
    this->flag=flag;
}
