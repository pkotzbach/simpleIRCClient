#include "ConnectionManager.h"
#include "Global.h"

ConnectionManager::ConnectionManager()
{
    options.channel = "";
    socket = new QTcpSocket(this);
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=]() { writeToSocket("PING ping"); });
    timer->start(100000);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));

    connect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    connect(
        socket, &QTcpSocket::stateChanged,
        [=](QAbstractSocket::SocketState socketState) { qDebug() << "STATE:" << socketState; }
    );
}

//FIXME!!!! this is bad
void ConnectionManager::receiveCommand(QString command, QString argument)
{
    //FIXME: i don't think that doing it this way is proper
    if (command.compare(QString("connect")) == 0 || command.compare(QString("c")) == 0){
        if (checkIP(argument)) {
            connectToHost(argument, GLOBAL::defaultPort);
        }
        else emit CMError(QString("Invalid IP"));
    }
    else if (command.compare(QString("disconnect")) == 0){
        socket->disconnectFromHost();
        socket->waitForDisconnected();
    }
    else if (command.compare(QString("join")) == 0){
        options.channel = argument;
        emit optionsChanged(options);

        writeToSocket(command + " " + argument);
    }
    else if (command.compare(QString("ping")) == 0){
        writeToSocket(command + " " + argument);
    }
    else if (command.compare(QString("unban")) == 0)
        writeToSocket("privmsg candide unbanme");

    else emit CMError(QString("Invalid command"));
}

void ConnectionManager::receiveMessage(QString message, GLOBAL::Dest dest)
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

void ConnectionManager::writeToSocket(QString message)
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
}

void ConnectionManager::connectToHost(QString ip, int port)
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
