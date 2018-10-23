#ifndef PARAMDIALOG_H
#define PARAMDIALOG_H
#include "custombutton.h"
#include <QWidget>
#include <QtWidgets>
#include "simulation_moudle.h"
#include "system_flag.h"
#include <QDebug>
class interface_bin;
struct tag_bind
{
    QButtonGroup *input;
    QButtonGroup *output;

    bool input_flag=false;
    bool output_flag=false;

    QComboBox* input_box;
    QComboBox* output_box;

    QString input_tag="-1";
    QString output_tag="-1";

    QLineEdit* information;
};
class interface_bin//用于接口绑定模块的参数配置
{
public:
     interface_bin();
     QList<QLineEdit*> address_input;//输入接口绑定ip
     QLineEdit *port_input;
     QHostAddress input_address;
     QList<QLineEdit*> address_output;//输出接口绑定ip
     QLineEdit *port_output;
     QHostAddress output_address;

     QPushButton* connect_input;
     QPushButton* connect_output;

     QButtonGroup *input;
     QButtonGroup *output;

     bool input_flag=false;
     bool output_flag=false;


};
class paramdialog : public QDialog
{
    Q_OBJECT
public:
    explicit paramdialog(QWidget *parent = nullptr,Simulation_Moudle* moudle= nullptr,system_flag* flag=nullptr);
    QLineEdit *nameText;
    QLineEdit *addressText;
    QList<QLineEdit*> param;
    QButtonGroup *group;
    interface_bin* interface;
    tag_bind* bind;
    int index;//复选按钮序号  
    bool main_socket_exist=false;
private:
    QLabel *nameLabel;
    QLabel *addressLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    Simulation_Moudle* moudle;
    system_flag* flag;
    bool stop_flag=false;
    void button();
    void init_selected(int index);
    void interface_check();
    void input_connect();
    void output_connect();

    bool check_moudle(Simulation_Moudle* moudle,int way);
    void combbox_change(QString str);
    void combbox_radio_change();

    void remove_tag(QString tag);//为了避免多个模块绑定同一标签，增加标签删除、插入功能
    void insert_tag(QString tag);
    QList<int> getnum(QString tag);//获取tag对应的number
    int sort_tag(QList<int> num,int index,int start);
signals:

public slots:
};

#endif // PARAMDIALOG_H
