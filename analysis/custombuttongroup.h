#ifndef CUSTOMBUTTONGROUP_H
#define CUSTOMBUTTONGROUP_H

#include <QWidget>
#include "custombutton.h"
QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QVBoxLayout;
class QButtonGroup;
QT_END_NAMESPACE

class CustomButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit CustomButtonGroup(QWidget *parent = nullptr);

signals:

public slots:

private:
  void createbutton(QWidget *parent);
  void ana1(void);
  void ana2();
  void ana3();
  void ana4();
  void ana5();
  void ana6();
};

#endif // CUSTOMBUTTONGROUP_H
