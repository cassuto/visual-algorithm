#include <QPushButton>
#include <QFormLayout>
#include <QSpinBox>
#include "modelgraphimpl.h"

ModelGraphImpl::ModelGraphImpl(QObject *parent)
    : QObject(parent),
      m_maxNumNodes(256),
      m_pageDin(new QWidget()),
      m_pageDout(new QWidget())
{
    createDataInputPage();
    createDataOutputPage();
}

/**
 * @brief ModelGraphImpl::createDataInputPage
 * 创建Data Input页面控件
 */
void ModelGraphImpl::createDataInputPage()
{
    QFormLayout *layout = new QFormLayout(m_pageDin);

    m_spinNumNodes = new QSpinBox(m_pageDin);
    m_spinNumNodes->setMaximum(m_maxNumNodes);
    m_spinNumNodes->setMinimum(1);
    layout->addWidget(m_spinNumNodes);
    QPushButton *btnCreate = new QPushButton(QIcon(":/new/icons/assets/creategraph.png"), tr("Create Graph"), m_pageDin);
    connect(btnCreate, SIGNAL(pressed()), this, SLOT(onBtnCreatePressed()));
    layout->addWidget(btnCreate);

    m_spinStart = new QSpinBox(m_pageDin);
    m_spinStart->setMaximum(m_maxNumNodes);
    m_spinStart->setMinimum(1);
    layout->addWidget(m_spinStart);
    m_spinEnd = new QSpinBox(m_pageDin);
    m_spinEnd->setMaximum(m_maxNumNodes);
    m_spinEnd->setMinimum(1);
    layout->addWidget(m_spinEnd);
    QPushButton *btnAdd = new QPushButton(QIcon(":/new/icons/assets/add.png"), tr("add edge"), m_pageDin);
    connect(btnAdd, SIGNAL(pressed()), this, SLOT(onBtnAddEdgePressed()));
    layout->addWidget(btnAdd);
}

/**
 * @brief ModelGraphImpl::createDataOutputPage
 * 创建Data Output页面控件
 */
void ModelGraphImpl::createDataOutputPage()
{
    QVBoxLayout *layout = new QVBoxLayout(m_pageDout);

}

/**
 * @brief onBtnCreatePressed 建图按钮单击信号槽
 */
void ModelGraphImpl::onBtnCreatePressed()
{
    clear();
    addNodes(m_spinNumNodes->value());
}

QWidget *ModelGraphImpl::getInputWidget(QWidget *parent) {
    m_pageDin->setParent(parent);
    return m_pageDin;
}
QWidget *ModelGraphImpl::getOutputWidget(QWidget *parent) {
    m_pageDout->setParent(parent);
    return m_pageDout;
}

/**
 * @brief onBtnAddEdgePressed 建边按钮单击信号槽
 */
void ModelGraphImpl::onBtnAddEdgePressed()
{
    int u = m_spinStart->value(), v = m_spinEnd->value();
    addEdge(u,v, 0.5);
}

/**
  * IModelGraph 接口实现
  * 接口定义详见 ../frontend/include/imodule.h
  */

void ModelGraphImpl::addEdge(int u, int v, double val)
{

}

void ModelGraphImpl::removeEdge(int u, int v)
{

}

void ModelGraphImpl::addNodes(int count)
{

}

void ModelGraphImpl::clear()
{

}
