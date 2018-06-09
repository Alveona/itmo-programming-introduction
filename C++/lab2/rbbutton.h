#ifndef RBBUTTON_H
#define RBBUTTON_H
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>
//#include "logicbutton.h"
class RbButton : public QPushButton
{
    Q_OBJECT
    //LogicButton *linkedLogicButton;
    static QMessageBox gameOverMsg;
    QPalette p;
    int index;
public:
    explicit RbButton(QWidget *parent = nullptr, int index = 0);
    //explicit RbButton(int index = 0);
    void changeColor(QColor color = Qt::blue);
    int getIndex() const;
    void setIndex(int value);
    //void mousePressEvent(QMouseEvent *event);
//protected:
    void mousePressEvent(QMouseEvent *event);
    void bombopened();
    void flagclicked(int i);
    static QMessageBox getGameOverMsg();
signals:
    void leftclicked(int index);
    void rightclicked(int index);
    void bombopened_signal();
    void flagclicked_signal(int i);
};

#endif // RBBUTTON_H
