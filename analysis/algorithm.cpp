#include "algorithm.h"
algorithm::algorithm(QWidget *parent):QDialog(parent)
{
    this->tab_widget=new QTabWidget();

    tag_scoll=new QScrollArea();
    socket_scoll=new QScrollArea();

    this->tag_dialog=new QDialog(tag_scoll);
    this->socket_dialog=new QDialog(socket_scoll);

    tag_scoll->setWidget(tag_dialog);
    socket_scoll->setWidget(socket_dialog);

    tag_scoll->show();
    socket_scoll->show();

    this->tab_widget->addTab(tag_scoll,"tag_bind");
    this->tab_widget->addTab(socket_scoll,"one by one connect");
    connect(this->tab_widget,&QTabWidget::currentChanged,this,&algorithm::tab_change);
    QVBoxLayout* vbox=new QVBoxLayout();
    vbox->addWidget(this->tab_widget);
    text_edit=new QLineEdit();
    //text_edit->resize(220,100);
    socket_main->address.push_back(new QLineEdit("192"));
    socket_main->address.push_back(new QLineEdit("168"));
    socket_main->address.push_back(new QLineEdit("1"));
    socket_main->address.push_back(new QLineEdit("1"));
    socket_main->port=new QLineEdit("8080");
    this->layout(vbox,socket_main);
    vbox->addWidget(run_button);
    connect(run_button,&QAbstractButton::pressed,this,&algorithm::run_analysis);

    vbox->addWidget(text_edit);
    text_edit->setEnabled(false);
    this->setLayout(vbox);
}
void algorithm::init(moudel_group* group)
{
    this->moudle=group;
    init_moudle();
    init_ui();
}
void algorithm::tab_change()
{
    if(page_change==false)
    {
        this->resize(250,500);
        page_change=true;
    }
    else
    {
        this->resize(250,500);
        page_change=false;
    }
}
void algorithm::init_moudle()
{
    for(int i=0;i<this->moudle->group.size();i++)
    {
        if(moudle->group[i]->index==38)
        {
            if(moudle->group[i]->bind_interface->input_flag==true||moudle->group[i]->bind_interface->output_flag==true)
                this->socket_group->group.push_back(moudle->group[i]);
            if(moudle->group[i]->bind_interface->input_flag==true)
            {
                moudle->group[i]->bind_interface->input_socket=new QTcpSocket();
                connect(moudle->group[i]->bind_interface->input_socket,&QTcpSocket::connected,this,&algorithm::socket_connect);
                connect(moudle->group[i]->bind_interface->input_socket,&QTcpSocket::disconnected,this,&algorithm::socket_disconnect);
                connect(moudle->group[i]->bind_interface->input_socket,&QIODevice::readyRead,this,&algorithm::socket_receive);
            }
            if(moudle->group[i]->bind_interface->output_flag==true)
            {
                moudle->group[i]->bind_interface->output_socket=new QTcpSocket();
                connect(moudle->group[i]->bind_interface->output_socket,&QTcpSocket::connected,this,&algorithm::socket_connect);
                connect(moudle->group[i]->bind_interface->output_socket,&QTcpSocket::disconnected,this,&algorithm::socket_disconnect);
                connect(moudle->group[i]->bind_interface->output_socket,&QIODevice::readyRead,this,&algorithm::socket_receive);
            }
        }
        else if(moudle->group[i]->index==39)
        {
            if(moudle->group[i]->tag_bind->input_flag==true||moudle->group[i]->tag_bind->output_flag==true)
                this->tag_group->group.push_back(moudle->group[i]);
        }
    }
    for(int i=0;i<8;i++)
        for(int j=0;j<50;j++)
        {
            QList<int> num;
            num.push_back(i);
            num.push_back(j);
            this->tag_number_group.push_back(num);
            this->tag.push_back(QString::number(i)+"-"+QString::number(j));
        }
    this->tag_temp=this->tag;
}
void algorithm::init_ui()
{
    init_ui_tag();
    init_ui_socket();
    this->resize(250,500);
    this->tag_dialog->resize(200,this->tag_group->group.size()*40>300?this->tag_group->group.size()*40:300);
    this->socket_dialog->resize(200,this->socket_group->group.size()*300);
}
void algorithm::init_ui_tag()
{
    QVBoxLayout* vbox;
    QHBoxLayout* hbox;
    if(this->tag_group->group.size()!=0)
    {
        vbox=new QVBoxLayout();
        hbox=new QHBoxLayout();
        //hbox->addWidget(new QLabel("name"));
        //hbox->addWidget(new QLabel("input"));
        //hbox->addWidget(new QLabel("output"));
        //vbox->addLayout(hbox);
        for(int i=0;i<this->tag_group->group.size();i++)
        {
            hbox=new QHBoxLayout();
            hbox->addWidget(new QLabel(this->tag_group->group[i]->name));
            QComboBox* box=new QComboBox();
            if(this->tag_group->group[i]->tag_bind->input_flag==true)
            {
                box->addItems(this->tag_temp);
                int index=this->tag_temp.indexOf(this->tag_group->group[i]->tag_bind->input_tag);
                stop_flag=true;
                box->setCurrentIndex(index);
                stop_flag=false;
                box_to_moudle.insert(box,this->tag_group->group[i]);
                box_to_flag.insert(box,true);
                connect(box,&QComboBox::currentTextChanged,this,&algorithm::combbox_change);
            }
            else
            {
                box->setEnabled(false);
            }
            hbox->addWidget(box);

            box=new QComboBox();
            if(this->tag_group->group[i]->tag_bind->output_flag==true)
            {
                box->addItems(this->tag_temp);
                stop_flag=true;
                box->setCurrentIndex(this->tag_temp.indexOf(this->tag_group->group[i]->tag_bind->output_tag));
                stop_flag=false;
                box_to_moudle.insert(box,this->tag_group->group[i]);
                box_to_flag.insert(box,false);
                connect(box,&QComboBox::currentTextChanged,this,&algorithm::combbox_change);
            }
            else
            {
                box->setEnabled(false);
            }
            hbox->addWidget(box);
            vbox->addLayout(hbox);
        }
        this->tag_dialog->setLayout(vbox);
    }


}
void algorithm::init_ui_socket()
{
    QVBoxLayout* vbox;
    if(this->socket_group->group.size()!=0)
    {
        vbox=new QVBoxLayout();
        for(int i=0;i<this->socket_group->group.size();i++)
        {
            QVBoxLayout* vvbox=new QVBoxLayout();
            vvbox->addWidget(new QLabel("name:"+this->socket_group->group[i]->name));
            vvbox->addWidget(new QLabel("input:"));
            QPushButton* button=new QPushButton("connect");
            connect(button,&QAbstractButton::pressed,this,&algorithm::clicked_button);
            ui_socket* ui=new ui_socket();
            ui->moudle=this->socket_group->group[i];
            ui->way=0;
            this->button_to_ui.insert(button,ui);
            ui->address.push_back(new QLineEdit("192"));
            ui->address.push_back(new QLineEdit("168"));
            ui->address.push_back(new QLineEdit("1"));
            ui->address.push_back(new QLineEdit("1"));
            ui->port=new QLineEdit("8080");
            this->layout(vvbox,ui);
            vvbox->addWidget(button);

            if(this->socket_group->group[i]->bind_interface->input_flag==true)
            {
                for(int j=0;j<4;j++)
                    ui->address[j]->setText(QString::number(this->socket_group->group[i]->bind_interface->input_ip[j]));
                ui->port->setText(QString::number(this->socket_group->group[i]->bind_interface->input_port));
                button->setEnabled(true);
            }
            else
            {
                for(int j=0;j<4;j++)
                    ui->address[j]->setEnabled(false);
                ui->port->setEnabled(false);
                button->setEnabled(false);
            }
            QPushButton* button1=new QPushButton("connect");
            connect(button1,&QAbstractButton::pressed,this,&algorithm::clicked_button);
            vvbox->addWidget(new QLabel("output:"));
            ui=new ui_socket();
            ui->moudle=this->socket_group->group[i];
            ui->way=1;
            this->button_to_ui.insert(button1,ui);
            ui->address.push_back(new QLineEdit("192"));
            ui->address.push_back(new QLineEdit("168"));
            ui->address.push_back(new QLineEdit("1"));
            ui->address.push_back(new QLineEdit("1"));
            ui->port=new QLineEdit("8080");
            this->layout(vvbox,ui);
            vvbox->addWidget(button1);

            if(this->socket_group->group[i]->bind_interface->output_flag==true)
            {
                for(int j=0;j<4;j++)
                    ui->address[j]->setText(QString::number(this->socket_group->group[i]->bind_interface->output_ip[j]));
                ui->port->setText(QString::number(this->socket_group->group[i]->bind_interface->output_port));
                button1->setEnabled(true);
            }
            else
            {
                for(int j=0;j<4;j++)
                    ui->address[j]->setEnabled(false);
                ui->port->setEnabled(false);
                button1->setEnabled(false);
            }
            vbox->addLayout(vvbox);
        }
        this->socket_dialog->setLayout(vbox);
    }
}
void algorithm::layout(QVBoxLayout* vbox,ui_socket* ui)
{
    QHBoxLayout* hbox;
    hbox=new QHBoxLayout();
    vbox->addWidget(new QLabel("address"));
    hbox->addWidget(ui->address[0]);
    hbox->addWidget(new QLabel("."));
    hbox->addWidget(ui->address[1]);
    hbox->addWidget(new QLabel("."));
    hbox->addWidget(ui->address[2]);
    hbox->addWidget(new QLabel("."));
    hbox->addWidget(ui->address[3]);
    vbox->addLayout(hbox);
    vbox->addWidget(new QLabel("port"));
    vbox->addWidget(ui->port);
}
void algorithm::combbox_change(QString str)
{
    if(stop_flag==true)
        return;

    QComboBox* box=qobject_cast<QComboBox*>(sender());
    if(this->box_to_flag.contains(box)==true)
    {
        this->text_edit->setText("");
        if(this->box_to_flag[box]==true)
        {
            if(this->tag.indexOf(str)!=-1)
            {
                if(this->box_to_moudle[box]->tag_bind->input_tag!="-1"&&this->box_to_moudle[box]->tag_bind->input_tag!="")
                    this->insert_tag(this->box_to_moudle[box]->tag_bind->input_tag);
                this->box_to_moudle[box]->tag_bind->input_tag=str;
                this->remove_tag(str);
            }
            else
            {
                int index=this->tag_temp.indexOf(this->box_to_moudle[box]->tag_bind->input_tag);
                stop_flag=true;
                box->setCurrentIndex(index);
                stop_flag=false;
                this->text_edit->setText(str+" already exists");
            }
        }
        else
        {
            if(this->tag.indexOf(str)!=-1)
            {
                if(this->box_to_moudle[box]->tag_bind->output_tag!="-1"&&this->box_to_moudle[box]->tag_bind->output_tag!="")
                    this->insert_tag(this->box_to_moudle[box]->tag_bind->output_tag);
                this->box_to_moudle[box]->tag_bind->output_tag=str;
                this->remove_tag(str);
            }
            else
            {
                int index=this->tag_temp.indexOf(this->box_to_moudle[box]->tag_bind->output_tag);
                stop_flag=true;
                box->setCurrentIndex(index);
                stop_flag=false;
                this->text_edit->setText(str+" already exists");
            }
        }
    }
}
void algorithm::remove_tag(QString tag)
{
    if(this->tag.indexOf(tag)!=-1)
    {
        int index=this->tag.indexOf(tag);
        this->tag_number_group.removeAt(index);
        this->tag.removeAt(index);
    }
}
void algorithm::insert_tag(QString tag)
{
    if(this->tag.contains(tag)==false)
    {
        QList<int> num=getnum(tag);
        int index=sort_tag(num,0,0);
        this->tag.insert(index,tag);
        this->tag_number_group.insert(index,num);
    }
}
int algorithm::sort_tag(QList<int> num,int index,int start)
{
    for(int i=start;i<this->tag.size();i++)
    {
        if(num[index]<this->tag_number_group[i][index])
        {
            return i;
        }
        else if(num[index]==this->tag_number_group[i][index])
        {
            return sort_tag(num,index+1,i);
        }
        else
        {
            if(index>=1&&i>=1)
            {
                if(this->tag_number_group[i][index-1]!=this->tag_number_group[i-1][index-1])
                    return i-1;
            }
        }
    }
    return this->tag.size();
}
QList<int> algorithm::getnum(QString tag)
{
    QList<int> num;
    QString tag_child="";
    for(int i=0;i<tag.size();i++)
    {
        if(tag[i]=='-')
        {
            num.push_back(tag_child.toInt());
            tag_child="";
        }
        else
        {
            tag_child+=tag[i];
        }
    }
    num.push_back(tag_child.toInt());
    return num;
}
void algorithm::run_analysis()
{
    if(detect_connect()==true)
    {
        this->text_edit->setText("start run");
        emit this->accept();
    }
}
bool algorithm::detect_connect()
{
    for(int i=0;i<this->tag_group->group.size();i++)
    {
        if(this->tag_group->group[i]->tag_bind->input_flag==true&&this->tag_group->group[i]->tag_bind->input_tag=="-1")
        {
            this->text_edit->setText(this->tag_group->group[i]->name+" input cannot bind tag");
            return false;
        }
        if(this->tag_group->group[i]->tag_bind->output_flag==true&&this->tag_group->group[i]->tag_bind->output_tag=="-1")
        {
            this->text_edit->setText(this->tag_group->group[i]->name+" output cannot bind tag");
            return false;
        }
    }
    for(int i=0;i<this->socket_group->group.size();i++)
    {
        if(this->socket_group->group[i]->bind_interface->input_flag==true&&this->socket_group->group[i]->bind_interface->input_success==false)
        {
            this->text_edit->setText(this->socket_group->group[i]->name+" input connect failed");
            return false;
        }
        if(this->socket_group->group[i]->bind_interface->output_flag==true&&this->socket_group->group[i]->bind_interface->output_success==false)
        {
            this->text_edit->setText(this->socket_group->group[i]->name+" input connect failed");
            return false;
        }
    }
    return true;
}
void algorithm::clicked_button()
{
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    if(this->button_to_ui.contains(button)==true)
    {
        ui_socket* ui=this->button_to_ui[button];
        if(button->text()=="connect")
        {
            QString ip=ui->address[0]->text()+"."+ui->address[1]->text()+"."+ui->address[2]->text()+"."+ui->address[3]->text();
            QHostAddress host;
            host.setAddress(ip);
            if(ui->way==0)
                ui->moudle->bind_interface->input_socket->connectToHost(host,quint16(ui->port->text().toInt()));
            else if(ui->way==1)
                ui->moudle->bind_interface->output_socket->connectToHost(host,quint16(ui->port->text().toInt()));
        }
        else if(button->text()=="disconnect")
        {
            if(ui->way==0)
                ui->moudle->bind_interface->input_socket->disconnectFromHost();
            else
                ui->moudle->bind_interface->output_socket->disconnectFromHost();
        }
    }
}
QPushButton* algorithm::find_with_socket(QTcpSocket* socket)
{
    QList<QPushButton*> button_group=this->button_to_ui.keys();
    for(int i=0;i<button_group.size();i++)
    {
        if(this->button_to_ui[button_group[i]]->moudle->bind_interface->output_socket==socket||this->button_to_ui[button_group[i]]->moudle->bind_interface->input_socket==socket)
            return button_group[i];
    }
    return nullptr;
}
void algorithm::socket_connect()
{
    qDebug()<<"connected";
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    QPushButton* button=this->find_with_socket(socket);
    button->setText("disconnect");
    ui_socket* ui=this->button_to_ui[button];
    if(ui->way==0)
    {
        for(int i=0;i<4;i++)
            ui->moudle->bind_interface->input_ip[i]=ui->address[i]->text().toInt();
        ui->moudle->bind_interface->input_port=ui->port->text().toInt();
    }
    else if(ui->way==1)
    {
        for(int i=0;i<4;i++)
            ui->moudle->bind_interface->output_ip[i]=ui->address[i]->text().toInt();
        ui->moudle->bind_interface->output_port=ui->port->text().toInt();
    }
    if(this->button_to_ui[button]->way==0)
        this->button_to_ui[button]->moudle->bind_interface->input_success=true;
    else if(this->button_to_ui[button]->way==1)
        this->button_to_ui[button]->moudle->bind_interface->output_success=true;
}
void algorithm::socket_disconnect()
{
    qDebug()<<"disconnected";
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    QPushButton* button=this->find_with_socket(socket);
    button->setText("connect");
    if(this->button_to_ui[button]->way==0)
        this->button_to_ui[button]->moudle->bind_interface->input_success=false;
    else if(this->button_to_ui[button]->way==1)
        this->button_to_ui[button]->moudle->bind_interface->output_success=false;
}
void algorithm::socket_receive()
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
}
algorithm_file::algorithm_file(QObject *parent):QObject(parent)
{
    //init();
    //run_();
    //readdata();
}
/*
void algorithm_file::readdata()
{
    QString filename=QFileDialog::getOpenFileName(nullptr,tr("import algorithm"),"",tr("Config Files (*.alg)"));
    if(!filename.isNull())
    {
        QFile* file=new QFile(filename);
        if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }
        QByteArray byt=file->readAll();
        QString str(byt);
        int moudle_count;
        int i_temp;
        double d_temp;
        QString s_temp;
        moudle_count=getstr(str).toInt();
        for(int i=0;i<moudle_count;i++)
        {
            Simulation_Moudle* moudle=new Simulation_Moudle();
            i_temp=getstr(str).toInt();
            for(int j=0;j<i_temp;j++)
            {
                d_temp=getstr(str).toDouble();
                moudle->param.push_back(d_temp);
            }
            i_temp=getstr(str).toInt();
            moudle->index=i_temp;
            i_temp=getstr(str).toInt();
            moudle->id=i_temp;
            s_temp=getstr(str);
            moudle->name=s_temp;
            i_temp=getstr(str).toInt();
            moudle->input_size=i_temp;
            i_temp=getstr(str).toInt();
            moudle->output_size=i_temp;
            i_temp=getstr(str).toInt();
            for(int j=0;j<i_temp;j++)
            {
                moudle_param* param=new moudle_param();
                int temp=getstr(str).toInt();
                for(int m=0;m<temp;m++)
                {
                    moudle_relation rela;
                    rela.id=getstr(str).toInt();
                    rela.index=getstr(str).toInt();
                    param->next.push_back(rela);
                }
                moudle->output.push_back(param);
            }
            if(moudle->index==38)
            {
                interface_bind* inter=new interface_bind();
                inter->input_flag=getstr(str).toInt();
                int temp=getstr(str).toInt();
                for(int j=0;j<temp;j++)
                    inter->input_ip.push_back(getstr(str).toInt());
                inter->input_port=getstr(str).toInt();
                inter->output_flag=getstr(str).toInt();
                temp=getstr(str).toInt();
                for(int j=0;j<temp;j++)
                    inter->output_ip.push_back(getstr(str).toInt());
                inter->output_port=getstr(str).toInt();
                moudle->bind_interface=inter;
            }
            else if(moudle->index==39)
            {
                bind_tag* bind=new bind_tag();
                bind->input_flag=getstr(str).toInt();
                bind->input_tag=getstr(str);
                bind->output_flag=getstr(str).toInt();
                bind->output_tag=getstr(str);
                moudle->tag_bind=bind;
            }
            this->simulation_group->group.push_back(moudle);
        }
        for(int i=0;i<this->simulation_group->group.size();i++)
        {
            Simulation_Moudle* moudle=this->simulation_group->group[i];
            for(int j=0;j<moudle->output.size();j++)
            {
                for(int m=0;m<moudle->output[j]->next.size();m++)
                    moudle->output[j]->next[m].moudle=this->simulation_group[moudle->output[j]->next[m].id];

            }
            if(moudle->index==39)
            {
                if(moudle->tag_bind->input_flag==true&&moudle->tag_bind->input_tag!="-1")
                {
                    this->remove_tag(moudle->tag_bind->input_tag);
                    this->sys_flag->input_bind.insert(moudle->tag_bind->input_tag,moudle);
                }
                if(moudle->tag_bind->output_flag==true&&moudle->tag_bind->output_tag!="-1")
                {
                    this->remove_tag(moudle->tag_bind->output_tag);
                    this->sys_flag->output_bind.insert(moudle->tag_bind->output_tag,moudle);
                }
            }
        }

    }
}
*/
QString algorithm_file::getstr(QString str)
{
    static int index=1;
    QString stri="";
    for(int i=index;i<str.size();i++)
    {
        if(str[i]=='!')
        {
            index=i+1;
            return stri;
        }
        else
            stri+=str[i];
    }
    return stri;
}
QStringList algorithm_file::url_to_name(QString fileName)//地址转文件名
{
    int index1=0,index2=0;
    QString name="";//文件名
    QString forma="";//文件格式
    QString pre_forma="";
    QStringList str;
    for(int i=fileName.size()-1;i>=0;i--)
    {
        if(fileName[i]=='.')
        {
            index1=i-1;
            break;
        }
    }
    for(int i=index1+2;i<fileName.size();i++)
        forma+=fileName[i];

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
    for(int i=0;i<index2;i++)
        pre_forma+=fileName[i];
    str.push_back(name);
    str.push_back(forma);
    str.push_back(pre_forma);
    return str;
}
/*
void algorithm_file::init()
{
    connect(this->rece_clock, SIGNAL(timeout()), this, SLOT(rece_Timeout()));
    connect(this->send_clock, SIGNAL(timeout()), this, SLOT(send_Timeout()));
}
void algorithm_file::run_()
{
    algorithm* alg=new algorithm();
    alg->init(this->simulation_group);
    if(alg->exec())
    {
        start_run=true;
    }
}

void algorithm_file::clear_finish_flag(int way)
{
    //数据传输完成标志位清除
    if(way==0)
    {
        for(int i=0;i<this->sys_flag->finish_socket->input.size();i++)
            this->sys_flag->finish_socket->input[i]=false;
        this->sys_flag->finish_socket->input_size=this->sys_flag->finish_socket->input.size();
    }
    if(way==1)
    {
        for(int i=0;i<this->sys_flag->finish_socket->output.size();i++)
            this->sys_flag->finish_socket->output[i]=false;
        this->sys_flag->finish_socket->output_size=this->sys_flag->finish_socket->output.size();
    }
}

void algorithm_file::rece_Timeout()
{
    for(int i=0;i<this->sys_flag->finish_socket->input.size();i++)
        if(this->sys_flag->finish_socket->input[i]==false)
        {
            Simulation_Moudle* moudle=finished_flag(i,0);
            if(moudle->index==39&&this->sys_flag->success_flag==true)
            {
                this->data_process(moudle->tag_bind->input_tag,"0");
            }
        }
    clear_finish_flag(0);
    this->rece_clock->stop();
}

Simulation_Moudle* algorithm_file::finished_flag(int id,int way)
{
    for(int i=0;i<this->simulation_group->group.size();i++)
    {
        Simulation_Moudle* moudle=this->simulation_group->group[i];
        if(moudle->index==39)
        {
            if(way==0&&moudle->tag_bind->input_flag&&moudle->socket_id_input==id)
                return moudle;
            else if(way==1&&moudle->tag_bind->output_flag&&moudle->socket_id_output==id)
                return moudle;
        }
    }
    return nullptr;
}

void algorithm_file::data_process(QString key,QString value)
{
    if(this->sys_flag->input_bind.contains(key)==false)
        return;
    Simulation_Moudle* moudle=*this->sys_flag->input_bind.find(key);
    this->sys_flag->finish_socket->input[moudle->socket_id_input]=true;
    if(moudle->tag_bind->output_flag==false)//虚拟仿真
    {
        for(int i=0;i<moudle->output_number.size();i++)
            moudle->output_number[i]=value.toDouble();
        this->run_simulation(moudle);
    }
    else//输出端口实物连接
    {
        //qDebug()<<1;
        this->sys_flag->finish_socket->output[moudle->socket_id_output]=true;
        this->sys_flag->output_buf+=(moudle->tag_bind->output_tag+" "+value);
        //qDebug()<<key+" "+value;
        //this->sys_flag->output_bind_count--;
        int i=0;
        for(i=0;i<this->sys_flag->finish_socket->output.size();i++)
        {
            if(this->sys_flag->finish_socket->output[i]==false)
                break;
        }
        if(i==this->sys_flag->finish_socket->output.size())//所有输出至外部接口的数据打包完成 开始发送
        {
            this->sys_flag->output_bind_count=this->sys_flag->output_bind.size();
            this->sys_flag->socket_main->write(this->sys_flag->output_buf.toLatin1(),this->sys_flag->output_buf.size());
            this->sys_flag->output_buf="";
            this->send_clock->stop();
            clear_finish_flag(1);
        }
    }
}

void algorithm_file::send_data_torun(int index,double value)
{
    Simulation_Moudle* moudle=this->simulation_group->group[index];
    //this->sys_flag->finish_socket->input[moudle->socket_id_input]=true;
    if(moudle->bind_interface->output_flag==true)//与实物连接
    {
        if(moudle->bind_interface->output_success==true)//是否与服务器连接成功
        {
            QString str=QString::number(value);
            moudle->bind_interface->output_socket->write(str.toLatin1(),str.length());
        }
        else
        {
            QString str=QString::number(moudle->bind_interface->output_ip[0])+"."+QString::number(moudle->bind_interface->output_ip[1])+"."+QString::number(moudle->bind_interface->output_ip[2])+"."+QString::number(moudle->bind_interface->output_ip[3]);
            QHostAddress ip(str);
            moudle->bind_interface->output_socket->connectToHost(ip,quint16(moudle->bind_interface->output_port));
            return;
        }
    }
    else
    {
        for(int i=0;i<moudle->output_number.size();i++)
            moudle->output_number[i]=value;
        //qDebug()<<value;
        this->run_simulation(moudle);
    }
}

void algorithm_file::send_Timeout()
{
    bool flag=false;
    for(int i=0;i<this->sys_flag->finish_socket->output.size();i++)
        if(this->sys_flag->finish_socket->output[i]==false)
        {
            Simulation_Moudle* moudle=finished_flag(i,1);
            if(flag==false)
                flag=true;
        }
    if(flag==true)//标签绑定模块输出部分数据没有完全形成
    {
        this->sys_flag->socket_main->write(this->sys_flag->output_buf.toLatin1(),this->sys_flag->output_buf.size());
        this->sys_flag->output_buf="";
    }

    clear_finish_flag(1);
    this->send_clock->stop();
}

int algorithm_file::find_moudle_with_socket(QTcpSocket* socket,int flag)
{
    int i=0;
    for(i=0;i<this->simulation_group->group.size();i++)
        if(this->simulation_group->group[i]->index==38)
        {
            if(this->simulation_group->group[i]->bind_interface->input_socket==socket)
            {
                if(flag==1)
                    this->simulation_group->group[i]->bind_interface->input_success=true;
                else
                    this->simulation_group->group[i]->bind_interface->input_success=false;
                break;
            }
            if(this->simulation_group->group[i]->bind_interface->output_socket==socket)
            {
                if(flag==1)
                    this->simulation_group->group[i]->bind_interface->output_success=true;
                else
                    this->simulation_group->group[i]->bind_interface->output_success=false;
                break;
            }
        }
    if(i==this->simulation_group->group.size())
        return -1;
    else
        return i;
}

void algorithm_file::socket_connect()
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    int index=find_moudle_with_socket(socket,1);
    if(index!=-1)
    {
    }
    else
    {
        this->sys_flag->success_flag=true;
    }
}

void algorithm_file::socket_disconnect()
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    int index=find_moudle_with_socket(socket,0);
    if(index!=-1)
    {}
    else
    {
        this->sys_flag->success_flag=false;
    }
    if(this->start_run==true)//当前处于运行态，需要重新建立连接
    {
        if(index!=-1)
        {
            reconnect(index);
        }
        else
        {
            socket->connectToHost(this->sys_flag->ip_main,this->sys_flag->port_main);
        }
    }
}
void algorithm_file::reconnect(int index)
{
    Simulation_Moudle* moudle=this->simulation_group->group[index];
    if(moudle->bind_interface->input_flag==true&&moudle->bind_interface->input_success==false)
    {
        QHostAddress ip(QString::number(moudle->bind_interface->input_ip[0])+"."+QString::number(moudle->bind_interface->input_ip[1])+"."+QString::number(moudle->bind_interface->input_ip[2])+"."+QString::number(moudle->bind_interface->input_ip[3]));
        moudle->bind_interface->input_socket->connectToHost(ip,quint16(moudle->bind_interface->input_port));
    }
    if(moudle->bind_interface->output_flag==true&&moudle->bind_interface->output_success==false)
    {
        QHostAddress ip(QString::number(moudle->bind_interface->output_ip[0])+"."+QString::number(moudle->bind_interface->output_ip[1])+"."+QString::number(moudle->bind_interface->output_ip[2])+"."+QString::number(moudle->bind_interface->output_ip[3]));
        moudle->bind_interface->output_socket->connectToHost(ip,quint16(moudle->bind_interface->output_port));
    }
}
void algorithm_file::socket_receive()
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    if(this->start_run==false)
    {
        socket->readLine();
        return;
    }

    int index=find_moudle_with_socket(socket,1);
    if(index==-1)//main socket数据接收
    {
        if(this->rece_clock->isActive()==false)
        {
            this->rece_clock->start(10);
            this->send_clock->start(50);
        }
        QByteArray temp;
        temp=socket->readLine();
        QString str(temp);
        QString str_key="";
        QString str_value="";
        int change_flag=false;
        for(int n=0;n<str.size();n++)
        {
            if(str[n]==' ')
            {
                //send_data_torun(index,str_key.toDouble());
                //this->run->run_simulation(moudle);
                if(change_flag==false)
                    change_flag=true;
                else
                {
                    change_flag=false;
                    //qDebug()<<str_key<<str_value;
                    data_process(str_key,str_value);
                    str_key="";
                    str_value="";
                }
            }
            else
            {
                if(change_flag==false)
                    str_key+=str[n];
                else
                    str_value+=str[n];
            }
        }
        data_process(str_key,str_value);
        //qDebug()<<str;
        return;
    }
    while(socket->bytesAvailable())
    {
        QByteArray temp;
        temp=socket->readLine();
        QString str(temp);
        QString str_child="";
        for(int n=0;n<str.size();n++)
        {
            if(str[n]==' ')
            {
                //qDebug()<<str_child.toDouble();
                this->simulation_group->group[index]->bind_interface->receive_data.push_back(str_child.toDouble());
                send_data_torun(index,str_child.toDouble());
                str_child="";
            }
            else
            {
                str_child+=str[n];
            }
        }
        if(str_child!="")
        {
            this->simulation_group->group[index]->bind_interface->receive_data.push_back(str_child.toDouble());
            send_data_torun(index,str_child.toDouble());
        }
        //qDebug()<<str_child.toDouble();

    }
}
void algorithm_file::run_simulation(Simulation_Moudle* moudle)
{
        for(int j=0;j<moudle->output.size();j++)
        {
            moudle_param* param=moudle->output[j];
            for(int m=0;m<param->next.size();m++)
            {
                if(check_input(param->next[m].moudle,param->next[m].index,moudle->output_number[j]))
                {
                    run_simulation(param->next[m].moudle);
                }
            }
        }
}
bool algorithm_file::check_input(Simulation_Moudle* moudle,int index,double value)
{
    bool flag=true;
    moudle->input_flag[index]=true;
    moudle->input_number[index]=value;
    for(int i=0;i<moudle->input_flag.size();i++)
    {
        if(moudle->input_flag[i]!=true&&moudle->input_loop[i]!=true)
        {
            flag=false;
            break;
        }
    }
    if(flag)
    {
        for(int i=0;i<moudle->input_flag.size();i++)
            moudle->input_flag[i]=false;
        calculation(moudle);
        return true;
    }
    return false;

}
void algorithm_file::calculation(Simulation_Moudle* moudle)
{
    double value=0;
    for(int i=0;i<moudle->input_number.size();i++)
    {
        value+=moudle->input_number[i];
    }
    if(moudle->output_number.size()!=0)
    {
        if(moudle->index==12)//惯性
        {
            double k1=0,k2=0,k3=0,k4=0;
            for(int i=0;i<moudle->output_number.size();i++)
            {
                //改进欧拉算法
                double temp;
                temp=moudle->output_number[0]/moudle->param[0];
                moudle->output_number[0]=temp+simu_step*(moudle->param[2]-temp)/moudle->param[1];
                moudle->output_number[0]=temp+simu_step/2*(moudle->param[2]-temp+value-moudle->output_number[0])/moudle->param[1];
                moudle->param[2]=value;//使用前需要清零
            }
            moudle->output_number[0]=moudle->output_number[0]*moudle->param[0];
        }
        else if(moudle->index==13)//n阶惯性
        {
            for(int i=0;i<moudle->output_number.size();i++)
            {
                for(int j=0;j<int(moudle->param[2]);j++)
                {
                    //改进欧拉算法
                    moudle->output_number[0]=moudle->temp[j]+simu_step*(moudle->param_temp[j]-moudle->temp[j])/moudle->param[1];
                    moudle->output_number[0]=moudle->temp[j]+simu_step/2*(moudle->param_temp[j]-moudle->temp[j]+value-moudle->output_number[0])/moudle->param[1];
                    moudle->param_temp[j]=value;//使用前需要清零
                    moudle->temp[j]=moudle->output_number[0];
                    value=moudle->output_number[0];
                }
                moudle->output_number[0]=moudle->output_number[0]*moudle->param[0];
            }
        }
        else if(moudle->index==8)//常数
        {
            moudle->output_number[0]=moudle->param[0]*value;
        }
        else if(moudle->index==9)//延时
        {
            moudle->process_value.push_back(value);
            if(moudle->process_value.size()>=moudle->param[0]/simu_step)
            {
                moudle->output_number[0]=moudle->process_value[0];
                moudle->process_value.removeAt(0);
            }
            else
            {
                moudle->output_number[0]=0;
            }
        }
        else if(moudle->index==10)//积分
        {
            moudle->output_number[0]+=value*moudle->param[0]*simu_step;
        }
        else if(moudle->index==11)//微分
        {
            double temp=value;
            moudle->output_number[0]=(value-moudle->param[0])/simu_step;
            moudle->param[0]=temp;
        }
        else if(moudle->index==19)//倒数
        {
            if(int(value)!=0)
                moudle->output_number[0]=1/value;
            else
                moudle->output_number[0]=0;
        }
        else if(moudle->index==20)//正三角
        {
            if(int(moudle->param[0])==0)
            {
                moudle->output_number[0]=sin(value);
            }
            else if(int(moudle->param[0])==1)
                moudle->output_number[0]=cos(value);
            else if(int(moudle->param[0])==2)
                moudle->output_number[0]=tan(value);
        }
        else if(moudle->index==21)//反三角
        {
            if(int(moudle->param[0])==0)
                moudle->output_number[0]=asin(value);
            else if(int(moudle->param[0])==1)
                moudle->output_number[0]=acos(value);
            else if(int(moudle->param[0])==2)
                moudle->output_number[0]=atan(value);
        }
        else if(moudle->index==22)//绝对值
        {
            moudle->output_number[0]=abs(value);
        }
        else if(moudle->index==23)//绝符号
        {
            moudle->output_number[0]=value>0?1:(value==0.0?0:-1);
        }
        else if(moudle->index==24)//自然对数 e
        {
            if(value>0)
                moudle->output_number[0]=log(value);
            else
                moudle->output_number[0]=value;
        }
        else if(moudle->index==25)//常用对数 10
        {
            if(value>0)
                moudle->output_number[0]=log10(value);
            else
                moudle->output_number[0]=value;
        }
        else if(moudle->index==26)//指数e
        {
            moudle->output_number[0]=exp(value);
        }
        else if(moudle->index==27)//幂函数
        {
            moudle->output_number[0]=pow(value,int(moudle->param[0]));
        }
        else if(moudle->index==28)//开方
        {
            if(value>=0)
                moudle->output_number[0]=sqrt(value);
            else
                moudle->output_number[0]=value;
        }
        else if(moudle->index==29)//加法器
        {
            moudle->output_number[0]=value;
        }
        else if(moudle->index==30)//乘法器
        {
            if(int(moudle->param[0])==0)
                moudle->output_number[0]=moudle->input_number[0]*moudle->input_number[1];
            else if(int(moudle->param[0])==1&&int(moudle->input_number[1])!=0)
            {
                moudle->output_number[0]=moudle->input_number[0]/moudle->input_number[1];
            }

        }
        else if(moudle->index==31)//比例偏置 kx+b
        {
            moudle->output_number[0]=moudle->param[0]*value+moudle->param[1];
        }
        else if(moudle->index==32)//逻辑运算> <
        {
            if(int(moudle->param[0])==0)
                moudle->output_number[0]=(moudle->input_number[0]>moudle->input_number[1]);
            else if(int(moudle->param[0])==1)
                moudle->output_number[0]=(moudle->input_number[0]<moudle->input_number[1]);
            else if(int(moudle->param[0])==2)
                moudle->output_number[0]=(int(moudle->input_number[0])==int(moudle->input_number[1]));
            else if(int(moudle->param[0])==3)
                moudle->output_number[0]=(int(moudle->input_number[0])&&int(moudle->input_number[1]));
            else if(int(moudle->param[0])==4)
                moudle->output_number[0]=(int(moudle->input_number[0])||int(moudle->input_number[1]));
            else if(int(moudle->param[0])==5)
            {
                if(int(moudle->input_number[0])!=0)
                    moudle->output_number[0]=0;
                else
                    moudle->output_number[0]=1;
            }
        }
        else if(moudle->index==33)//逻辑& | ~
        {
            if(int(moudle->param[0])==0)
                moudle->output_number[0]=(int(moudle->input_number[0])&int(moudle->input_number[1]));
            else if(int(moudle->param[0])==1)
                moudle->output_number[0]=(int(moudle->input_number[0])|int(moudle->input_number[1]));
            else if(int(moudle->param[0])==2)
                moudle->output_number[0]=(~int(moudle->input_number[0]));
        }
        else if(moudle->index==34)//取最值
        {
            if(int(moudle->param[1])==0) //最大值
            {
                double max=moudle->input_number[0];
                for(int i=1;i<moudle->input_number.size();i++)
                {
                    if(max<moudle->input_number[i])
                        max=moudle->input_number[i];
                }
                moudle->output_number[0]=max;

            }
            else if(int(moudle->param[1])==1) //MIN
            {
                double min=moudle->input_number[0];
                for(int i=1;i<moudle->input_number.size();i++)
                {
                    if(min>moudle->input_number[i])
                        min=moudle->input_number[i];
                }
                moudle->output_number[0]=min;
            }
        }
        else if(moudle->index==35)//出多选一
        {
            if(int(moudle->input_number[1])<moudle->output_size)
            {
                for(int i=0;i<moudle->output_size;i++)
                {
                    if(i==int(moudle->input_number[1]))
                        moudle->output_number[i]=moudle->input_number[0];
                    else
                        moudle->output_number[i]=0;
                }
            }
            else
            {
                for(int i=0;i<moudle->output_size;i++)
                {
                    moudle->output_number[i]=0;
                }

            }
        }
        else if(moudle->index==36)//入多选一
        {
            if(int(moudle->input_number[moudle->input_size-1])<moudle->input_size-1)
                moudle->output_number[0]=moudle->input_number[int(moudle->input_number[moudle->input_size-1])];
            else
                moudle->output_number[0]=0;
        }
        else if(moudle->index==38)//接口模块专属
        {
            for(int m=0;m<moudle->output_number.size();m++)
                moudle->output_number[m]=value;
        }
        else if(moudle->index==39)//tag_bind模块专属
        {
            for(int m=0;m<moudle->output_number.size();m++)
                moudle->output_number[m]=value;
        }

    }
    else
    {
        if(moudle->index==38)//接口模块专属
        {
            if(moudle->bind_interface->output_success==true)//是否与服务器连接成功
            {
                QString str=QString::number(value);
                moudle->bind_interface->output_socket->write(str.toLatin1(),str.length());
            }
            else
            {
                QString str=QString::number(moudle->bind_interface->output_ip[0])+"."+QString::number(moudle->bind_interface->output_ip[1])+"."+QString::number(moudle->bind_interface->output_ip[2])+"."+QString::number(moudle->bind_interface->output_ip[3]);
                QHostAddress ip(str);
                moudle->bind_interface->output_socket->connectToHost(ip,quint16(moudle->bind_interface->output_port));
                return;
            }
        }
        else if(moudle->index==39)//tag_bind模块专属
        {

            if(this->sys_flag->success_flag==false)//断开连接
            {
                return;
            }
            this->sys_flag->finish_socket->output[moudle->socket_id_output]=true;
            this->sys_flag->output_buf+=(moudle->tag_bind->output_tag+" "+QString::number(value));
            //this->window_parent->sys_flag->output_bind_count--;
            int m=0;
            for(m=0;m<this->sys_flag->finish_socket->output.size();m++)
            {
                if(this->sys_flag->finish_socket->output[m]==false)
                    break;
            }
            if(m==this->sys_flag->finish_socket->output.size())//所有输出至外部接口的数据打包完成 开始发送
            {
                this->sys_flag->output_bind_count=this->sys_flag->output_bind.size();
                this->sys_flag->socket_main->write(this->sys_flag->output_buf.toLatin1(),this->sys_flag->output_buf.size());
                this->sys_flag->output_buf="";
                this->send_clock->stop();
                this->clear_finish_flag(1);
            }
        }
        else if(moudle->index==37)//图表
            moudle->graph_value.push_back(value);
    }
}
*/
