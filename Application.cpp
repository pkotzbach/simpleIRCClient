#include "Application.h"

Application::Application(int &argc, char **argv)
: QApplication(argc, argv)
{
    //we create stuff in newInstance()
    main_window = nullptr;
    text_parser = nullptr;
    connection_manager = nullptr;
    options = nullptr;
    command_centre = nullptr;
}

Application::~Application()
{
    delete main_window;
    delete text_parser;
    delete connection_manager;
    delete options;
    delete command_centre;
}

void Application::newInstance()
{
    main_window = new MainWindow();

    main_window->show();

    text_parser = new TextParser();
    connection_manager = new ConnectionManager();
    command_centre = new CommandCentre(static_cast<MainWidget*>(main_window->centralWidget()), connection_manager);

    //options
    options = new Options();
    text_parser->setOptions(options);
    connection_manager->setOptions(options);
    command_centre->setOptions(options);
    static_cast<MainWidget*>(main_window->centralWidget())->setOptions(options);


    //connections INPUT
    //input box to text parser
    connect(static_cast<MainWidget*>(main_window->centralWidget())->getInputBox(), SIGNAL(newMessageIB(QString&, GLOBAL::Dest)),
            text_parser, SLOT(transportMessage(QString&, GLOBAL::Dest)));

    //text parser to command centre
    connect(text_parser, SIGNAL(commandSend(QStringList&, QString&)),
            command_centre, SLOT(receiveCommand(QStringList&, QString&)));

    //text parser to connection manager
    connect(text_parser, SIGNAL(messageSendIn(QString&, GLOBAL::Dest)),
            connection_manager, SLOT(receiveMessage(QString&, GLOBAL::Dest)));

    //connections OUTPUT
    //connection manager to text parser
    connect(connection_manager, SIGNAL(newMessageOut(QString&, GLOBAL::Dest)),
            text_parser, SLOT(transportMessage(QString&, GLOBAL::Dest)));

    //text parser to widget
    connect(text_parser, SIGNAL(messageSendOut(QString&, GLOBAL::Dest)),
            main_window->centralWidget(), SLOT(gotMessage(QString&, GLOBAL::Dest)));
}
