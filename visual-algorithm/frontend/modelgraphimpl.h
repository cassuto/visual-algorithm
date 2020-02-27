#ifndef MODELGRAPHIMPL_H
#define MODELGRAPHIMPL_H

#include <QObject>
#include "imodel.h"

/**
 * @brief The IModelGraph class
 * 图论模型（算法无关）
 */
class ModelGraphImpl : public QObject, public IModelGraph
{
    Q_OBJECT
public:
    explicit ModelGraphImpl(QObject *parent = 0);

    /**
      * IModel接口实现
      * 接口定义详见 ../frontend/include/imodule.h
      */
    QWidget *getInputWidget(QWidget * parent = 0);
    QWidget *getOutputWidget(QWidget * parent = 0);

    /**
      * IModelGraph 接口实现
      * 接口定义详见 ../frontend/include/imodule.h
      */
    void addEdge(int u, int v, double val);
    void removeEdge(int u, int v);
    void addNodes(int count);
    void clear();

signals:

public slots:
    void onBtnCreatePressed();
    void onBtnAddEdgePressed();

protected:
    void createDataInputPage();
    void createDataOutputPage();
    void randomGenInput();
    void updateInputEnable();

private:
    int m_maxNumNodes;
    QWidget *m_pageDin;
    QWidget *m_pageDout;
    class QSpinBox *m_spinNumNodes;
    class QSpinBox *m_spinStart, *m_spinEnd;
    class QSpinBox *m_spinWeight;
    class QPushButton *m_btnAddEdge;
    class GraphWidget *m_graph;
};

#endif // MODELGRAPHIMPL_H
