#include <QSpinBox>
#include <QLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QPainter>
#include <cstdlib>
#include <algorithm>
#include <qDebug>
#include "modellinearlistimpl.h"

ModelLinearListImpl::ModelLinearListImpl(QObject *parent)
    : QObject(parent),
      m_pageDin(new QWidget()),
      m_pageDout(new QWidget()),
      m_listLen(0)
{
    createDataInputPage();
    createDataOutputPage();
}

ModelLinearListImpl::~ModelLinearListImpl()
{
    delete m_view;
}

/**
 * @brief ModelLinearListImpl::createDataInputPage
 * 创建Data Input页面控件
 */
void ModelLinearListImpl::createDataInputPage()
{
    QFormLayout *layout = new QFormLayout(m_pageDin);
    m_spinNum = new QSpinBox(m_pageDin);
    m_spinNum->setMaximum(m_maxListSize);
    m_spinNum->setMinimum(1);
    m_spinNum->setValue(50);
    layout->addRow(tr("Number"), m_spinNum);
    QPushButton *btnGen = new QPushButton(QIcon(":/new/icons/assets/creategraph.png"), tr("Generate"), m_pageDin);
    layout->addWidget(btnGen);
    m_spinValue = new QSpinBox(m_pageDin);
    layout->addRow(tr("value"), m_spinValue);
    QPushButton *btnAppend = new QPushButton(tr("Append"), m_pageDin);
    layout->addWidget(btnAppend);
    QPushButton *btnClear = new QPushButton(tr("Clear"), m_pageDin);
    layout->addWidget(btnClear);

    connect(btnGen, SIGNAL(pressed()), this, SLOT(slotRandomGenInput()));
    connect(btnAppend, SIGNAL(pressed()), this, SLOT(slotBtnAppendPressed()));
    connect(btnClear, SIGNAL(pressed()), this, SLOT(slotBtnClearPressed()));
}

/**
 * @brief ModelLinearListImpl::createDataOutputPage
 * 创建Data Output页面控件
 */
void ModelLinearListImpl::createDataOutputPage()
{
    QVBoxLayout *layout = new QVBoxLayout(m_pageDout);
    m_view = new LinearWidget(this);
    layout->addWidget(m_view);

    clear();
}

QWidget *ModelLinearListImpl::getInputWidget(QWidget * parent)
{
    m_pageDin->setParent(parent);
    return m_pageDin;
}

QWidget *ModelLinearListImpl::getOutputWidget(QWidget * parent)
{
    m_pageDout->setParent(parent);
    return m_pageDout;
}

void ModelLinearListImpl::slotBtnAppendPressed()
{
    if (m_listLen + 1 < m_maxListSize) {
        setElement(++m_listLen, m_spinValue->value());
        updateView();
    }
}

void ModelLinearListImpl::slotBtnClearPressed()
{
    clear();
}

void ModelLinearListImpl::slotRandomGenInput()
{
    int n = m_spinNum->value();
    m_listLen = 0;
    for(int i=0;i<n;++i) {
        setElement(++m_listLen, /*(rand()&1?1:-1) * */ double(rand())/RAND_MAX * INT_MAX);
    }
    updateView();
}

void ModelLinearListImpl::clear()
{
    m_listMax = 0;
    m_listLen = 0;
    updateView();
}

/**
 * @brief 更新线性表视图
 */
void LinearWidget::paintEvent(QPaintEvent *event)
{
    if(!model->m_listLen) {
        return;
    }
    int barX = 0, barY=0; // 偏移量
    int barWidth = width() / model->m_listLen;
    if(!barWidth) barWidth = 1;
    double barHeightDiv = double(height()) / model->m_listMax;

    QPainter p(this);
    double x=0;
    for(int i=1;i<=model->m_listLen;++i) {
        int h = model->m_list[i] * barHeightDiv;
        //p.drawText(QPoint(barX+x, barY+height()-h), QString::number(model->m_list[i]));
        p.setBrush(QBrush(QColor(rand()%255,rand()%255,rand()%255)));
        p.drawRect(barX+x,barY+height()-h, barWidth, h);
        x += barWidth;
    }
}

void ModelLinearListImpl::updateView()
{
    m_view->update();
}

/**
 * IModelLinearList接口实现
 * 接口定义详见 ../frontend/include/imodule.h
 */

int ModelLinearListImpl::getSize() const
{
    return m_listLen;
}
int ModelLinearListImpl::getElement(int idx) const
{
    return m_list[idx];
}
void ModelLinearListImpl::setElement(int idx, int value)
{
    m_list[idx] = value;
    m_listMax = std::max(m_listMax, value);
    updateView();
}
