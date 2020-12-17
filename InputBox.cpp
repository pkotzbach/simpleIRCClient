#include "InputBox.h"

InputBox::InputBox(QWidget* parent) : QTextEdit(parent)
{
    setGeometry(10, 510, 500, 40);
    prevMessagesPos = -1;
}

void InputBox::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Return) {
            //enter
            buttonClicked();
        }
        else if (event->key() == Qt::Key_Up && prevMessagesPos < prevMessages.size() - 1) {
            setPlainText(prevMessages.at(++prevMessagesPos));
            qDebug() << prevMessagesPos;
            moveCursor(QTextCursor::End);
        }
        else if (event->key() == Qt::Key_Down && prevMessagesPos > 0) {
            setPlainText(prevMessages.at(--prevMessagesPos));
            qDebug() << prevMessagesPos;
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
    prevMessages.prepend(temp); //should it be limited?
    prevMessagesPos = -1;

    emit newMessageIB(temp);
    emit newMessageIB(temp, GLOBAL::Dest::in);

    clear();
}
