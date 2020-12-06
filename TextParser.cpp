#include "TextParser.h"
#include "Global.h"
#include <QRegularExpression>

TextParser::TextParser()
{
    options.channel = ""; //FIXME: GLOBAL::defaultchannel
}

void TextParser::transportMessage(QString message, GLOBAL::Dest dest)
{
    if (message.size() > 0)
    {
        if (dest == GLOBAL::Dest::in) prepAndSendIn(message);
        else if (dest == GLOBAL::Dest::out) prepAndSendOut(message);
    }
    //else do nothing i guess
}

void TextParser::prepAndSendIn(QString input)
{
    if (input.startsWith(GLOBAL::commandChar)) {
        input.remove(0, 1);
        auto parts = input.split(QString(" "), Qt::SkipEmptyParts);

        if (parts.size() == 2)
            emit commandSend(parts[0], parts[1]);
        //FIXME: else
    }
    else {
        input.prepend(QString("privmsg ") + options.channel + QString(" :")); //FIXME
        emit messageSendIn(input, GLOBAL::Dest::in);
    }
}

void TextParser::prepAndSendOut(QString message)
{
    //FIXME: it can make errors i think
    if (message.contains("PRIVMSG")) {
        QRegularExpression re("(?<=\\:)(.*?)(?=\\!)"); //get nick
        QRegularExpression re1("(?<=" + options.channel + ").*"); //get message
        message = "<" + re.match(message).captured() + ">" + re1.match(message).captured().remove(0, 2).prepend(": ");
    }
    emit messageSendOut(message, GLOBAL::Dest::out);
}


void TextParser::getOptions(GLOBAL::Options options)
{
    this->options = options;
    //debug print
    qDebug() << "CHANNEL: " << options.channel;
}
