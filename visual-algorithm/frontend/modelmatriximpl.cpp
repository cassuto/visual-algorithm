#include <QFormLayout>
#include <QLayout>
#include <QTableWidget>
#include <QSpinBox>
#include <QPushButton>
#include "modelmatriximpl.h"

ModelMatrixImpl::ModelMatrixImpl(QObject *parent)
    : QObject(parent),
      m_pageDin(new QWidget()),
      m_pageDout(new QWidget()),
      m_rows(0),
      m_cols(0),
      m_matrixColWidth(35)
{
    createDataInputPage();
    createDataOutputPage();
}

/**
 * @brief ModelMatrixImpl::createDataInputPage
 * 创建Data Input页面控件
 */
void ModelMatrixImpl::createDataInputPage()
{
    QFormLayout *layout = new QFormLayout(m_pageDin);
    m_spinNumRows = new QSpinBox(m_pageDin);
    m_spinNumRows->setMaximum(m_maxRowSize);
    m_spinNumRows->setMinimum(1);
    m_spinNumRows->setValue(10);
    layout->addRow(tr("Rows"), m_spinNumRows);
    m_spinNumCols = new QSpinBox(m_pageDin);
    m_spinNumCols->setMaximum(m_maxColSize);
    m_spinNumCols->setMinimum(1);
    m_spinNumCols->setValue(10);
    layout->addRow(tr("Columns"), m_spinNumCols);
    QPushButton *btnGen = new QPushButton(QIcon(":/new/icons/assets/creategraph.png"), tr("Generate"), m_pageDin);
    layout->addWidget(btnGen);

    connect(btnGen, SIGNAL(pressed()), this, SLOT(slotRandomGenInput()));
}

/**
 * @brief ModelMatrixImpl::createDataOutputPage
 * 创建Data Output页面控件
 */
void ModelMatrixImpl::createDataOutputPage()
{
    QVBoxLayout *layout = new QVBoxLayout(m_pageDout);
    m_matrixTable = new QTableWidget(m_pageDout);
    updateMatrixLayout();
    layout->addWidget(m_matrixTable);
}

QWidget *ModelMatrixImpl::getInputWidget(QWidget * parent)
{
    m_pageDin->setParent(parent);
    return m_pageDin;
}

QWidget *ModelMatrixImpl::getOutputWidget(QWidget * parent)
{
    m_pageDout->setParent(parent);
    return m_pageDout;
}

void ModelMatrixImpl::slotRandomGenInput()
{
    m_rows = m_spinNumRows->value();
    m_cols = m_spinNumCols->value();

    updateMatrixLayout();

    for(int i=0;i<m_rows;++i)
        for(int j=0;j<m_cols;++j) {
            m_matrix[i][j] = rand()&1;
        }
}

void ModelMatrixImpl::updateMatrixLayout()
{
    m_matrixTable->setRowCount(m_spinNumRows->value());
    m_matrixTable->setColumnCount(m_spinNumCols->value());
    for(int i=0;i<m_spinNumCols->value(); ++i) {
        m_matrixTable->setColumnWidth(i, m_matrixColWidth);
    }
}

int ModelMatrixImpl::getNumRows() const
{
    return m_rows;
}
int ModelMatrixImpl::getNumColumns() const
{
    return m_cols;
}
int ModelMatrixImpl::getElement(int row, int col) const
{
    return m_matrix[row][col];
}
void ModelMatrixImpl::setElement(int row, int col, int value)
{
    m_matrix[row][col] = value;
}
