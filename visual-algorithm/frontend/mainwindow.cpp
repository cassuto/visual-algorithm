#include <QMdiArea>
#include <QStatusBar>
#include <QDebug>
#include "formalgorithmmenu.h"
#include "formalgorithmview.h"
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

void MainWindow::createAlgorithmForm(class IModule *module)
{
    FormAlgorithmView *datio = new FormAlgorithmView(module);
    m_mdiArea->addSubWindow(datio);
    datio->show();
}
