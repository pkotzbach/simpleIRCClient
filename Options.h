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

private:
    int port;
    std::string nick;
    QString channel;
};

#endif // OPTIONS_H
