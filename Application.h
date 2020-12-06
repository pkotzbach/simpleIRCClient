#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QPointer>

#include "MainWindow.h"
#include "TextParser.h"
#include "ConnectionManager.h"
#include "Global.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int &argc, char **argv);
    ~Application();

    void newInstance();

private:
    QPointer<MainWindow> main_window;
    QPointer<TextParser> text_parser;
    QPointer<ConnectionManager> connection_manager;
};

#endif // APPLICATION_H
