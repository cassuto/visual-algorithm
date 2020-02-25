#include "modelhanoiimpl.h"

ModelHanoiImpl::ModelHanoiImpl()
{
}

/**
  * IModel接口实现
  * 接口定义详见 ../frontend/include/imodule.h
  */

QWidget *ModelHanoiImpl::createInputWidget(QWidget * parent)
{
    return new QWidget(parent);
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
