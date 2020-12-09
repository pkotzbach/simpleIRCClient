#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>

class Options
{
    friend class ConnectionManager;
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
