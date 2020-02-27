#include <QMdiArea>
#include <QStatusBar>
#include <QDebug>
#include <QMenuBar>
#include "formalgorithmmenu.h"
#include "mainwindow.h"

MainWindow *MainWindow::m_instance = 0l;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_mdiArea(new QMdiArea(this))
{
    this->setCentralWidget(m_mdiArea);
    this->statusBar()->show();

    m_formAlgorithmMenu = new FormAlgorithmMenu(m_mdiArea);

    m_mdiArea->addSubWindow(m_formAlgorithmMenu, Qt::WindowTitleHint);
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *)
{
    exit(0);
}
