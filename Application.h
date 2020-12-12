#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QPointer>

#include "MainWindow.h"
#include "TextParser.h"
#include "ConnectionManager.h"
#include "Global.h"
#include "Options.h"
#include "CommandCentre.h"
#include "OptionsReader.h"

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
    QPointer<CommandCentre> command_centre;
    Options* options; //should it be here?
    QPointer<OptionsReader> options_reader;
};

#endif // APPLICATION_H
