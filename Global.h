#pragma once

#include <QDebug>

namespace GLOBAL
{
    const char commandChar = '/';
    const bool debug = 1;

    const int defaultPort = 6667;
    const std::string nick = "IRCIRCIRC";

    enum Dest {in, out};

    struct Options
    {
        QString channel;
    };
}
