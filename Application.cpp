#include "Application.h"

Application::Application(int &argc, char **argv)
: QApplication(argc, argv)
{
    //we create stuff in newInstance()
    main_window = nullptr;
    text_parser = nullptr;
    connection_manager = nullptr;
}

Application::~Application()
{
    delete main_window;
    delete text_parser;
    delete connection_manager;
}

void Application::newInstance()
{
    main_window = new MainWindow();

    main_window->show();

    text_parser = new TextParser();
    connection_manager = new ConnectionManager();

    //connections INPUT
    //widget to text parser
    connect(main_window->centralWidget(), SIGNAL(newMessageIn(QString, GLOBAL::Dest)),
            text_parser, SLOT(transportMessage(QString, GLOBAL::Dest)));

    //text parser to connection manager
    connect(text_parser, SIGNAL(commandSend(QStringList, QString)),
            connection_manager, SLOT(receiveCommand(QStringList, QString)));
    connect(text_parser, SIGNAL(messageSendIn(QString, GLOBAL::Dest)),
            connection_manager, SLOT(receiveMessage(QString, GLOBAL::Dest)));

    //connections OUTPUT
    //connection manager to text parser
    connect(connection_manager, SIGNAL(newMessageOut(QString, GLOBAL::Dest)),
            text_parser, SLOT(transportMessage(QString, GLOBAL::Dest)));

    //text parser to widget
    connect(text_parser, SIGNAL(messageSendOut(QString, GLOBAL::Dest)),
            main_window->centralWidget(), SLOT(gotMessage(QString, GLOBAL::Dest)));

    //options from connection manager to text parser
    connect(connection_manager, SIGNAL(optionsChanged(GLOBAL::Options)),
            text_parser, SLOT(getOptions(GLOBAL::Options)));
}
