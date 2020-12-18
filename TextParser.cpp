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
    if (message.contains("PRIVMSG") || message.contains("privmsg")) {
        QRegularExpression re("(?<=\\:)(.*?)(?=\\!)"); //get nick
        QRegularExpression re1("(?<=" + options->getChannel() + ").*"); //get message
        message = "<" + re.match(message).captured() + ">" + re1.match(message).captured().remove(0, 2).prepend(": ");
    }

    if (!message.contains("freenode.net :ping")) //FIXME
        emit messageSendOut(message, GLOBAL::Dest::out);
}
