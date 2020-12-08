#include "InputBox.h"

InputBox::InputBox(QWidget* parent) : QTextEdit(parent)
{
    setGeometry(10, 510, 500, 40);
}

void InputBox::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Return) {
            //enter
            buttonClicked();
        }
        else if (event->key() == Qt::Key_Up) {
            setPlainText(prevMessage);
            moveCursor(QTextCursor::End);
        }
        else {
            QTextEdit::keyPressEvent(event);
        }
    }

void InputBox::buttonClicked()
{
    if(GLOBAL::debug) {
        qDebug() << "IB::buttonClicked, message:" << toPlainText();
    }

    QString temp(toPlainText());
    prevMessage = temp;

    emit newMessageIB(temp);
    emit newMessageIB(temp, GLOBAL::Dest::in);

    clear();
}
