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

private:
    int port;
    std::string nick;
    QString channel;
    QString server;
};

#endif // OPTIONS_H
