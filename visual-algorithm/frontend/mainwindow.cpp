#include <QMdiArea>
#include <QStatusBar>
#include "formalgorithmmenu.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_mdiArea(new QMdiArea(this))
{
    this->setCentralWidget(m_mdiArea);
    this->statusBar()->show();

    m_formAlgorithmMenu = new FormAlgorithmMenu();

    m_mdiArea->addSubWindow(m_formAlgorithmMenu, Qt::WindowTitleHint);
}

MainWindow::~MainWindow()
{

}
