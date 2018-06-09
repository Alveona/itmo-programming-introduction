#include "logicbutton.h"
#include "rbbutton.h"
STATE LogicButton::getState() const
{
    return currentstate;
}

void LogicButton::setState(const STATE &value)
{
    currentstate = value;
}

int LogicButton::getIndex() const
{
    return index;
}

void LogicButton::setIndex(int value)
{
    index = value;
}

int LogicButton::getBombCount() const
{
    return bombCount;
}

void LogicButton::setBombCount(int value)
{
    bombCount = value;
}

void LogicButton::setH(int value)
{
    H = value;
}

void LogicButton::setW(int value)
{
    W = value;
}

int LogicButton::getW() const
{
    return W;
}

int LogicButton::getH() const
{
    return H;
}

LogicButton::LogicButton(int defaultstate, RbButton *linkedRbButton, int index)
{
    this->bombCount = bombCount;
    previousstate = NULL_;
    //auto gameOverMsg = new QMessageBox();
    //gameOverMsg->setText("Game Over");
    this->linkedRbButton = linkedRbButton;
    this->index = index;
    //printf("%d\n", defaultstate);
    currentstate = (defaultstate == 0) ? EMPTY : BOMB;
    //currentstate = defaultstate;
    //linkedRbButton->setStyleSheet("border-image: url(:/images/Assets/cell.png);");
    switch(currentstate)
    {
        case EMPTY:
            linkedRbButton->changeColor(Qt::blue);
        break;
        case BOMB:
            linkedRbButton->changeColor(Qt::green);
        break;
    }
}
void LogicButton::updateButton(STATE currentstate)
{
    //switch(current)
    switch(currentstate)
    {
        case EMPTY:
            linkedRbButton->setIcon(QIcon(":/images/Assets/cell_0.png"));
        break;
        case BOMB:
            linkedRbButton->setIcon(QIcon(":/images/Assets/mine.png"));
        break;
        case OPENED:
            linkedRbButton->bombopened();
            switch(bombCount)
            {
                case 0: linkedRbButton->setIcon(QIcon(":/images/Assets/cell_0.png"));
                break;
                case 1: linkedRbButton->setIcon(QIcon(":/images/Assets/cell_1.png"));
                break;
                case 2: linkedRbButton->setIcon(QIcon(":/images/Assets/cell_2.png"));
                break;
                case 3: linkedRbButton->setIcon(QIcon(":/images/Assets/cell_3.png"));
                break;
                case 4: linkedRbButton->setIcon(QIcon(":/images/Assets/cell_4.png"));
                break;
                case 5: linkedRbButton->setIcon(QIcon(":/images/Assets/cell_5.png"));
                break;
                case 6: linkedRbButton->setIcon(QIcon(":/images/Assets/cell_6.png"));
                break;
                case 7: linkedRbButton->setIcon(QIcon(":/images/Assets/cell_7.png"));
                break;
                case 8: linkedRbButton->setIcon(QIcon(":/images/Assets/cell_8.png"));
                break;
            }

        break;
        case FLAG:
            linkedRbButton->setIcon(QIcon(":/images/Assets/flag.png"));
        break;
    }
}
void LogicButton::doRightLogic()
{
    if(currentstate != OPENED)
    {
        if(currentstate != FLAG)
        {
            previousstate = currentstate;
            currentstate = FLAG;
            linkedRbButton->flagclicked(1);
            updateButton(currentstate);
            //if(previousstate)
        }
        else
        {
            currentstate = previousstate;
            updateButton(currentstate);
            linkedRbButton->flagclicked(0);
            //if(currentstate == BOMB)
            linkedRbButton->setIcon(QIcon(":/images/Assets/cell.png"));
        }
    }
    printf("doing right logic\n");
}

void LogicButton::doLeftLogic()
{
    //int nextx, nexty;
    printf("doing left logic\n");
    //if(current)
    if(currentstate == BOMB)
    {
        updateButton(currentstate);
    }
    if(currentstate == EMPTY)
    {
        currentstate = OPENED;
        updateButton(currentstate);
    }
}
