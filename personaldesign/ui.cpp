#include "ui.h"

UI::UI()
{
    mline  =new QLineEdit(this);

    mline->resize(240,30);
    mline->move(10,10);
    mline->setAlignment(Qt::AlignRight);
    mline->setReadOnly(1);

    this->setWindowTitle("计算器");
}
