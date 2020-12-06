#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "MainWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //should it be static const?
    static const int width = 800;
    static const int height = 600;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

};
#endif // MAINWINDOW_H
