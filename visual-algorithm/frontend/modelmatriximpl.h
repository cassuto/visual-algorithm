#ifndef MODELMATRIXIMPL_H
#define MODELMATRIXIMPL_H

#include <QObject>
#include "imodel.h"

class ModelMatrixImpl : public QObject, public IModelMatrix
{
    Q_OBJECT
public:
    explicit ModelMatrixImpl(QObject *parent = 0);

    /**
      * IModel接口实现
      * 接口定义详见 ../frontend/include/imodule.h
      */
    QWidget *getInputWidget(QWidget * parent = 0);
    QWidget *getOutputWidget(QWidget * parent = 0);

    /**
     * IModelMatrix接口实现
     * 接口定义详见 ../frontend/include/imodule.h
     */
    int getNumRows() const;
    int getNumColumns() const;
    int getElement(int row, int col) const;
    void setElement(int row, int col, int value);

protected:
    void createDataInputPage();
    void createDataOutputPage();
    void updateMatrixLayout();

signals:

public slots:
    void slotRandomGenInput();

private:
    class QWidget *m_pageDin;
    class QWidget *m_pageDout;
    class QSpinBox *m_spinNumRows;
    class QSpinBox *m_spinNumCols;
    class QTableWidget *m_matrixTable;
    int m_rows, m_cols;
    int m_matrixColWidth;

    static const int m_maxRowSize = 1024;
    static const int m_maxColSize = 1024;
    int m_matrix[m_maxRowSize][m_maxColSize];
};

#endif // MODELMATRIXIMPL_H
