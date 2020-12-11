#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>

#include "InputBox.h"
#include "Global.h"
#include "Options.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QMainWindow* parent = nullptr);
    void setOptions(Options* op) { options = op; }
    InputBox* getInputBox() { return input_box; }
    QTextBrowser* getChatBox() { return chat_box; }

signals:
    void newMessageOut(QString message);

private slots:
    void gotMessage(QString& message, GLOBAL::Dest dest);
    void parseMyNewMessage(QString message);

private:
    QTextBrowser* chat_box;
    InputBox* input_box;
    QPushButton* send_message_button;
    Options* options;
};

#endif // MAINWIDGET_H
