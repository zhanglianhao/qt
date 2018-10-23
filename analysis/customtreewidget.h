#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H
#include <QtWidgets>

class CustomTreeWidget:public QTreeWidget
{
public:
    CustomTreeWidget(QWidget *parent = nullptr);
protected:
    void resizeEvent(QResizeEvent *);
private:
    QMap<QString, QTreeWidgetItem*> itemMap_;
    QMap<QString, QString> itemstring_;
    QTreeWidgetItem* parent;
    QWidget* parent_window;
    QScrollArea* scoll;
    QLabel* label_content;
    QSize window_size;
    int addItem(QStringList item, QString parentKey, QString theKey,QString content);
public slots:
    void clicked();
};

#endif // CUSTOMTREEWIDGET_H
