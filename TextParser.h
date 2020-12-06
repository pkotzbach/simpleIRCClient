#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include <QObject>
#include "Global.h"

class TextParser : public QObject
{
    Q_OBJECT
public:
    TextParser();
    ~TextParser() { }

public slots:
    void transportMessage(QString& message, GLOBAL::Dest dest);
    void getOptions(GLOBAL::Options options);

signals:
    void commandSend(QStringList& command, QString& argument);
    void messageSendIn(QString& message, GLOBAL::Dest dest);
    void messageSendOut(QString& message, GLOBAL::Dest dest);

private:
    void prepAndSendIn(QString& input);
    void prepAndSendOut(QString& message);

    GLOBAL::Options options;
};

#endif // TEXTPARSER_H
