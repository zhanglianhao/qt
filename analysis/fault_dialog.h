#ifndef FAULT_DIALOG_H
#define FAULT_DIALOG_H
#include <QtWidgets>
#include <qtextcodec.h>
#include <QtNetwork>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
struct client_connet//用于接口绑定模块的参数配置
{
     QList<QLineEdit*> address_input;//输入接口绑定ip
     QLineEdit *port_input;
     QHostAddress input_address;

     QTcpSocket* client=nullptr;
     QTcpSocket* client_tcp=nullptr;
     QTcpSocket* client_udp=nullptr;
     QTcpSocket* client_Sctp=nullptr;

     QPushButton* connect_input;
     QTextEdit   *send_edit;
     QTextEdit   *rece_edit;
};
class fault_dialog : public QTabWidget
{
    Q_OBJECT
public:
    fault_dialog(QWidget *parent = nullptr);
protected:
    void resizeEvent(QResizeEvent *);
private slots:
    void Btn_ListenClickedSlot();
    void Btn_StopListenClickedSlot();
    void newConnectionSlot();
    void dataReceived();
    void client_receive();
private:
    QDialog* server_dialog;
    QDialog* client_dialog;
    QSize window_size;

    //server mode ui
    QTcpServer *m_pServer=nullptr;
    QTcpSocket *m_pSocket=nullptr;
    QPushButton *m_pBtn_Listen;
    QPushButton *m_pBtn_StopListen;
    QPushButton* rece_button;
    QPushButton* send_button;
    QPushButton* clear_send;
    QPushButton* clear_rece;
    QPushButton* clear_count;

    QTextEdit   *m_pEdt_Info;
    QTextEdit   *send_edit;
    QLineEdit* ip_target;
    QLineEdit* port_target;
    QLineEdit* ip_local;
    QLineEdit* port_local;
    QLineEdit* send_count;
    QLineEdit* rece_count;

    QPushButton* dis_all;
    QList<QLineEdit*> auto_send_time;
    QList<QCheckBox*> auto_flag;
    bool stop_trigger=false;
    //多客户端连接 多页面切换显示
    QMap<QTcpSocket*,QPushButton*> map_button;
    QMap<QTcpSocket*,QString> map_str_send;
    QMap<QTcpSocket*,QStringList> map_str_rece;
    QMap<QTcpSocket*,QString> map_str_ip;
    QMap<QTcpSocket*,quint16> map_str_port;
    QMap<QTcpSocket*,int> map_str_send_count;
    QMap<QTcpSocket*,int> map_str_rece_count;
    QMap<QTcpSocket*,QTimer*> map_time;
    QMap<QTcpSocket*,bool> map_send_auto;//自动发送
    QMap<QTcpSocket*,int> map_send_auto_time;
    void page_change();
    QList<QTcpSocket*> socket_pool;//销毁socket池 节省内存 在new socket之前，先从pool中获取

    QString local_ip="";
    QString target_ip="";
    int local_port=8080;
    int target_port;

    //client mode ui
    QHBoxLayout* page_layout=new QHBoxLayout();
    client_connet* client_ui=new client_connet();
    QPushButton* send_button_client;
    QPushButton* clear_send_client;
    QPushButton* clear_rece_client;
    QPushButton* clear_count_client;
    QLineEdit* send_count_client;
    QLineEdit* rece_count_client;
    QComboBox* connect_mode;//Tcp/Udp/Sctp
    QStringList mode_connect;
    QTimer* client_timer;
    bool client_auto=false;
    int count_send_client=0;
    int count_rece_client=0;
    void input_connect();
    void client_connect();
    void client_disconnect();

    void init_server_latyout();
    void init_client_latyout();
    void send_data();
    void clear_send_data();
    void clear_rece_data();
    void clear_count_data();
    void disconnect_client();
    void disconnect_the_client();
    void disconnect_all();
    void init();
    void state_change();
private slots:
    void timerSlot();
    //void line_change(QString str);
};

#endif // FAULT_DIALOG_H
