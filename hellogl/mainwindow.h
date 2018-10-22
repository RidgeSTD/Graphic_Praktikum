#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include "gl_widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public slots:
    void showAboutBox();

  private:
    GLWidget *glWidget;
};

#endif // MAINWINDOW_H
