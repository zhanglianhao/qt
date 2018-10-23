#include "fault_dialog.h"
fault_dialog::fault_dialog(QWidget *parent):QTabWidget(parent)
{
    this->server_dialog=new QDialog();
    this->addTab(this->server_dialog,"server mode");
    this->client_dialog=new QDialog();
    this->addTab(this->client_dialog,"client mode");
    m_pBtn_Listen=new QPushButton(QObject::tr("start listen"),this->server_dialog);
    m_pBtn_StopListen=new QPushButton(QObject::tr("stop listen"),this->server_dialog);
    m_pEdt_Info=new QTextEdit(this->server_dialog);
    //this->m_pEdt_Info->setEnabled(false);
    m_pServer=new QTcpServer(this->server_dialog);
    connect(m_pBtn_Listen,&QAbstractButton::pressed,this,&fault_dialog::Btn_ListenClickedSlot);
    connect(m_pBtn_StopListen,&QAbstractButton::pressed,this,&fault_dialog::Btn_StopListenClickedSlot);
    connect(m_pServer,&QTcpServer::newConnection,this,&fault_dialog::newConnectionSlot);

    init();
    init_server_latyout();
    init_client_latyout();
    window_size=this->size();
}
void fault_dialog::init_server_latyout()
{
    QLabel* target_ip=new QLabel("target ip:");
    QLabel* target_port=new QLabel("target port:");
    QLabel* local_ip=new QLabel("local ip:");
    QLabel* local_port=new QLabel("local port:");
    QLabel* send=new QLabel("send:");
    QLabel* rece=new QLabel("receive:");
    QFormLayout* form=new QFormLayout();
    form->setRowWrapPolicy(QFormLayout::WrapAllRows);
    form->addRow(target_ip,ip_target);
    form->addRow(target_port,port_target);
    form->addRow(local_ip,ip_local);
    form->addRow(local_port,port_local);
    form->addRow(send,send_count);
    form->addRow(rece,rece_count);
    form->addRow(this->clear_count);
    connect(this->clear_count,&QAbstractButton::pressed,this,&fault_dialog::clear_count_data);

    QVBoxLayout* vbox=new QVBoxLayout();
    vbox->addLayout(form);
    dis_all=new QPushButton("disconnect all");
    dis_all->setEnabled(false);
    connect(this->dis_all,&QAbstractButton::pressed,this,&fault_dialog::disconnect_all);
    vbox->addWidget(dis_all);
    vbox->addWidget(m_pBtn_Listen,Qt::AlignHCenter);
    vbox->addWidget(m_pBtn_StopListen,Qt::AlignHCenter);

    QHBoxLayout* hbox=new QHBoxLayout();
    hbox->addLayout(vbox);

    QVBoxLayout* vbox1=new QVBoxLayout();
    vbox1->addWidget(m_pEdt_Info);
    QHBoxLayout* hbox1=new QHBoxLayout();
    hbox1->addWidget(this->rece_button);
    this->rece_button->setEnabled(false);
    connect(this->rece_button,&QAbstractButton::pressed,this,&fault_dialog::disconnect_the_client);
    hbox1->addWidget(this->clear_rece);
    connect(this->clear_rece,&QAbstractButton::pressed,this,&fault_dialog::clear_rece_data);
    vbox1->addLayout(hbox1);
    hbox->addLayout(vbox1);

    vbox1=new QVBoxLayout();
    vbox1->addWidget(send_edit);
    hbox1=new QHBoxLayout();
    hbox1->addWidget(this->send_button);
    connect(this->send_button,&QAbstractButton::pressed,this,&fault_dialog::send_data);
    this->send_button->setEnabled(false);
    this->auto_flag.push_back(new QCheckBox());
    this->auto_flag.push_back(new QCheckBox());
    hbox1->addWidget(this->auto_flag[0]);
    connect(this->auto_flag[0], &QCheckBox::stateChanged, this, &fault_dialog::state_change);
    connect(this->auto_flag[1], &QCheckBox::stateChanged, this, &fault_dialog::state_change);
    this->auto_send_time.push_back(new QLineEdit("100"));
    this->auto_send_time.push_back(new QLineEdit("100"));
    hbox1->addWidget(this->auto_send_time[0]);
    hbox1->addWidget(new QLabel("ms"));

    hbox1->addWidget(this->clear_send);
    connect(this->clear_send,&QAbstractButton::pressed,this,&fault_dialog::clear_send_data);
    vbox1->addLayout(hbox1);

    hbox->addLayout(vbox1);

    QVBoxLayout* center_layout=new QVBoxLayout();
    center_layout->addLayout(this->page_layout);
    center_layout->addLayout(hbox);
    this->server_dialog->setLayout(center_layout);

    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    //qDebug()<<info.addresses();
    ip_local->setText(info.addresses()[7].toString());
    ip_local->setEnabled(false);

    port_local->setText(QString::number(this->local_port));

    ip_target->setEnabled(false);
    port_target->setEnabled(false);

    send_count->setText(QString::number(0));
    send_count->setEnabled(false);
    rece_count->setText(QString::number(0));
    rece_count->setEnabled(false);


}
void fault_dialog::init_client_latyout()
{
    QLabel* target_ip=new QLabel("target ip:");
    QLabel* target_port=new QLabel("target port:");
    QLabel* send=new QLabel("send:");
    QLabel* rece=new QLabel("receive:");
    QFormLayout* form=new QFormLayout();
    form->setRowWrapPolicy(QFormLayout::WrapAllRows);
    QHBoxLayout* hbox=new QHBoxLayout();
    this->client_ui->address_input[0]->setMinimumWidth(10);
    this->client_ui->address_input[1]->setMinimumWidth(10);
    this->client_ui->address_input[2]->setMinimumWidth(10);
    this->client_ui->address_input[3]->setMinimumWidth(10);
    hbox->addWidget(this->client_ui->address_input[0]);
    hbox->addWidget(new QLabel("."));
    hbox->addWidget(this->client_ui->address_input[1]);
    hbox->addWidget(new QLabel("."));
    hbox->addWidget(this->client_ui->address_input[2]);
    hbox->addWidget(new QLabel("."));
    hbox->addWidget(this->client_ui->address_input[3]);


    form->addRow(target_ip,hbox);
    form->addRow(target_port,this->client_ui->port_input);
    form->addRow(send,send_count_client);
    form->addRow(rece,rece_count_client);
    form->addRow(this->clear_count_client);
    connect(this->clear_count_client,&QAbstractButton::pressed,this,&fault_dialog::clear_count_data);

    QVBoxLayout* vbox=new QVBoxLayout();
    /*
    vbox->addWidget(target_ip);
    vbox->addLayout(hbox);
    vbox->addWidget(target_port);
    vbox->addWidget(this->client_ui->port_input);
    vbox->addWidget(send);
    vbox->addWidget(send_count_client);
    vbox->addWidget(rece);
    vbox->addWidget(this->clear_count_client);
*/
    vbox->addLayout(form);
    vbox->addWidget(connect_mode);
    vbox->addWidget(this->client_ui->connect_input,Qt::AlignHCenter);
    connect(client_ui->connect_input,&QAbstractButton::pressed,this,&fault_dialog::input_connect);

    hbox=new QHBoxLayout();
    hbox->addLayout(vbox);

    QVBoxLayout* vbox1=new QVBoxLayout();
    vbox1->addWidget(this->client_ui->rece_edit);
    connect(this->clear_rece_client,&QAbstractButton::pressed,this,&fault_dialog::clear_rece_data);
    vbox1->addWidget(this->clear_rece_client);
    hbox->addLayout(vbox1);

    vbox1=new QVBoxLayout();
    vbox1->addWidget(this->client_ui->send_edit);
    QHBoxLayout* hbox1=new QHBoxLayout();
    hbox1->addWidget(this->send_button_client);
    connect(this->send_button_client,&QAbstractButton::pressed,this,&fault_dialog::send_data);
    this->send_button_client->setEnabled(false);
    this->auto_flag[1]->setEnabled(false);
    hbox1->addWidget(this->clear_send_client);
    hbox1->addWidget(this->auto_flag[1]);
    hbox1->addWidget(this->auto_send_time[1]);
    connect(this->clear_send_client,&QAbstractButton::pressed,this,&fault_dialog::clear_send_data);
    vbox1->addLayout(hbox1);

    hbox->addLayout(vbox1);

    this->client_dialog->setLayout(hbox);


    send_count_client->setText(QString::number(count_send_client));
    send_count_client->setEnabled(false);
    rece_count_client->setText(QString::number(count_rece_client));
    rece_count_client->setEnabled(false);

}
void fault_dialog::init()
{
    //server mode
    rece_button=new QPushButton("disconnect",this->server_dialog);
    send_button=new QPushButton("send",this->server_dialog);
    clear_send=new QPushButton("clear send",this->server_dialog);
    clear_rece=new QPushButton("clear rece",this->server_dialog);
    clear_count=new QPushButton("clear count",this->server_dialog);

    send_edit=new QTextEdit(this->server_dialog);
    ip_target=new QLineEdit(this->server_dialog);
    port_target=new QLineEdit(this->server_dialog);
    ip_local=new QLineEdit(this->server_dialog);
    port_local=new QLineEdit(this->server_dialog);
    send_count=new QLineEdit(this->server_dialog);
    rece_count=new QLineEdit(this->server_dialog);

    //client mode
    client_ui->address_input.push_back(new QLineEdit("192",this->client_dialog));
    client_ui->address_input.push_back(new QLineEdit("168",this->client_dialog));
    client_ui->address_input.push_back(new QLineEdit("1",this->client_dialog));
    client_ui->address_input.push_back(new QLineEdit("1",this->client_dialog));
    client_ui->port_input=new QLineEdit("8080",this->client_dialog);
    client_ui->connect_input=new QPushButton("connect",this->client_dialog);

    client_ui->client_tcp=new QTcpSocket(this->client_dialog);
    connect(client_ui->client_tcp,&QTcpSocket::connected,this,&fault_dialog::client_connect);
    connect(client_ui->client_tcp,&QTcpSocket::disconnected,this,&fault_dialog::client_disconnect);
    connect(client_ui->client_tcp,SIGNAL(readyRead()),this,SLOT(client_receive()));

    client_ui->client_udp=new QTcpSocket(this->client_dialog);
    connect(client_ui->client_udp,&QTcpSocket::connected,this,&fault_dialog::client_connect);
    connect(client_ui->client_udp,&QTcpSocket::disconnected,this,&fault_dialog::client_disconnect);
    connect(client_ui->client_udp,SIGNAL(readyRead()),this,SLOT(client_receive()));

    client_ui->client_Sctp=new QTcpSocket(this->client_dialog);
    connect(client_ui->client_Sctp,&QTcpSocket::connected,this,&fault_dialog::client_connect);
    connect(client_ui->client_Sctp,&QTcpSocket::disconnected,this,&fault_dialog::client_disconnect);
    connect(client_ui->client_Sctp,SIGNAL(readyRead()),this,SLOT(client_receive()));

    client_ui->send_edit=new QTextEdit(this->client_dialog);
    client_ui->rece_edit=new QTextEdit(this->client_dialog);
    //client_ui->rece_edit->setEnabled(false);
    mode_connect.push_back("Tcp");
    mode_connect.push_back("Udp");
    mode_connect.push_back("Sctp");
    this->connect_mode=new QComboBox();
    connect_mode->addItems(mode_connect);

    send_button_client=new QPushButton("send",this->client_dialog);
    clear_send_client=new QPushButton("clear send",this->client_dialog);
    clear_rece_client=new QPushButton("clear rece",this->client_dialog);
    clear_count_client=new QPushButton("clear count",this->client_dialog);

    send_count_client=new QLineEdit(this->client_dialog);
    rece_count_client=new QLineEdit(this->client_dialog);

    this->client_timer=new QTimer();
    connect(this->client_timer, SIGNAL(timeout()), this, SLOT(timerSlot()));

}
void fault_dialog::input_connect()
{
    if(client_ui->connect_input->text()=="connect")
    {
        //client_ui->connect_input->text()="disconnect";
        QString ip=this->client_ui->address_input[0]->text()+"."+this->client_ui->address_input[1]->text()+"."+this->client_ui->address_input[2]->text()+"."+this->client_ui->address_input[3]->text();
        client_ui->input_address.setAddress(ip);
        if(this->connect_mode->currentText()=="Tcp")//连接mode 选择
            client_ui->client=client_ui->client_tcp;
        else if(this->connect_mode->currentText()=="Udp")//连接mode 选择
            client_ui->client=client_ui->client_udp;
        else if(this->connect_mode->currentText()=="Sctp")//连接mode 选择
            client_ui->client=client_ui->client_Sctp;
        qDebug()<<this->connect_mode->currentText();
        client_ui->client->connectToHost(client_ui->input_address,quint16(this->client_ui->port_input->text().toInt()));
    }
    else
    {
        client_ui->client->disconnectFromHost();
    }
}
void fault_dialog::resizeEvent(QResizeEvent *)
{
    this->resize(window_size);
}
void fault_dialog::send_data()
{
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    if(button==this->send_button_client)
    {
        QString send_str=this->client_ui->send_edit->toPlainText();
        qint64 length=0;
        if(this->client_ui->client!=nullptr&&this->client_ui->client->isOpen())
        {
            if((length=this->client_ui->client->write(send_str.toLatin1(),send_str.length()))!=send_str.length())
            {
            }
            else
            {
                this->count_send_client+=length;
                this->send_count_client->setText(QString::number(count_send_client));
            }
        }
        return;
    }
    QString send_str=this->send_edit->toPlainText();
    qint64 length=0;
    if(m_pSocket!=nullptr&&m_pSocket->isOpen())
    {
        if((length=m_pSocket->write(send_str.toLatin1(),send_str.length()))!=send_str.length())
        {
        }
        else
        {
            this->map_str_send_count[m_pSocket]+=length;
            this->send_count->setText(QString::number(this->map_str_send_count[m_pSocket]));
        }
    }
}
void fault_dialog::clear_count_data()
{
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    if(button==this->clear_count)
    {
        this->map_str_rece_count[m_pSocket]=0;
        this->map_str_send_count[m_pSocket]=0;
        this->rece_count->setText(QString::number(this->map_str_rece_count[m_pSocket]));
        this->send_count->setText(QString::number(this->map_str_send_count[m_pSocket]));
    }
    else if(button==this->clear_count_client)
    {
        this->count_rece_client=0;
        this->count_send_client=0;
        this->rece_count_client->setText(QString::number(this->count_rece_client));
        this->send_count_client->setText(QString::number(this->count_send_client));
    }

}
void fault_dialog::clear_send_data()
{
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    if(button==this->clear_send)
        this->send_edit->setText("");
    else if(button==this->clear_send_client)
        this->client_ui->send_edit->setText("");
}
void fault_dialog::clear_rece_data()
{
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    if(button==this->clear_rece)
    {
        this->m_pEdt_Info->setText("");
        this->map_str_rece[m_pSocket].clear();
    }
    else
        this->client_ui->rece_edit->setText("");
}
void fault_dialog::Btn_ListenClickedSlot()
{
    if(!m_pServer->isListening())
    {
        if(m_pServer->listen(QHostAddress::Any,quint16(this->port_local->text().toInt())))
        {
            //QString address=m_pServer->serverAddress().toString();
            //quint64 port=m_pServer->serverPort();
            //m_pEdt_Info->append(address);
            //m_pEdt_Info->append(QString::number(port));
            m_pEdt_Info->append(tr("open port success"));
            this->port_local->setEnabled(false);
        }
        else
            m_pEdt_Info->append(tr("open port faild"));
    }
    else
    {
        m_pEdt_Info->append(tr("listening"));
    }
}
void fault_dialog::Btn_StopListenClickedSlot()
{
    if(m_pServer->isListening())
    {
        m_pServer->close();
        m_pEdt_Info->append(tr("stop listen"));
        this->port_local->setEnabled(true);
    }
}
void fault_dialog::newConnectionSlot()
{        
    QTcpSocket* socket=m_pServer->nextPendingConnection();

    this->target_ip=socket->peerAddress().toString();
    this->ip_target->setText(this->target_ip);
    this->target_port=socket->peerPort();
    this->port_target->setText(QString::number(this->target_port));
    //m_pEdt_Info->append(m_pSocket->localAddress().toString());

    this->map_str_send.insert(socket,"");
    //this->map_str_rece.insert(m_pSocket,"");
    this->map_str_send_count.insert(socket,0);
    this->map_str_rece_count.insert(socket,0);
    this->map_str_ip.insert(socket,this->target_ip);
    this->map_str_port.insert(socket,quint16(this->target_port));
    QPushButton* button=new QPushButton(this->target_ip+":"+QString::number(this->target_port));
    this->map_button.insert(socket,button);
    this->page_layout->addWidget(button);
    connect(button,&QAbstractButton::pressed,this,&fault_dialog::page_change);
    QTimer* time=new QTimer();
    this->map_time.insert(socket,time);
    connect(time, SIGNAL(timeout()), this, SLOT(timerSlot()));
    this->map_send_auto.insert(socket,false);
    this->map_send_auto_time.insert(socket,100);

    connect(socket,&QTcpSocket::disconnected,this,&fault_dialog::disconnect_client);
    connect(socket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    emit button->pressed();
    this->send_button->setEnabled(true);
    this->auto_flag[0]->setEnabled(true);
    this->rece_button->setEnabled(true);
    this->dis_all->setEnabled(true);
    qint64 length=0;
    QString str=tr("welcome");
    if((length=socket->write(str.toLatin1(),str.length()))!=str.length())
    {

    }
    m_pEdt_Info->append(tr("new client connect to server"));
}
void fault_dialog::client_connect()
{
    qDebug()<<"connected";
    send_button_client->setEnabled(true);
    this->auto_flag[1]->setEnabled(true);
    client_ui->rece_edit->append("connect to server success");
    this->client_ui->connect_input->setText("disconnect");
}
void fault_dialog::client_disconnect()
{
    qDebug()<<"disconnected";
    send_button_client->setEnabled(false);
    this->client_auto=false;
    this->stop_trigger=true;
    this->auto_flag[1]->setCheckState(Qt::Unchecked);
    this->stop_trigger=false;
    this->auto_flag[1]->setEnabled(false);
    client_ui->rece_edit->append("disconnect to server");
    this->client_ui->connect_input->setText("connect");
    this->client_timer->stop();
}
void fault_dialog::client_receive()
{

    while(client_ui->client->bytesAvailable())
    {
        QByteArray temp;
        temp=client_ui->client->readLine();
        QString str(temp);
        client_ui->rece_edit->append(str);
        this->count_rece_client+=str.size();
        this->rece_count_client->setText(QString::number(this->count_rece_client));
    }
}
void fault_dialog::disconnect_all()//服务器断开所有客户端连接
{
    QList<QTcpSocket*> socket_group=this->map_button.keys();
    for(int i=0;i<socket_group.size();i++)
        socket_group[i]->disconnectFromHost();
}
void fault_dialog::disconnect_the_client()
{
    m_pSocket->disconnectFromHost();
}
void fault_dialog::disconnect_client()
{   
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    //delete socket; socket不能直接从内存中移除
    qDebug()<<"disconnected";
    this->m_pEdt_Info->append("disconnected");
    if(this->map_button.contains(socket))
    {
        this->map_str_ip.remove(socket);
        this->map_str_port.remove(socket);
        this->map_str_rece.remove(socket);
        this->map_str_rece_count.remove(socket);
        this->map_str_send.remove(socket);
        this->map_str_send_count.remove(socket);
        QPushButton* button=*this->map_button.find(socket);
        this->map_button.remove(socket);
        this->page_layout->removeWidget(button);
        delete button;
        delete this->map_time[socket];//删除定时器
        if(socket==m_pSocket)
        {
            m_pSocket=nullptr;
            if(this->map_button.size()>=1)
            {
                emit this->map_button.first()->pressed();
            }
            else
            {
                this->send_button->setEnabled(false);
                this->auto_flag[0]->setEnabled(false);
                this->rece_button->setEnabled(false);
                this->dis_all->setEnabled(false);
            }
        }
    }
}
void fault_dialog::dataReceived()
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    if(this->map_str_ip.contains(socket)==false)
        return;
    while(socket->bytesAvailable())
    {
        QByteArray temp;
        temp=socket->readLine();
        QString str(temp);
        if(socket==m_pSocket)
            m_pEdt_Info->append(str);
        this->map_str_rece[socket].push_back(str);
        this->map_str_rece_count[socket]+=str.size();
        if(socket==m_pSocket)
            this->rece_count->setText(QString::number(this->map_str_rece_count[socket]));
    }
}
void fault_dialog::page_change()
{
    QPushButton* button=qobject_cast<QPushButton*>(sender());
    if(button!=*this->map_button.find(m_pSocket))
    {
        if(m_pSocket!=nullptr)
            this->map_str_send[m_pSocket]=this->send_edit->toPlainText();
        m_pSocket=this->map_button.key(button);
        this->ip_target->setText(this->map_str_ip[m_pSocket]);
        this->port_target->setText(QString::number(this->map_str_port[m_pSocket]));
        this->send_count->setText(QString::number(this->map_str_send_count[m_pSocket]));
        this->rece_count->setText(QString::number(this->map_str_rece_count[m_pSocket]));
        this->m_pEdt_Info->setText("");
        for(int i=0;i<this->map_str_rece[m_pSocket].size();i++)
            this->m_pEdt_Info->append(this->map_str_rece[m_pSocket][i]);
        this->send_edit->setText(this->map_str_send[m_pSocket]);
        stop_trigger=true;
        if(this->map_send_auto[m_pSocket]==false)
        {
            this->send_button->setEnabled(true);
            this->auto_flag[0]->setCheckState(Qt::Unchecked);
        }
        else
        {
            this->send_button->setEnabled(false);
            this->auto_flag[0]->setCheckState(Qt::Checked);
        }
        stop_trigger=false;
        this->auto_send_time[0]->setText(QString::number(this->map_send_auto_time[m_pSocket]));
    }
}
void fault_dialog::timerSlot()
{
    QTimer* timer=qobject_cast<QTimer*>(sender());
    if(timer==this->client_timer)
    {
        client_ui->client->write(this->client_ui->send_edit->toPlainText().toLatin1(),this->client_ui->send_edit->toPlainText().size());
        this->client_timer->start(this->auto_send_time[1]->text().toInt());
        this->count_send_client+=this->client_ui->send_edit->toPlainText().size();
        this->send_count_client->setText(QString::number(count_send_client));
        return;
    }

    QTcpSocket* socket=this->map_time.key(timer);
    if(socket==m_pSocket)
    {
        this->map_str_send_count[socket]+=this->send_edit->toPlainText().size();
        socket->write(this->send_edit->toPlainText().toLatin1(),this->send_edit->toPlainText().size());
        this->send_count->setText(QString::number(this->map_str_send_count[socket]));
    }
    else
    {
        this->map_str_send_count[socket]+=this->map_str_send[socket].size();
        socket->write(this->map_str_send[socket].toLatin1(),this->map_str_send[socket].size());
    }
    timer->start(this->map_send_auto_time[socket]);
}
void fault_dialog::state_change()
{
    if(stop_trigger==true)
        return;
    QCheckBox* box=qobject_cast<QCheckBox*>(sender());
    if(box==this->auto_flag[1])
    {
        if(this->client_auto==false)
        {
            //qDebug()<<this->auto_send_time[1]->text().toInt();
            this->client_timer->start(this->auto_send_time[1]->text().toInt());
            this->client_auto=true;
            this->send_button_client->setEnabled(false);
        }
        else
        {
            this->client_timer->stop();
            this->client_auto=false;
            this->send_button_client->setEnabled(true);
        }
        return;
    }

    QCheckBox* button=qobject_cast<QCheckBox*>(sender());

    if(this->auto_send_time[0]->text()==""||m_pSocket==nullptr)
    {
        stop_trigger=true;
        if(button->isChecked())
        {
            button->setCheckState(Qt::Unchecked);
        }
        else
        {
            button->setCheckState(Qt::Checked);
        }
        stop_trigger=false;
        return;
    }
    if(this->map_send_auto[m_pSocket]==false)//开启自动发送
    {
        this->send_button->setEnabled(false);
        this->map_send_auto_time[m_pSocket]=this->auto_send_time[0]->text().toInt();
        this->map_time[m_pSocket]->start(this->auto_send_time[0]->text().toInt());
        this->map_send_auto[m_pSocket]=true;
    }
    else//关闭自动发送
    {
        this->send_button->setEnabled(true);
        this->map_time[m_pSocket]->stop();
        this->map_send_auto[m_pSocket]=false;
    }
}
