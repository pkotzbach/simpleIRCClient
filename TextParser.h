#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include <QObject>
#include "Global.h"
#include "Options.h"

class TextParser : public QObject
{
    Q_OBJECT
public:
    TextParser();
    ~TextParser() { }
    void setOptions(Options* op) { options = op; }

public slots:
    void transportMessage(QString& message, GLOBAL::Dest dest);

signals:
    void commandSend(QStringList& commandList, QString& fullCommand);
    void messageSendIn(QString& message, GLOBAL::Dest dest);
    void messageSendOut(QString& message, GLOBAL::Dest dest);

private:
    void prepAndSendIn(QString& input);
    void prepAndSendOut(QString& message);

    bool shouldDisplay(QString& message);

    Options* options;
};

#endif // TEXTPARSER_H
