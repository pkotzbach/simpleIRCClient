#ifndef COMMANDCENTRE_H
#define COMMANDCENTRE_H

#include <QObject>
#include "MainWidget.h"
#include "ConnectionManager.h"

class CommandCentre : public QObject
{
    Q_OBJECT
public:
    CommandCentre(MainWidget* mw, ConnectionManager* cm);
    void setOptions(Options* o) { options = o; }

public slots:
    void receiveCommand(QStringList& commandList, QString& fullCommand);

private:
    bool isEnteredCommand(std::string command) { return entered_command.compare(QString(&command[0])) == 0; }

    MainWidget* main_widget;
    ConnectionManager* connection_manager;
    Options* options;
    QString entered_command;
};

#endif // COMMANDCENTRE_H
