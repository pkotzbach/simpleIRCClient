#include "CommandCentre.h"

void CommandCentre::receiveCommand(QStringList& commandList, QString& command)
{
    if (commandList.at(0).compare(QString("clear")) == 0 ) {
        main_widget->getChatBox()->clear();
    }
    else if (commandList.at(0).compare(QString("connect")) == 0 || commandList.at(0).compare(QString("c")) == 0){
        if (commandList.size() > 1) connection_manager->connectToHost(commandList.at(1), options->getPort());
    }
    else if (commandList.at(0).compare(QString("disconnect")) == 0){
        connection_manager->disconnectFromHost();
    }
    else if (commandList.at(0).compare(QString("join")) == 0){
        if (commandList.size() > 1) options->channel = commandList.at(1);
        connection_manager->writeToSocket(command);
    }
    else if (commandList.at(0).compare(QString("nick")) == 0){
        if (commandList.size() > 1) options->nick = commandList.at(1).toStdString();
        connection_manager->writeToSocket(command);
    }
    else connection_manager->writeToSocket(command);
}
