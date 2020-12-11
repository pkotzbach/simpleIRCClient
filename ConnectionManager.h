#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QTimer>
#include <QTcpSocket>

#include "Global.h"
#include "Options.h"

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    ConnectionManager();
    ~ConnectionManager() { }

    static const int bufforSize = 1024;

    void setOptions(Options* op) { options = op; }
    void connectToHost(const QString& ip, int port);
    void disconnectFromHost();
    void writeToSocket(QString& message);

public slots:
    void receiveMessage(QString& message, GLOBAL::Dest dest);

private slots:
    void handleError(QAbstractSocket::SocketError error);
    void readFromSocket();

signals:
    void CMError(QString& error);
    void newMessageOut(QString& message, GLOBAL::Dest dest);

private:
    bool checkIP(const QString& ip) { return 1; } //FIXME

    Options* options;
    QTcpSocket* socket;
    QTimer* timer;

    //strings
    QString sPing = "PING ping";
    QString sError = "ERROR"; //FIXME
};

#endif // CONNECTIONMANAGER_H
