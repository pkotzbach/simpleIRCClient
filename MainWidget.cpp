#include "MainWidget.h"
#include "Global.h"
#include <QPushButton>

MainWidget::MainWidget(QMainWindow* parent) : QWidget(parent)
{
    chat_box = new QTextBrowser(this);
    input_box = new InputBox(this);;
    send_message_button = new QPushButton(this);

    //FIXME: should it be in constructor?
    chat_box->setGeometry(10, 10, 780, 490);

    send_message_button->setGeometry(520, 510, 110, 40);
    send_message_button->setText("Wyslij");

    connect(send_message_button, SIGNAL(clicked()), input_box, SLOT(buttonClicked()));
    connect(input_box, SIGNAL(newMessageIB(QString&, GLOBAL::Dest)),
            this, SLOT(gotMessage(QString&, GLOBAL::Dest)));
    connect(input_box, SIGNAL(newMessageIB(QString)),
            this, SLOT(parseMyNewMessage(QString)));

    connect(this, SIGNAL(newMessageOut(QString)),
            chat_box, SLOT(insertPlainText(QString)));
}

void MainWidget::gotMessage(QString& message, GLOBAL::Dest dest)
{
    if (message.compare(QString("/clear")) == 0) chat_box->clear(); //FIXME
    else if (dest == GLOBAL::Dest::in) emit newMessageIn(message, dest);
    else if (dest == GLOBAL::Dest::out) emit newMessageOut(message);
}

//FIXME
void MainWidget::parseMyNewMessage(QString message)
{
    message.prepend(QString::fromStdString("<" + GLOBAL::nick + ">: "));
    message.append("\n");

    emit newMessageOut(message);
}
