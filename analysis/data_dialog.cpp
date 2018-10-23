#include "data_dialog.h"

data_dialog::data_dialog(QWidget *parent):QDialog(parent)
{
    init();
}
void data_dialog::resizeEvent(QResizeEvent *)
{
    this->resize(window_size);
}
void data_dialog::init()
{
    window_size=this->size();
    this->setWindowTitle("数据分析");
    //this->left_view=new QListView(this);
    //this->left_view->setGeometry(int(this->width()*0.1),int(this->height()*0.1),int(this->width()*0.35),int(this->height()*0.7));
    //this->right_view=new QListView(this);
    //this->right_view->setGeometry(int(this->width()*0.55),int(this->height()*0.1),int(this->width()*0.35),int(this->height()*0.7));

    left_scroll=new QScrollArea(this);
    this->left_scroll->setGeometry(int(this->width()*0.1),int(this->height()*0.1),int(this->width()*0.35),int(this->height()*0.7));

    this->right_scroll=new QScrollArea(this);
    this->right_scroll->setGeometry(int(this->width()*0.55),int(this->height()*0.1),int(this->width()*0.35),int(this->height()*0.7));

    this->left_view=new QListView(left_scroll);
    left_scroll->setWidget(left_view);
    left_view->resize(int(this->width()*0.35),336);
    left_scroll->show();
    this->right_view=new QListView(right_scroll);
    right_scroll->setWidget(right_view);
    right_view->resize(int(this->width()*0.35),336);
    right_scroll->show();

    this->join=new QPushButton(this);
    this->join->setText("加入文件");
    this->join->setGeometry(int(this->width()*0.25),int(this->height()*0.85),int(this->width()*0.1),int(this->height()*0.06));
    connect(this->join, &QPushButton::clicked, this, &data_dialog::join_text);

    this->remove=new QPushButton(this);
    this->remove->setText("移除");
    this->remove->setGeometry(int(this->width()*0.46),int(this->height()*0.4),int(this->width()*0.08),int(this->height()*0.06));
    connect(this->remove, &QPushButton::clicked, this, &data_dialog::remove_box);

    this->left_move=new QPushButton(this);
    this->left_move->setText("左移");
    this->left_move->setGeometry(int(this->width()*0.46),int(this->height()*0.2),int(this->width()*0.08),int(this->height()*0.06));
    connect(this->left_move, &QPushButton::clicked, this, &data_dialog::move_to_left);

    this->right_move=new QPushButton(this);
    this->right_move->setText("右移");
    this->right_move->setGeometry(int(this->width()*0.46),int(this->height()*0.6),int(this->width()*0.08),int(this->height()*0.06));
    connect(this->right_move, &QPushButton::clicked, this, &data_dialog::move_to_right);

    this->start=new QPushButton(this);
    this->start->setText("分析");
    this->start->setGeometry(int(this->width()*0.7),int(this->height()*0.85),int(this->width()*0.1),int(this->height()*0.06));
    connect(this->start, &QPushButton::clicked, this, &data_dialog::start_analysis);
    //connect(this->start, &QAbstractButton::clicked, this, &QDialog::accept);

    this->left_gLayout=new QGridLayout;
    this->left_view->setLayout(this->left_gLayout);

    this->right_Layout=new QGridLayout;
    this->right_view->setLayout(this->right_Layout);
}
void data_dialog::state_change()
{
    if(stop_trigger==true)
        return;
    QCheckBox* box=qobject_cast<QCheckBox*>(sender());
    if(this->checkbox_group_left.indexOf(box)!=-1)
    {
        if(checked_flag_left[this->checkbox_group_left.indexOf(box)]==true)
            checked_flag_left[this->checkbox_group_left.indexOf(box)]=false;
        else
            checked_flag_left[this->checkbox_group_left.indexOf(box)]=true;
    }
    if(this->checkbox_group_right.indexOf(box)!=-1)
    {
        if(checked_flag_right[this->checkbox_group_right.indexOf(box)]==true)
            checked_flag_right[this->checkbox_group_right.indexOf(box)]=false;
        else
            checked_flag_right[this->checkbox_group_right.indexOf(box)]=true;
    }
    //qDebug()<<checked_flag_left[this->checkbox_group_left.indexOf(box)];
}
void data_dialog::move_to_left()
{
    stop_trigger=true;
    for(int i=0;i<this->checked_flag_right.size();i++)
    {
        if(this->checked_flag_right[i]==true)
        {
            this->checked_flag_right.removeAt(i);
            this->checked_flag_left.push_back(false);
            this->checkbox_group_left.push_back(this->checkbox_group_right[i]);
            this->right_Layout->removeWidget(this->checkbox_group_right[i]);
            this->left_gLayout->addWidget(this->checkbox_group_right[i]);
            this->checkbox_group_left[checkbox_group_left.size()-1]->setCheckState(Qt::Unchecked);

            this->checkbox_group_right.removeAt(i);
            i--;
        }
    }
    stop_trigger=false;
    updata_pos();
}
void data_dialog::move_to_right()
{
    stop_trigger=true;
    for(int i=0;i<this->checked_flag_left.size();i++)
    {
        if(this->checked_flag_left[i]==true)
        {
            this->checked_flag_left.removeAt(i);
            this->checked_flag_right.push_back(false);
            this->checkbox_group_right.push_back(this->checkbox_group_left[i]);
            this->left_gLayout->removeWidget(this->checkbox_group_left[i]);
            this->right_Layout->addWidget(this->checkbox_group_left[i]);
            this->checkbox_group_right[checkbox_group_right.size()-1]->setCheckState(Qt::Unchecked);

            this->checkbox_group_left.removeAt(i);
            i--;
        }
    }
    stop_trigger=false;
    updata_pos();
}
void data_dialog::updata_pos()
{
    this->left_view->resize(this->left_view->width(),checkbox_group_left.size()*30<336?336:checkbox_group_left.size()*30);
    this->right_view->resize(this->left_view->width(),checkbox_group_right.size()*30<336?336:checkbox_group_right.size()*30);
    /*
    for(int i=0;i<checkbox_group_left.size();i++)
        left_gLayout->removeWidget(checkbox_group_left[i]);
    for(int i=0;i<checkbox_group_right.size();i++)
        left_gLayout->removeWidget(checkbox_group_right[i]);
    for(int i=0;i<checkbox_group_left.size();i++)
        left_gLayout->addWidget(checkbox_group_left[i],i,0);
    left_gLayout->setSpacing(0);
    */
}
void data_dialog::remove_box()
{
    for(int i=0;i<this->checked_flag_right.size();i++)
    {
        if(this->checked_flag_right[i]==true)
        {
            this->checked_flag_right.removeAt(i);
            this->right_Layout->removeWidget(this->checkbox_group_right[i]);
            int index=button_group.indexOf(this->checkbox_group_right[i]);
            url.removeAt(index);
            button_group.removeAt(index);

            delete this->checkbox_group_right[i];
            this->checkbox_group_right.removeAt(i);

            i--;
        }
    }
    for(int i=0;i<this->checked_flag_left.size();i++)
    {
        if(this->checked_flag_left[i]==true)
        {
            this->checked_flag_left.removeAt(i);
            this->left_gLayout->removeWidget(this->checkbox_group_left[i]);
            int index=button_group.indexOf(this->checkbox_group_left[i]);
            url.removeAt(index);
            button_group.removeAt(index);

            delete this->checkbox_group_left[i];
            this->checkbox_group_left.removeAt(i);
            i--;
        }
    }
    updata_pos();
}
void data_dialog::join_text()
{
    QList<QString> fileName;
    fileName=QFileDialog::getOpenFileNames(this,tr("打开"),"",tr("Config Files (*.txt)"));
    if(fileName.size()!=0)
    {
        for(int i=0;i<fileName.size();i++)
        {
            if(url.indexOf(fileName[i])==-1)
            {
                url.push_back(fileName[i]);
                QCheckBox* box=new QCheckBox(url_to_name(fileName[i]));
                box->resize(int(this->width()*0.2),int(this->height()*0.06));
                this->left_gLayout->addWidget(box);
                connect(box, &QCheckBox::stateChanged, this, &data_dialog::state_change);
                this->checkbox_group_left.push_back(box);
                checked_flag_left.push_back(false);
                button_group.push_back(box);
            }
        }
    }
    updata_pos();
    //this->left_view->resize(this->left_view->width(),checkbox_group_left.size()*30<336?336:checkbox_group_left.size()*30);
    //qDebug()<<checkbox_group_left[0]->height()<<left_scroll->height();
}
QString data_dialog::url_to_name(QString fileName)
{
    int index1=0,index2=0;
    QString name="";
    for(int i=fileName.size()-1;i>=0;i--)
    {
        if(fileName[i]=='.')
        {
            index1=i-1;
            break;
        }
    }
    for(int i=fileName.size()-1;i>=0;i--)
    {
        if(fileName[i]=='/'||fileName[i]=='\\')
        {
            index2=i+1;
            break;
        }
    }
    for(int i=index2;i<=index1;i++)
    {
        name+=fileName[i];
    }
    return name;

}
void data_dialog::start_analysis()
{
    for(int i=0;i<checkbox_group_right.size();i++)
    {
        int index=button_group.indexOf(checkbox_group_right[i]);
        qDebug()<<url[index];//输出文件地址 数据分析时调用
    }
}
