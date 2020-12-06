#include "InputBox.h"

InputBox::InputBox(QWidget* parent) : QTextEdit(parent)
{
    setGeometry(10, 510, 500, 40);
}

void InputBox::buttonClicked()
{
    if(GLOBAL::debug) {
        qDebug() << "IB::buttonClicked, message:" << toPlainText();
    }

    emit newMessageIB(toPlainText(), GLOBAL::Dest::in);

    clear();
}
