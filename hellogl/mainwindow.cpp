#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *menuBar = new QMenuBar();
    QMenu *fileMenu = menuBar->addMenu("&File");
    QAction *exitAction = fileMenu->addAction("E&xit");

    exitAction->setShortcut(QKeySequence("Ctrl+q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    //    here is nothing showed on OSX because  File->Exit collapses with System menu, it's automatically hiden
    setMenuBar(menuBar);

    //    a way to write with conveniece function, again, nothing showed because it's taken by OS X System
    menuBar->addMenu("&Help")->addAction("&About", this, SLOT(showAboutBox()), QKeySequence("Ctrl+a"));

    this->glWidget = new GLWidget();

    setCentralWidget(glWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showAboutBox()
{
    QString txt = "";
    txt = txt + "majorVersion" + QString::number(this->glWidget->format().majorVersion()) + "\n";
    txt = txt + "minor version: " + QString::number(this->glWidget->format().minorVersion()) + "\n";
    txt = txt + "Profile: ";
    switch (this->glWidget->format().profile())
    {
    case QSurfaceFormat::OpenGLContextProfile::CoreProfile:
        txt = txt + "CoreProfile";
        break;
    case QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile:
        txt = txt + "CompatibilityProfile";
        break;
    default:
        txt = txt + "NoProfile";
    }

    QMessageBox::information(this, "About Hello GL", txt);
}
