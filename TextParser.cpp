#include "TextParser.h"
#include "Global.h"
#include <QRegularExpression>

TextParser::TextParser()
{
    options = nullptr;
}

void TextParser::transportMessage(QString& message, GLOBAL::Dest dest)
{
    if (message.size() > 0)
    {
        if (dest == GLOBAL::Dest::in) prepAndSendIn(message);
        else if (dest == GLOBAL::Dest::out) prepAndSendOut(message);
    }
    //else do nothing i guess
}

void TextParser::prepAndSendIn(QString& input)
{
    if (input.startsWith(GLOBAL::commandChar)) {
        input.remove(0, 1);

        auto temp = input.split(QString(" "), Qt::SkipEmptyParts);
        emit commandSend(temp, input);
    }
    else {
        input.prepend(QString("PRIVMSG ") + options->getChannel() + QString(" :")); //FIXME
        qDebug() << input;
        emit messageSendIn(input, GLOBAL::Dest::in);
    }
}

void TextParser::prepAndSendOut(QString& message)
{
    //FIXME: it can make errors i think
    if (message.contains("PRIVMSG", Qt::CaseInsensitive)) {
        QRegularExpression re("(?<=\\:)(.*?)(?=\\!)"); //get nick
        QRegularExpression re1("(?<=" + options->getChannel() + ").*"); //get message
        message = "<" + re.match(message).captured() + ">" + re1.match(message).captured().remove(0, 2).prepend(": ");
        emit messageSendOut(message, GLOBAL::Dest::out);
    }

    else if (shouldDisplay(message))
        emit messageSendOut(message, GLOBAL::Dest::out);
}

bool TextParser::shouldDisplay(QString& message)
{
    if (message.contains("PONG", Qt::CaseInsensitive)) return false;
    if (!options->displayConnections() && (message.contains("QUIT", Qt::CaseInsensitive) || message.contains("PART", Qt::CaseInsensitive) || message.contains("JOIN", Qt::CaseInsensitive)))
        return false;

    return true;
}
