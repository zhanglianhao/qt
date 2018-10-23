#ifndef DATA_DIALOG_H
#define DATA_DIALOG_H
#include <QtWidgets>
#include <qtextcodec.h>
class data_dialog:public QDialog
{
public:
    data_dialog(QWidget *parent = nullptr);
    QList<QCheckBox*> checkbox_group_right;//外部调用
    //QMap<QString,QString> name_to_url;
    QList<QString> url;
    QList<QCheckBox*> button_group;
protected:
    void resizeEvent(QResizeEvent *);
private:
    QList<QCheckBox*> checkbox_group_left;
    QListView* left_view;
    QListView* right_view;
    QScrollArea* left_scroll;
    QScrollArea* right_scroll;
    QGridLayout * right_Layout;
    QGridLayout * left_gLayout;
    QList<bool> checked_flag_left;
    QList<bool> checked_flag_right;   

    QPushButton* join;
    QPushButton* remove;
    QPushButton* right_move;
    QPushButton* left_move;
    QPushButton* start;

    QSize window_size;

    bool stop_trigger=false;
    void init();

    void move_to_left();
    void move_to_right();
    void remove_box();
    void start_analysis();
    void join_text();
    QString url_to_name(QString filename);
    void state_change();
    void updata_pos();
};

#endif // DATA_DIALOG_H
