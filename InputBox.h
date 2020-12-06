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

public slots:
    void buttonClicked();

signals:
    void newMessageIB(QString& message, GLOBAL::Dest dest);
    void newMessageIB(QString message);

};

#endif // INPUTBOX_H
