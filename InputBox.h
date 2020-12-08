#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QTextEdit>
#include <QKeyEvent>

#include "Global.h"

class InputBox : public QTextEdit
{
    Q_OBJECT
public:
    InputBox(QWidget* parent);
    void keyPressEvent(QKeyEvent* event);

public slots:
    void buttonClicked();

signals:
    void newMessageIB(QString& message, GLOBAL::Dest dest);
    void newMessageIB(QString message);

private:
    QString prevMessage;
};

#endif // INPUTBOX_H
