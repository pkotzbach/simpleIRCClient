#ifndef COMMANDCENTRE_H
#define COMMANDCENTRE_H

#include <QObject>
#include "MainWidget.h"
#include "ConnectionManager.h"

class CommandCentre : public QObject
{
    Q_OBJECT
public:
    CommandCentre(MainWidget* mw, ConnectionManager* cm) { main_widget = mw; connection_manager = cm; options = nullptr;}
    void setOptions(Options* o) { options = o; }

public slots:
    void receiveCommand(QStringList& commandList, QString& command);

private:
    MainWidget* main_widget;
    ConnectionManager* connection_manager;
    Options* options;
};

#endif // COMMANDCENTRE_H
