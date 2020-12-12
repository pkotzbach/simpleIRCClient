#ifndef OPTIONSREADER_H
#define OPTIONSREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include "Options.h"
#include "Global.h"

class OptionsReader : public QObject
{
    Q_OBJECT
public:
    explicit OptionsReader(QObject *parent = nullptr);
    void setOptions(Options* op) { options = op; }
    void readOptions();
    void applyOptions(QString& data);

signals:

private:
    QFile* file;
    Options* options;

    const int buffor_size = 1024;
    const QString file_name = "options.txt";
};

#endif // OPTIONSREADER_H
