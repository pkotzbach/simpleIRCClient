#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStatusBar>
#include <QAbstractSocket>

#include "MainWidget.h"
#include "Options.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //should it be static const?
    static const int width = 800;
    static const int height = 600;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setOptions(Options* o) { options = o; }

public slots:
    void socketStateChanged(int socketState);

private:
    Options* options;
};
#endif // MAINWINDOW_H
