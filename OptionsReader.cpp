#include "OptionsReader.h"

OptionsReader::OptionsReader(QObject *parent) : QObject(parent)
{
    file = new QFile(file_name, this);
    bool exist = file->exists();
    file->open(QIODevice::ReadWrite); //FIXME: what if it fails?

    if (!exist) {
        qDebug() << "CREATED OPTIONS FILE";
        file->write(&std::string("NICK:" + GLOBAL::default_nick)[0]);
    }

    if (file->exists()) qDebug() << "LOADED OPTIONS FILE";
}

void OptionsReader::readOptions()
{
    while (!file->atEnd()) {
        QByteArray data = file->readLine(buffor_size);
        QString output(data);
        applyOptions(output);
//        qDebug() << output;
    }
}

void OptionsReader::applyOptions(QString& data)
{
    QString opt(data.split(":").at(0));
    data = data.split(":").at(1).simplified();

    if (opt.compare(QString("NICK")) == 0 ) {
        options->nick = data.toStdString();
    }
}
