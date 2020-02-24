#include "mainwindow.h"
#include <QMdiArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_mdiArea(new QMdiArea(this))
{
    this->setCentralWidget(m_mdiArea);
}

MainWindow::~MainWindow()
{

}
