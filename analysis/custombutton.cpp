#include "custombutton.h"

custombutton::custombutton(QWidget *parent):QPushButton(parent)
{

}
void custombutton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int x,y;
    QPoint* oldpos=new QPoint();
    painter.setPen(QPen(Qt::black,2));
    for(int j=0;j<moudle->input.size();j++)
    {
        x=0;//moudle->button->x();
        y=0+(j+1)*moudle->button->height()/(moudle->input.size()+1);
        moudle->spacing=moudle->button->height()/(moudle->input.size()+1);
        oldpos->setX(x);
        oldpos->setY(y);
        painter.drawLine(x,oldpos->y()-moudle->spacing/2,x+moudle->spacing,oldpos->y());
        painter.drawLine(x,oldpos->y()+moudle->spacing/2,x+moudle->spacing,oldpos->y());

    }
    for(int j=0;j<moudle->output.size();j++)
    {
        moudle->spacing=moudle->button->height()/(moudle->output.size()+1);
        x=moudle->button->width()-moudle->spacing;
        y=(j+1)*moudle->button->height()/(moudle->output.size()+1);
        oldpos->setX(x);
        oldpos->setY(y);
        painter.drawLine(x,oldpos->y()-moudle->spacing/2,x+moudle->spacing,oldpos->y());
        painter.drawLine(x,oldpos->y()+moudle->spacing/2,x+moudle->spacing,oldpos->y());
    }
}
