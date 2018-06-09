#include "rbbutton.h"

int RbButton::getIndex() const
{
    return index;
}

void RbButton::setIndex(int value)
{
    index = value;
}

RbButton::RbButton(QWidget *parent, int index) : QPushButton()

{
    this->index = index;
}
void RbButton::bombopened()
{
    emit bombopened_signal();
}
void RbButton::flagclicked(int i)
{
    emit flagclicked_signal(i);
}
void RbButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
       emit rightclicked(index);
    }
    if(event->button() == Qt::LeftButton)
    {
       emit leftclicked(index);
    }
}

void RbButton::changeColor(QColor color)
{
    QString back_standard_css = "background-color: chocolate;";
    QString back_gray_css = "background-color: gray;";
    QString red_css = "color: red;";
    QString blue_css = "color: blue;";
    QString black_css = "color: black;";
    QString green_css = "color: green;";
    QString current_css = "";

    if(color == Qt::red)
        current_css = red_css + back_standard_css;
    if(color == Qt::blue)
        current_css = blue_css + back_standard_css;
    if(color == Qt::black)
        current_css = black_css + back_standard_css;
    if(color == Qt::green)
        current_css = green_css + back_standard_css;
    //this->setStyleSheet(current_css);

}
