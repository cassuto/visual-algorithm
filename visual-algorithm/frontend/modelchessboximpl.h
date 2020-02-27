#ifndef MODELCHESSBOXIMPL_H
#define MODELCHESSBOXIMPL_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include "imodel.h"

class ModelChessBoxImpl : public QObject, public IModelChessBox
{
    Q_OBJECT
public:
    explicit ModelChessBoxImpl(QObject *parent = 0);

    /**
      * IModel接口实现
      * 接口定义详见 ../frontend/include/imodule.h
      */
    QWidget *getInputWidget(QWidget * parent = 0);
    QWidget *getOutputWidget(QWidget * parent = 0);
    void setEna(bool enabled);
    int getTimeInval() const {
        return 200;
    }

    /**
     * IModelMatrix接口实现
     * 接口定义详见 ../frontend/include/imodule.h
     */
    int getNumRows() const;
    int getNumColumns() const;
    int getMagX() const;
    int getMagY() const;
    int getElement(int row, int col) const;
    void setElement(int row, int col, int value);

protected:
    void createDataInputPage();
    void createDataOutputPage();
    void updateMatrixLayout();

signals:

public slots:
    void slotRandomGenInput();
    void slotSpinNumRowsChanged(int v);
    void slotSpinNumColsChanged(int v);

private:
    class QWidget *m_pageDin;
    class QWidget *m_pageDout;
    class QSpinBox *m_spinNumRows;
    class QSpinBox *m_spinNumCols;
    class QSpinBox *m_spinMagX;
    class QSpinBox *m_spinMagY;
    class QTableWidget *m_matrixTable;
    int m_rows, m_cols;
    int m_matrixColWidth;

    static const int m_maxRowSize = 15;
    static const int m_maxColSize = 15;
    int m_matrix[m_maxRowSize+1][m_maxColSize+1];
    static const int m_maxColors = 10000;
    QColor m_colors[m_maxColors+1];

    class ColorFillWidget : public QWidget
    {
    public:
        ColorFillWidget()
        {}
        void paintEvent(QPaintEvent *) {
            QPainter p(this);
            p.setBrush(m_color);
            p.drawRect(0,0,width(), height());
        }
        QColor m_color;
    };

    ColorFillWidget m_colorWidgets[m_maxRowSize+1][m_maxColSize+1];
};

#endif // MODELCHESSBOXIMPL_H
