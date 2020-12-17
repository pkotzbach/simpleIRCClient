#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new MainWidget(this));
    setGeometry(0, 0, width, height);
    setMinimumSize(width, height);
    setMaximumSize(width, height);

    setStatusBar(new QStatusBar(this));
    socketStateChanged(QAbstractSocket::SocketState::UnconnectedState);
}

MainWindow::~MainWindow()
{
}

void MainWindow::socketStateChanged(int socketState)
{
    switch (socketState) {
    case QAbstractSocket::SocketState::UnconnectedState:
        statusBar()->showMessage(QString("Unconnected"));
        break;

    case QAbstractSocket::SocketState::ConnectingState:
        statusBar()->showMessage(QString("Connecting"));
        break;

    case QAbstractSocket::SocketState::ConnectedState:
        statusBar()->showMessage(QString("Connected to " + options->getServer()));
        break;

    default:
        break;
    }
}
