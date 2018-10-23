#include "custombuttongroup.h"
#include <QtWidgets>

typedef QList<const char*> analysis;
//typedef void FUNC_HELLO_PTR(void);
CustomButtonGroup::CustomButtonGroup(QWidget *parent):QWidget(parent)
{
    createbutton(parent);
}
void CustomButtonGroup::createbutton(QWidget *parent)
{// QButtonGroup* ana_group=new QButtonGroup();
    QPushButton* button_analysis;
    QGridLayout* mainLayout=new QGridLayout(parent);
    //QVBoxLayout* mainLayout = new QVBoxLayout(parent);
    analysis ana_string={"1","2","3","4","5","6"};
   // void *event_fun[6]={&CustomButtonGroup::ana1,&CustomButtonGroup::ana2,&CustomButtonGroup::ana3,&CustomButtonGroup::ana4,&CustomButtonGroup::ana5,&CustomButtonGroup::ana6};
  //  FUNC_HELLO_PTR *ptr=CustomButtonGroup::ana1;
    for(int i=0;i<ana_string.size();i++)
    {
       button_analysis=new QPushButton(tr(ana_string[i]));
   //    connect(button_analysis, &QAbstractButton::clicked, this, event_fun[i]);
       mainLayout->addWidget(button_analysis);
    }
    QRect size(100,100,1000,1000);
    this->setLayout(mainLayout);

     mainLayout->setGeometry(mainLayout->geometry());
    // mainLayout->setVerticalSpacing(20);
    // mainLayout->setColumnMinimumWidth(0,50);
   //  mainLayout->setRowStretch(1,1);
   // mainLayout->setColumnStretch(0,1);
    mainLayout->setOriginCorner(Qt::Corner::TopRightCorner);
   //  this->setGeometry(size);
}
void CustomButtonGroup::ana1(void)
{

}
void CustomButtonGroup::ana2()
{

}
void CustomButtonGroup::ana3()
{

}
void CustomButtonGroup::ana4()
{

}
void CustomButtonGroup::ana5()
{

}
void CustomButtonGroup::ana6()
{

}
