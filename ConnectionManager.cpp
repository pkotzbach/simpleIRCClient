#include "ConnectionManager.h"
#include "Global.h"

ConnectionManager::ConnectionManager()
{
    options.channel = "";
    socket = new QTcpSocket(this);
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=]() { writeToSocket(sPing); });
    timer->start(100000);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));

    connect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    connect(
        socket, &QTcpSocket::stateChanged,
        [=](QAbstractSocket::SocketState socketState) { qDebug() << "STATE:" << socketState; }
    );
}

void ConnectionManager::receiveCommand(QStringList& commandList, QString& command)
{
    if (commandList.at(0).compare(QString("connect")) == 0 || commandList.at(0).compare(QString("c")) == 0){
        if (checkIP(commandList.at(1))) {
            connectToHost(commandList.at(1), GLOBAL::defaultPort);
        }
        else emit CMError(sError);
    }
    else if (commandList.at(0).compare(QString("disconnect")) == 0){
        socket->disconnectFromHost();
        socket->waitForDisconnected();
    }
    else if (commandList.at(0).compare(QString("join")) == 0){
        options.channel = commandList.at(1);
        emit optionsChanged(options);

        writeToSocket(command);
    }
    else writeToSocket(command);
}

void ConnectionManager::receiveMessage(QString& message, GLOBAL::Dest dest)
{
    if (dest == GLOBAL::Dest::out) emit newMessageOut(message, GLOBAL::Dest::out);
    if (dest == GLOBAL::Dest::in && socket->isWritable()) writeToSocket(message);
}

void ConnectionManager::readFromSocket()
{
    //that is very slow, but that is IRC client, so it doesn't really matter
    while (!socket->atEnd()) {
        QByteArray data = socket->readLine(bufforSize);
        QString output(data);
        receiveMessage(output, GLOBAL::Dest::out);
//        qDebug() << output;
    }
}

void ConnectionManager::writeToSocket(QString& message)
{
    //in case we forgot to check
    if (socket->isWritable()){
        std::string mes = message.toStdString();
        mes += "\n\r";
        char *buffor;
        buffor = &mes[0];

        int a;
        a = socket->write(buffor);
        socket->waitForBytesWritten();
        qDebug() << socket->bytesToWrite();
        qDebug() << "WRITTEN" << a << "BYTES";
    }
    else emit CMError(sError);
}

void ConnectionManager::connectToHost(const QString& ip, int port)
{
    socket->connectToHost(ip, port);
    socket->waitForConnected();
    socket->write(&std::string("NICK " + GLOBAL::nick + "\r\n")[0]); //a bit tricky, but i wanna have char array here, tbh i don't know why this is working
    socket->write("USER IRCIRC * * :IRCIRC\r\n");
}


void ConnectionManager::handleError(QAbstractSocket::SocketError error)
{
    qDebug() << "ERROR:" << error;
}
