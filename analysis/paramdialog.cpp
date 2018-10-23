#include "paramdialog.h"
#include <qtextcodec.h>
paramdialog::paramdialog(QWidget *parent,Simulation_Moudle* moudle,system_flag* flag) : QDialog(parent)
{

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QHBoxLayout *buttonLayout;
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    nameText = new QLineEdit; 
    nameLabel = new QLabel("标签");
    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
    int count=this->param.size();
    for(int i=0;i<count;i++)
        this->param.removeAt(0);

    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
 /*   gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    gLayout->addWidget(addressLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
    gLayout->addWidget(addressText, 1, 1, Qt::AlignLeft);
    */

    if(moudle!=nullptr)
    {
        nameText->setText(moudle->name);
        gLayout->addWidget(nameLabel,0,0);
        gLayout->addWidget(nameText,0,1);
        if(moudle->index==0)
        {
            addressLabel = new QLabel("斜率");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);
            setWindowTitle(tr("Linear signal"));

            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
        }
        else if(moudle->index==1)
        {
            addressLabel = new QLabel("阶跃高度");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);
            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

            setWindowTitle(tr("阶跃信号"));

        }
        else if(moudle->index==2)
        {
            addressLabel = new QLabel("Amplitude");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("frequency");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[1]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
            setWindowTitle(tr("正弦信号"));

        }
        else if(moudle->index==3)
        {
            addressLabel = new QLabel("周期s");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("幅度");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[1]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
            setWindowTitle(tr("方波信号"));

        }
        else if(moudle->index==4)
        {
            addressLabel = new QLabel("周期s");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("波峰");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[1]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            addressLabel = new QLabel("波谷");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[2]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,3,0);
            gLayout->addWidget(addressText,3,1);

            gLayout->addLayout(buttonLayout, 5, 1, Qt::AlignRight);
            setWindowTitle(tr("Triangle wave"));
        }
        else if(moudle->index==5)
        {
            addressLabel = new QLabel("折点时间序列");
            addressText = new QLineEdit;
            addressText->setText(moudle->time);
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("折点输出序列");
            addressText = new QLineEdit;
            addressText->setText(moudle->value);
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
            setWindowTitle(tr("分段折线信号"));

        }
        else if(moudle->index==7)
        {
            addressLabel = new QLabel("信号下限");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("信号上限");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[1]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
            setWindowTitle(tr("随机信号"));

        }
        else if(moudle->index==8)
        {
            addressLabel = new QLabel("常数");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
            setWindowTitle(tr("constant"));

        }
        else if(moudle->index==9)
        {
            addressLabel = new QLabel("时间(s)");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
            setWindowTitle(tr("延时环节"));

        }
        else if(moudle->index==10)
        {
            addressLabel = new QLabel("系数k");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
            setWindowTitle(tr("积分环节"));

        }
        else if(moudle->index==11)
        {
            gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);
            setWindowTitle(tr("微分环节"));
        }
        else if(moudle->index==12)
        {
            addressLabel = new QLabel("比例系数k");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("时间常数T");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[1]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
            setWindowTitle(tr("First order inertia"));

        }
        else if(moudle->index==13)
        {
            addressLabel = new QLabel("比例系数k");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("时间常数T");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[1]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            addressLabel = new QLabel("阶数n");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[2]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,3,0);
            gLayout->addWidget(addressText,3,1);

            gLayout->addLayout(buttonLayout, 5, 1, Qt::AlignRight);
            setWindowTitle(tr("inertia"));

        }
        else if(moudle->index==14)
        {
            QString display="";
            addressLabel = new QLabel("分母序列");
            addressText = new QLineEdit;
            for(int i=0;i<moudle->time_sequence.size();i++)
                display+=QString::number(moudle->time_sequence[i])+",";
            addressText->setText(display);
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("分子序列");
            addressText = new QLineEdit;
            display="";
            for(int i=0;i<moudle->value_sequence.size();i++)
                display+=QString::number(moudle->value_sequence[i])+",";
            addressText->setText(display);
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
            setWindowTitle(tr("函数"));
        }
        else if(moudle->index==15)
        {
            QString display="";
            addressLabel = new QLabel("分母各阶系数");
            addressText = new QLineEdit;
            for(int i=0;i<moudle->time_sequence.size();i++)
                display+=QString::number(moudle->time_sequence[i])+",";
            addressText->setText(display);
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("分子各阶系数");
            addressText = new QLineEdit;
            display="";
            for(int i=0;i<moudle->value_sequence.size();i++)
                display+=QString::number(moudle->value_sequence[i])+",";
            addressText->setText(display);
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            /*
            addressLabel = new QLabel("常数k");
            addressText=new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,3,0);
            gLayout->addWidget(addressText,3,1);
            */
            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
            setWindowTitle(tr("函数"));
        }
        else if(moudle->index==20)
        {
            QRadioButton *radio1 = new QRadioButton("sin");
            QRadioButton *radio2 = new QRadioButton("cos");
            QRadioButton *radio3 = new QRadioButton("tan");
            group=new QButtonGroup(this);
            group->addButton(radio1);
            group->addButton(radio2);
            group->addButton(radio3);
            gLayout->addWidget(radio1, 1, 0);
            gLayout->addWidget(radio2, 1, 1,Qt::AlignCenter);
            gLayout->addWidget(radio3, 1, 2);
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio3, &QAbstractButton::clicked, this, &paramdialog::button);

            this->index=int(moudle->param[0]);
            init_selected(int(moudle->param[0]));
            setWindowTitle(tr("triangle"));
            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
        }
        else if(moudle->index==21)
        {

            QRadioButton *radio1 = new QRadioButton("asin");
            QRadioButton *radio2 = new QRadioButton("acos");
            QRadioButton *radio3 = new QRadioButton("atan");
            group=new QButtonGroup(this);
            group->addButton(radio1);
            group->addButton(radio2);
            group->addButton(radio3);
            gLayout->addWidget(radio1, 1, 0);
            gLayout->addWidget(radio2, 1, 1,Qt::AlignCenter);
            gLayout->addWidget(radio3, 1, 2);
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio3, &QAbstractButton::clicked, this, &paramdialog::button);

            this->index=int(moudle->param[0]);
            init_selected(int(moudle->param[0]));

            setWindowTitle(tr("Anti-triangle"));
            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
        }
        else if(moudle->index==27)
        {
            addressLabel = new QLabel("p");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
            setWindowTitle(tr("Power function"));

        }
        else if(moudle->index==29)
        {
            addressLabel = new QLabel("输入数量");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
            setWindowTitle(tr("ADD"));

        }
        else if(moudle->index==30)
        {
            QRadioButton *radio1 = new QRadioButton("Mul");
            QRadioButton *radio2 = new QRadioButton("Div");
            group=new QButtonGroup(this);
            group->addButton(radio1);
            group->addButton(radio2);
            gLayout->addWidget(radio1, 1, 0);
            gLayout->addWidget(radio2, 1, 1,Qt::AlignRight);
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::button);

            this->index=int(moudle->param[0]);
            init_selected(int(moudle->param[0]));
            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
            setWindowTitle(tr("乘法"));

        }
        else if(moudle->index==31)
        {
            addressLabel = new QLabel("比例系数k");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            addressLabel = new QLabel("偏置常数b");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[1]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,2,0);
            gLayout->addWidget(addressText,2,1);

            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
            setWindowTitle(tr("比例偏置"));

        }
        else if(moudle->index==32)
        {

            QRadioButton *radio1 = new QRadioButton(">");
            QRadioButton *radio2 = new QRadioButton("<");
            QRadioButton *radio3 = new QRadioButton("=");
            QRadioButton *radio4 = new QRadioButton("AND");
            QRadioButton *radio5 = new QRadioButton("||");
            QRadioButton *radio6 = new QRadioButton("!");
            group=new QButtonGroup(this);
            group->addButton(radio1);
            group->addButton(radio2);
            group->addButton(radio3);
            group->addButton(radio4);
            group->addButton(radio5);
            group->addButton(radio6);
            gLayout->addWidget(radio1, 1, 0);
            gLayout->addWidget(radio2, 1, 1,Qt::AlignCenter);
            gLayout->addWidget(radio3, 1, 2);
            gLayout->addWidget(radio4, 2, 0);
            gLayout->addWidget(radio5, 2, 1,Qt::AlignCenter);
            gLayout->addWidget(radio6, 2, 2);
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio3, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio4, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio5, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio6, &QAbstractButton::clicked, this, &paramdialog::button);

            this->index=int(moudle->param[0]);
            init_selected(int(moudle->param[0]));

            setWindowTitle(tr("逻辑运算"));
            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
        }
        else if(moudle->index==33)
        {

            QRadioButton *radio1 = new QRadioButton("AND");
            QRadioButton *radio2 = new QRadioButton("|");
            QRadioButton *radio3 = new QRadioButton("~");
            group=new QButtonGroup(this);
            group->addButton(radio1);
            group->addButton(radio2);
            group->addButton(radio3);
            gLayout->addWidget(radio1, 1, 0);
            gLayout->addWidget(radio2, 1, 1,Qt::AlignCenter);
            gLayout->addWidget(radio3, 1, 2);
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio3, &QAbstractButton::clicked, this, &paramdialog::button);

            this->index=int(moudle->param[0]);
            init_selected(int(moudle->param[0]));

            setWindowTitle(tr("单目运算"));
            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
        }
        else if(moudle->index==34)
        {
            addressLabel = new QLabel("输入数量");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            QRadioButton *radio1 = new QRadioButton("MAX");
            QRadioButton *radio2 = new QRadioButton("MIN");
            group=new QButtonGroup(this);
            group->addButton(radio1);
            group->addButton(radio2);
            gLayout->addWidget(radio1, 2, 0);
            gLayout->addWidget(radio2, 2, 1,Qt::AlignRight);
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::button);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::button);

            this->index=int(moudle->param[1]);
            init_selected(int(moudle->param[1]));


            gLayout->addLayout(buttonLayout, 4, 1, Qt::AlignRight);
            setWindowTitle(tr("Maximum value"));

        }
        else if(moudle->index==35)
        {
            addressLabel = new QLabel("输出数量");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
            setWindowTitle(tr("单输入多输出"));

        }
        else if(moudle->index==36)
        {
            addressLabel = new QLabel("输入数量");
            addressText = new QLineEdit;
            addressText->setText(QString::number(moudle->param[0]));
            param.push_back(addressText);
            gLayout->addWidget(addressLabel,1,0);
            gLayout->addWidget(addressText,1,1);

            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
            setWindowTitle(tr("多输入单输出"));

        }
        else if(moudle->index==38)//接口绑定模块
        {
            this->interface=new interface_bin();
            this->moudle=moudle;
            QLabel* input=new QLabel("input");
            QLabel* output=new QLabel("output");
            QRadioButton *radio1 = new QRadioButton("real");
            QRadioButton *radio2 = new QRadioButton("simulation");
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::interface_check);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::interface_check);
            this->interface->input=new QButtonGroup(this);
            this->interface->input->addButton(radio1);
            this->interface->input->addButton(radio2);
            gLayout->addWidget(input,1,0);
            gLayout->addWidget(radio1,2,0);
            gLayout->addWidget(radio2,2,1);


            gLayout->addWidget(new QLabel("address:"),3,0);
            QHBoxLayout* hbox=new QHBoxLayout();
            this->interface->address_input.push_back(new QLineEdit(QString::number(moudle->bind_interface->input_ip[0])));
            this->interface->address_input.push_back(new QLineEdit(QString::number(moudle->bind_interface->input_ip[1])));
            this->interface->address_input.push_back(new QLineEdit(QString::number(moudle->bind_interface->input_ip[2])));
            this->interface->address_input.push_back(new QLineEdit(QString::number(moudle->bind_interface->input_ip[3])));
            hbox->addWidget(this->interface->address_input[0]);
            hbox->addWidget(new QLabel("."));
            hbox->addWidget(this->interface->address_input[1]);
            hbox->addWidget(new QLabel("."));
            hbox->addWidget(this->interface->address_input[2]);
            hbox->addWidget(new QLabel("."));
            hbox->addWidget(this->interface->address_input[3]);
            gLayout->addLayout(hbox,3,1);
            gLayout->addWidget(new QLabel("port:"),4,0);
            this->interface->port_input=new QLineEdit(QString::number(moudle->bind_interface->input_port));
            gLayout->addWidget(this->interface->port_input,4,1);
            if(moudle->bind_interface->input_success==true)
                this->interface->connect_input=new QPushButton("disconnect");
            else
                this->interface->connect_input=new QPushButton("connect");
            connect(this->interface->connect_input,&QAbstractButton::pressed,this,&paramdialog::input_connect);
            gLayout->addWidget(this->interface->connect_input,4,2,Qt::AlignHCenter);
            if(moudle->bind_interface->input_flag==true)
            {
                this->interface->input_flag=true;
                radio1->setChecked(true);
            }
            else
            {
                this->interface->input_flag=false;
                radio2->setChecked(true);
                emit radio2->clicked();
                if(check_moudle(moudle,0))
                    radio1->setEnabled(false);
            }

            radio1 = new QRadioButton("real");
            radio2 = new QRadioButton("simulation");
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::interface_check);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::interface_check);
            this->interface->output=new QButtonGroup(this);
            this->interface->output->addButton(radio1);
            this->interface->output->addButton(radio2);
            gLayout->addWidget(output,6,0);
            gLayout->addWidget(radio1,7,0);
            gLayout->addWidget(radio2,7,1);

            gLayout->addWidget(new QLabel("address:"),8,0);
            hbox=new QHBoxLayout();
            this->interface->address_output.push_back(new QLineEdit(QString::number(moudle->bind_interface->output_ip[0])));
            this->interface->address_output.push_back(new QLineEdit(QString::number(moudle->bind_interface->output_ip[1])));
            this->interface->address_output.push_back(new QLineEdit(QString::number(moudle->bind_interface->output_ip[2])));
            this->interface->address_output.push_back(new QLineEdit(QString::number(moudle->bind_interface->output_ip[3])));
            hbox->addWidget(this->interface->address_output[0]);
            hbox->addWidget(new QLabel("."));
            hbox->addWidget(this->interface->address_output[1]);
            hbox->addWidget(new QLabel("."));
            hbox->addWidget(this->interface->address_output[2]);
            hbox->addWidget(new QLabel("."));
            hbox->addWidget(this->interface->address_output[3]);
            gLayout->addLayout(hbox,8,1);
            gLayout->addWidget(new QLabel("port:"),9,0);
            this->interface->port_output=new QLineEdit(QString::number(moudle->bind_interface->output_port));
            gLayout->addWidget(this->interface->port_output,9,1);
            if(moudle->bind_interface->output_success==true)
                this->interface->connect_output=new QPushButton("disconnect");
            else
                this->interface->connect_output=new QPushButton("connect");
            connect(this->interface->connect_output,&QAbstractButton::pressed,this,&paramdialog::output_connect);
            gLayout->addWidget(this->interface->connect_output,9,2,Qt::AlignHCenter);
            if(moudle->bind_interface->output_flag==true)
            {
                this->interface->output_flag=true;
                radio1->setChecked(true);
            }
            else
            {
                this->interface->output_flag=false;
                radio2->setChecked(true);
                emit radio2->clicked();
                if(check_moudle(moudle,1))
                    radio1->setEnabled(false);
            }

            gLayout->addWidget(okButton, 12, 1, Qt::AlignCenter);
            setWindowTitle(tr("connect interface"));
            this->resize(100,300);
        }
        else if(moudle->index==39)//bind_tag
        {
            this->flag=flag;
            this->bind=new tag_bind();          
            this->moudle=moudle;
            QLabel* input=new QLabel("input");
            QLabel* output=new QLabel("output");
            QRadioButton *radio1 = new QRadioButton("real");
            QRadioButton *radio2 = new QRadioButton("simulation");
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::combbox_radio_change);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::combbox_radio_change);
            this->bind->input=new QButtonGroup(this);
            this->bind->input->addButton(radio1);
            this->bind->input->addButton(radio2);
            gLayout->addWidget(input,1,0);
            gLayout->addWidget(radio1,2,0);
            gLayout->addWidget(radio2,2,1);
            this->bind->input_box=new QComboBox();
            this->bind->input_box->addItems(flag->tag_group_temp);
            connect(this->bind->input_box,&QComboBox::currentTextChanged,this,&paramdialog::combbox_change);
            gLayout->addWidget(this->bind->input_box,3,0,1,2);
            stop_flag=true;
            this->bind->input_box->setCurrentIndex(flag->tag_group_temp.indexOf(moudle->tag_bind->input_tag));
            stop_flag=false;
            this->bind->input_tag=moudle->tag_bind->input_tag;
            if(moudle->tag_bind->input_flag==true)
            {
                this->bind->input_flag=true;
                radio1->setChecked(true);
            }
            else
            {
                this->bind->input_flag=false;
                radio2->setChecked(true);
                emit radio2->clicked();
                if(check_moudle(moudle,0))
                    radio1->setEnabled(false);
            }
            radio1 = new QRadioButton("real");
            radio2 = new QRadioButton("simulation");
            connect(radio1, &QAbstractButton::clicked, this, &paramdialog::combbox_radio_change);
            connect(radio2, &QAbstractButton::clicked, this, &paramdialog::combbox_radio_change);
            this->bind->output=new QButtonGroup(this);
            this->bind->output->addButton(radio1);
            this->bind->output->addButton(radio2);
            gLayout->addWidget(output,4,0);
            gLayout->addWidget(radio1,5,0);
            gLayout->addWidget(radio2,5,1);
            this->bind->output_box=new QComboBox();
            this->bind->output_box->addItems(flag->tag_group_temp);
            connect(this->bind->output_box,&QComboBox::currentTextChanged,this,&paramdialog::combbox_change);
            gLayout->addWidget(this->bind->output_box,6,0,1,2);
            stop_flag=true;
            this->bind->output_box->setCurrentIndex(flag->tag_group_temp.indexOf(moudle->tag_bind->output_tag));
            stop_flag=false;
            this->bind->output_tag=moudle->tag_bind->output_tag;
            if(moudle->tag_bind->output_flag==true)
            {
                this->bind->output_flag=true;
                radio1->setChecked(true);
            }
            else
            {
                this->bind->output_flag=false;
                radio2->setChecked(true);
                emit radio2->clicked();
                if(check_moudle(moudle,1))
                    radio1->setEnabled(false);
            }
            this->bind->information=new QLineEdit();
            gLayout->addWidget(this->bind->information,7,0,1,2);
            this->bind->information->setEnabled(false);
            gLayout->addWidget(okButton, 9, 1, Qt::AlignCenter);
            setWindowTitle(tr("bind tag"));
        }
        else
        {
            for(int i=0;i<flag->param[moudle->index];i++)
            {
               // qDebug()<<123;
                if(i==0)
                {
                    addressLabel = new QLabel("input");
                }
                else if(i==1)
                {
                    addressLabel = new QLabel("output");
                }
                else
                {
                    QString s=QString("%0").arg(i-2);
                    addressLabel = new QLabel("parameter"+s);
                }
                addressText = new QLineEdit;
                addressText->setText(QString::number(moudle->param[i]));
                param.push_back(addressText);
                gLayout->addWidget(addressLabel,i+1,0);
                gLayout->addWidget(addressText,i+1,1);

            }

            gLayout->addLayout(buttonLayout, flag->param[moudle->index]+1, 1, Qt::AlignRight);
            setWindowTitle(tr("set parameter"));

        }
    }
    else
    {       
        addressLabel = new QLabel("仿真时间(s)");
        addressText = new QLineEdit;
        param.push_back(addressText);
        gLayout->addWidget(addressLabel,0,0);
        gLayout->addWidget(addressText,0,1);        
        addressLabel = new QLabel("仿真步距(s)");
        addressText = new QLineEdit;
        gLayout->addWidget(addressLabel,1,0);
        gLayout->addWidget(addressText,1,1);
        param.push_back(addressText);
        if(flag->main_socket_exist!=true)
        {
            gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);
        }
        else
        {
            this->flag=flag;
            this->main_socket_exist=flag->main_socket_exist;
            this->interface=new interface_bin();
            gLayout->addWidget(new QLabel("address:"),2,0);
            QHBoxLayout* hbox=new QHBoxLayout();
            this->interface->address_input.push_back(new QLineEdit(QString::number(192)));
            this->interface->address_input.push_back(new QLineEdit(QString::number(168)));
            this->interface->address_input.push_back(new QLineEdit(QString::number(1)));
            this->interface->address_input.push_back(new QLineEdit(QString::number(1)));
            hbox->addWidget(this->interface->address_input[0]);
            hbox->addWidget(new QLabel("."));
            hbox->addWidget(this->interface->address_input[1]);
            hbox->addWidget(new QLabel("."));
            hbox->addWidget(this->interface->address_input[2]);
            hbox->addWidget(new QLabel("."));
            hbox->addWidget(this->interface->address_input[3]);
            gLayout->addLayout(hbox,2,1);
            gLayout->addWidget(new QLabel("port:"),3,0);
            this->interface->port_input=new QLineEdit(QString::number(8080));
            gLayout->addWidget(this->interface->port_input,3,1);
            this->interface->connect_input=new QPushButton("connect");
            connect(this->interface->connect_input,&QAbstractButton::pressed,this,&paramdialog::input_connect);
            gLayout->addWidget(this->interface->connect_input,4,1,Qt::AlignLeft);

            gLayout->addLayout(buttonLayout, 6, 1, Qt::AlignRight);
            setWindowTitle(tr("仿真参数"));
            this->resize(100,150);
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);


}
void paramdialog::button()
{
    QRadioButton* button=qobject_cast<QRadioButton*>(sender());
    int index=0;
    foreach(QAbstractButton* button1,group->buttons())
    {
        if(button1==button)
        {
            break;
        }
        index++;
    }
    this->index=index;
}
void paramdialog::init_selected(int index)
{
    int i=0;
    foreach(QAbstractButton* button1,group->buttons())
    {
        if(i==index)
        {
            button1->setChecked(true);
            break;
        }
        i++;
    }
}
void paramdialog::combbox_change(QString str)
{
    if(stop_flag==true)
        return;
    QComboBox* button=qobject_cast<QComboBox*>(sender());
    this->bind->information->setText("");
    if(button==this->bind->input_box)
    {
        if(this->flag->tag_group.indexOf(str)!=-1)
        {
            if(this->bind->input_tag!="-1"&&this->bind->input_tag!="")
                this->insert_tag(this->bind->input_tag);
            this->bind->input_tag=str;
            this->remove_tag(str);
            //qDebug()<<this->flag->tag_group.indexOf(str);
        }
        else
        {
            int index=this->flag->tag_group_temp.indexOf(this->bind->input_tag);
            stop_flag=true;
            button->setCurrentIndex(index);
            stop_flag=false;
            this->bind->information->setText(str+" already exists");
        }
        //this->bind->input_tag=str;
        //qDebug()<<this->bind->input_tag;
    }
    else
    {
        if(this->flag->tag_group.indexOf(str)!=-1)
        {
            if(this->bind->output_tag!="-1"&&this->bind->output_tag!="")
                this->insert_tag(this->bind->output_tag);
            this->bind->output_tag=str;
            this->remove_tag(str);
            //qDebug()<<this->flag->tag_group.indexOf(str);
        }
        else
        {
            int index=this->flag->tag_group_temp.indexOf(this->bind->output_tag);
            stop_flag=true;
            button->setCurrentIndex(index);
            stop_flag=false;
            this->bind->information->setText(str+" already exists");
        }
        //qDebug()<<this->bind->output_tag;
    }
}
void paramdialog::combbox_radio_change()
{
    int flag=0;
    int index=0;
    QRadioButton* button=qobject_cast<QRadioButton*>(sender());
    foreach(QAbstractButton* button1,this->bind->input->buttons())
    {
        if(button1==button)
        {
            if(index==0)
            {
                this->bind->input_flag=true;
                this->bind->input_box->setEnabled(true);
            }
            else
            {
                this->bind->input_flag=false;
                this->bind->input_box->setEnabled(false);
            }
            flag=1;
            break;
        }
        index++;
    }
    if(flag==1)
        return;
    index=0;
    foreach(QAbstractButton* button1,this->bind->output->buttons())
    {
        if(button1==button)
        {
            if(index==0)
            {
                this->bind->output_flag=true;
                this->bind->output_box->setEnabled(true);
            }
            else
            {
                this->bind->output_flag=false;
                this->bind->output_box->setEnabled(false);
            }
            flag=1;
            break;
        }
        index++;
    }
}
void paramdialog::interface_check()
{
    int flag=0;
    int index=0;
    QRadioButton* button=qobject_cast<QRadioButton*>(sender());
    foreach(QAbstractButton* button1,this->interface->input->buttons())
    {
        if(button1==button)
        {
            if(index==0)
            {
                for(int i=0;i<this->interface->address_input.size();i++)
                    this->interface->address_input[i]->setEnabled(true);
                this->interface->port_input->setEnabled(true);
                this->interface->connect_input->setEnabled(true);
                this->interface->input_flag=true;
            }
            else
            {
                for(int i=0;i<this->interface->address_input.size();i++)
                    this->interface->address_input[i]->setEnabled(false);
                this->interface->port_input->setEnabled(false);
                this->interface->connect_input->setEnabled(false);
                this->interface->input_flag=false;
                this->moudle->bind_interface->input_socket->disconnectFromHost();
            }

            flag=1;
            break;
        }
        index++;
    }
    if(flag==1)
        return;
    index=0;
    foreach(QAbstractButton* button1,this->interface->output->buttons())
    {
        if(button1==button)
        {
            if(index==0)
            {
                for(int i=0;i<this->interface->address_output.size();i++)
                    this->interface->address_output[i]->setEnabled(true);
                this->interface->port_output->setEnabled(true);
                this->interface->connect_output->setEnabled(true);
                this->interface->output_flag=true;
            }
            else
            {
                for(int i=0;i<this->interface->address_output.size();i++)
                    this->interface->address_output[i]->setEnabled(false);
                this->interface->port_output->setEnabled(false);
                this->interface->connect_output->setEnabled(false);
                this->interface->output_flag=false;
                this->moudle->bind_interface->output_socket->disconnectFromHost();
            }
            break;
        }
        index++;
    }
}
interface_bin::interface_bin()
{

}
void paramdialog::input_connect()
{
    if(this->interface->connect_input->text()=="connect")
    {
        QString ip=this->interface->address_input[0]->text()+"."+this->interface->address_input[1]->text()+"."+this->interface->address_input[2]->text()+"."+this->interface->address_input[3]->text();
        interface->input_address.setAddress(ip);
        if(this->main_socket_exist==false)
            moudle->bind_interface->input_socket->connectToHost(interface->input_address,quint16(this->interface->port_input->text().toInt()));
        else
        {
            this->flag->ip_main=ip;
            this->flag->port_main=quint16(this->interface->port_input->text().toInt());
            this->flag->socket_main->connectToHost(interface->input_address,quint16(this->interface->port_input->text().toInt()));
        }

    }
    else if(this->interface->connect_input->text()=="disconnect")
    {
        if(this->main_socket_exist==false)
            moudle->bind_interface->input_socket->disconnectFromHost();
        else
            this->flag->socket_main->disconnectFromHost();
    }

}
void paramdialog::output_connect()
{
    if(this->interface->connect_output->text()=="connect")
    {
        QString ip=this->interface->address_output[0]->text()+"."+this->interface->address_output[1]->text()+"."+this->interface->address_output[2]->text()+"."+this->interface->address_output[3]->text();
        interface->output_address.setAddress(ip);
        moudle->bind_interface->output_socket->connectToHost(interface->output_address,quint16(this->interface->port_output->text().toInt()));
    }
    else if(this->interface->connect_output->text()=="disconnect")
    {
        moudle->bind_interface->output_socket->disconnectFromHost();
    }
}
bool paramdialog::check_moudle(Simulation_Moudle* moudle,int way)
{
    if(way==0)
    {
        if(moudle->input_size>=1)
        {
            for(int i=0;i<moudle->input.size();i++)
                if(moudle->input[i]->connect_line.size()!=0)
                    return true;
        }
        return false;
    }
    else if(way==1)
    {
        if(moudle->output_size>=1)
        {
            for(int i=0;i<moudle->output.size();i++)
                if(moudle->output[i]->connect_line.size()!=0)
                    return true;
        }
        return false;
    }
    return false;
}
void paramdialog::remove_tag(QString tag)
{
    if(this->flag->tag_group.indexOf(tag)!=-1)
    {
        int index=this->flag->tag_group.indexOf(tag);
        this->flag->tag_number_group.removeAt(index);
        this->flag->tag_group.removeAt(index);
    }
}
void paramdialog::insert_tag(QString tag)
{
    if(this->flag->tag_group.contains(tag)==false)
    {
        QList<int> num=getnum(tag);
        int index=sort_tag(num,0,0);
        this->flag->tag_group.insert(index,tag);
        this->flag->tag_number_group.insert(index,num);
    }
}
int paramdialog::sort_tag(QList<int> num,int index,int start)
{
    for(int i=start;i<this->flag->tag_group.size();i++)
    {
        if(num[index]<this->flag->tag_number_group[i][index])
        {
            return i;
        }
        else if(num[index]==this->flag->tag_number_group[i][index])
        {
            return sort_tag(num,index+1,i);
        }
        else
        {
            if(index>=1&&i>=1)
            {
                if(this->flag->tag_number_group[i][index-1]!=this->flag->tag_number_group[i-1][index-1])
                    return i-1;
            }
        }
    }
    return this->flag->tag_group.size();
}
QList<int> paramdialog::getnum(QString tag)
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
