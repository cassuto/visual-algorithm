#include <QFormLayout>
#include <QLayout>
#include <QTableWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QDebug>
#include "modelchessboximpl.h"

ModelChessBoxImpl::ModelChessBoxImpl(QObject *parent)
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
void ModelChessBoxImpl::createDataInputPage()
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

    connect(m_spinNumRows, SIGNAL(valueChanged(int)), this, SLOT(slotSpinNumRowsChanged(int)));
    connect(m_spinNumCols, SIGNAL(valueChanged(int)), this, SLOT(slotSpinNumColsChanged(int)));

    layout->addRow(tr("Columns"), m_spinNumCols);
    m_spinMagX = new QSpinBox(m_pageDin);
    m_spinMagX->setMaximum(m_maxColSize);
    m_spinMagX->setMinimum(1);
    m_spinMagX->setValue(5);
    layout->addRow(tr("MagX"), m_spinMagX);
    m_spinMagY = new QSpinBox(m_pageDin);
    m_spinMagY->setMaximum(m_maxRowSize);
    m_spinMagY->setMinimum(1);
    m_spinMagY->setValue(5);
    layout->addRow(tr("MagY"), m_spinMagY);
    QPushButton *btnGen = new QPushButton(QIcon(":/new/icons/assets/creategraph.png"), tr("Generate"), m_pageDin);
    layout->addWidget(btnGen);

    connect(btnGen, SIGNAL(pressed()), this, SLOT(slotRandomGenInput()));
}

/**
 * @brief ModelMatrixImpl::createDataOutputPage
 * 创建Data Output页面控件
 */
void ModelChessBoxImpl::createDataOutputPage()
{
    QVBoxLayout *layout = new QVBoxLayout(m_pageDout);
    m_matrixTable = new QTableWidget(m_pageDout);
    updateMatrixLayout();
    layout->addWidget(m_matrixTable);
    slotRandomGenInput();
}

QWidget *ModelChessBoxImpl::getInputWidget(QWidget * parent)
{
    m_pageDin->setParent(parent);
    return m_pageDin;
}

QWidget *ModelChessBoxImpl::getOutputWidget(QWidget * parent)
{
    m_pageDout->setParent(parent);
    return m_pageDout;
}

void ModelChessBoxImpl::setEna(bool enabled)
{
    m_pageDin->setEnabled(enabled);
}

void ModelChessBoxImpl::slotSpinNumRowsChanged(int v)
{
    m_rows = v;
    m_spinMagY->setMaximum(v);
}
void ModelChessBoxImpl::slotSpinNumColsChanged(int v)
{
    m_cols = v;
    m_spinMagX->setMaximum(v);
}

void ModelChessBoxImpl::slotRandomGenInput()
{
    m_cols = m_spinNumCols->value();
    m_rows = m_spinNumRows->value();
    m_spinMagX->setValue((rand()%m_cols)+1);
    m_spinMagY->setValue((rand()%m_rows)+1);
    updateMatrixLayout();

    for(int i=1;i<=m_rows;++i)
        for(int j=1;j<=m_cols;++j) {
            setElement(i, j, ((i==m_spinMagY->value()) && (j==m_spinMagX->value())) ? 0 : -1);
        }
}

void ModelChessBoxImpl::updateMatrixLayout()
{
    m_matrixTable->setRowCount(m_spinNumRows->value());
    m_matrixTable->setColumnCount(m_spinNumCols->value());
    for(int i=0;i<m_spinNumCols->value(); ++i) {
        m_matrixTable->setColumnWidth(i, m_matrixColWidth);
    }
    for(int i=0;i<m_maxColors;++i) {
        m_colors[i].setRed(rand()%255);
        m_colors[i].setGreen(rand()%255);
        m_colors[i].setBlue(rand()%255);
    }
    for(int i=1;i<=m_rows;++i)
        for(int j=1;j<=m_cols;++j) {
             m_matrixTable->setCellWidget(i-1, j-1, &m_colorWidgets[i][j]);
        }
}

int ModelChessBoxImpl::getNumRows() const
{
    return m_rows;
}
int ModelChessBoxImpl::getNumColumns() const
{
    return m_cols;
}
int ModelChessBoxImpl::getMagX() const
{
    return m_spinMagX->value();
}
int ModelChessBoxImpl::getMagY() const
{
    return m_spinMagY->value();
}
int ModelChessBoxImpl::getElement(int row, int col) const
{
    return m_matrix[row][col];
}
void ModelChessBoxImpl::setElement(int row, int col, int value)
{
    m_matrix[row][col] = value;
    if(m_matrix[row][col] == -1)
        m_colorWidgets[row][col].m_color = QColor(255,255,255);
    else
        m_colorWidgets[row][col].m_color = m_colors[value];
    m_colorWidgets[row][col].update();
}
