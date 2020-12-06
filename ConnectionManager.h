#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QTimer>
#include <QTcpSocket>

#include "Global.h"

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    ConnectionManager();
    ~ConnectionManager() { }
    static const int bufforSize = 1024;

public slots:
    void receiveCommand(QStringList commandList, QString command);
    void receiveMessage(QString message, GLOBAL::Dest dest);

private slots:
    void handleError(QAbstractSocket::SocketError error);
    void readFromSocket();

signals:
    void CMError(QString error);
    void newMessageOut(QString message, GLOBAL::Dest dest);
    void optionsChanged(GLOBAL::Options options);

private:
    bool checkIP(QString ip) { return 1; } //FIXME
    void connectToHost(QString ip, int port);
    void writeToSocket(QString message);

    GLOBAL::Options options;
    QTcpSocket* socket;
    QTimer* timer;
};

#endif // CONNECTIONMANAGER_H
