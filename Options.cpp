#include "Options.h"

Options::Options()
{
    port = 6667;
    nick = GLOBAL::default_nick;
    channel = "";
    server = "aaa";

    display_connections = false;
}
