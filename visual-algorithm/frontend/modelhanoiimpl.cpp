#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include "modelhanoiimpl.h"

ModelHanoiImpl::ModelHanoiImpl()
    : m_maxDiskNum(10)
{
}

/**
  * IModel接口实现
  * 接口定义详见 ../frontend/include/imodule.h
  */

QWidget *ModelHanoiImpl::createInputWidget(QWidget * parent)
{
    QWidget *page = new QWidget(parent);
    QFormLayout *layout = new QFormLayout(page);
    QLabel *label = new QLabel(tr("Number of Disks:"), page);
    layout->addWidget(label);
    QSpinBox *spinDiskNum = new QSpinBox(page);
    spinDiskNum->setMaximum(m_maxDiskNum);
    spinDiskNum->setMinimum(1);
    layout->addWidget(spinDiskNum);
    page->setMinimumSize(100,100);
    return page;
}

QWidget *ModelHanoiImpl::createOutputWidget(QWidget * parent)
{
    return new QWidget(parent);
}

/**
 * IModelHanoi接口实现
 * 接口定义详见 ../frontend/include/imodule.h
 */

int ModelHanoiImpl::getDisksNum() const
{
    return 0;
}

void ModelHanoiImpl::moveTop(char src, char dst)
{
}
