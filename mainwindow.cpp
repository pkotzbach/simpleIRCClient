#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new MainWidget(this));
    setGeometry(0, 0, width, height);
    setMinimumSize(width, height);
    setMaximumSize(width, height);
}

MainWindow::~MainWindow()
{
}
