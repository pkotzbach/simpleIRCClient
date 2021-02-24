#include "CommandCentre.h"
#include "OptionsReader.h"

CommandCentre::CommandCentre(MainWidget* mw, ConnectionManager* cm)
{
    main_widget = mw;
    connection_manager = cm;
    options = nullptr;
}

void CommandCentre::receiveCommand(QStringList& commandList, QString& fullCommand)
{
    entered_command = commandList.at(0);

    if (isEnteredCommand("clear")) {
        main_widget->getChatBox()->clear();
    }
    else if (isEnteredCommand("connect") || isEnteredCommand("c")){
        if (commandList.size() > 1) {
            if (connection_manager->isConnected())
                connection_manager->disconnectFromHost();

            options->server = commandList.at(1);
            connection_manager->connectToHost(commandList.at(1), options->getPort());
        }
    }
    else if (isEnteredCommand("disconnect") || isEnteredCommand("dc")){
        connection_manager->disconnectFromHost();
    }
    else if (isEnteredCommand("join")){
        if (commandList.size() > 1) options->channel = commandList.at(1);
        connection_manager->writeToSocket(fullCommand);
    }
    else if (isEnteredCommand("nick")){
        if (commandList.size() > 1) options->nick = commandList.at(1).toStdString();
        connection_manager->writeToSocket(fullCommand);
    }
    else connection_manager->writeToSocket(fullCommand);
}
