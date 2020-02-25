#include "formalgorithmview.h"

FormAlgorithmView::FormAlgorithmView(IModule *module, QWidget *parent)
    : QWidget(parent),
      m_module(module)
{
    this->setWindowTitle(tr("Algorithm View - ") + QString(module->getName()) + "-" + QString(module->getGroup()));
    this->setFixedSize(100,100);
}

