#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>
#include "Global.h"

class Options
{
    friend class OptionsReader;
    friend class CommandCentre;
public:
    Options();
    ~Options() { }

    int getPort() { return port; }
    std::string getNick() { return nick; }
    QString getChannel() { return channel; }
    QString getServer() { return server; }

    bool displayConnections() { return display_connections; }

private:
    int port;
    std::string nick;
    QString channel;
    QString server;

    bool display_connections;
};

#endif // OPTIONS_H
