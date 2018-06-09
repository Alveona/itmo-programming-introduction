#ifndef LOGICBUTTON_H
#define LOGICBUTTON_H
#include "rbbutton.h"

enum STATE
{
    NULL_,
    EMPTY,
    BOMB,
    OPENED,
    FLAG
};
class LogicButton
{
    //Q_OBJECT
    //static QMessageBox gameOverMsg;
    STATE currentstate;
    STATE previousstate;
    RbButton *linkedRbButton;
    //static int **field;
    int bombCount;
    int H;
    int W;
    int index;
    //Q_OBJECT
public:
    LogicButton(int defaultstate = 0, RbButton *linkedRbButton = nullptr, int index = 0);
    //this->field = field
    STATE getState() const;
    void setState(const STATE &value);
    int getIndex() const;
    void setIndex(int value);
    void updateButton(STATE currentstate);
    int getBombCount() const;
    void setBombCount(int value);

    void setH(int value);

    void setW(int value);

    int getW() const;

    int getH() const;

public slots:
    void doRightLogic();
    void doLeftLogic();
};

#endif // LOGICBUTTON_H
