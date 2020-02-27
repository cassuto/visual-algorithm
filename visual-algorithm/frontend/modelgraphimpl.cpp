#include <QPushButton>
#include <QFormLayout>
#include <QSpinBox>
#include <QMessageBox>
#include <QLabel>
#include <cstdlib>
#include "graphwidget.h"
#include "modelgraphimpl.h"

ModelGraphImpl::ModelGraphImpl(QObject *parent)
    : QObject(parent),
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
    m_spinNumNodes->setValue(6);
    layout->addRow(tr("n="), m_spinNumNodes);
    QPushButton *btnCreate = new QPushButton(QIcon(":/new/icons/assets/creategraph.png"), tr("Create"), m_pageDin);
    connect(btnCreate, SIGNAL(pressed()), this, SLOT(onBtnCreatePressed()));
    layout->addWidget(btnCreate);

    m_spinStart = new QSpinBox(m_pageDin);
    m_spinStart->setMaximum(m_maxNumNodes);
    m_spinStart->setMinimum(1);
    layout->addRow(tr("u="), m_spinStart);
    m_spinEnd = new QSpinBox(m_pageDin);
    m_spinEnd->setMaximum(m_maxNumNodes);
    m_spinEnd->setMinimum(1);
    layout->addRow(tr("v="), m_spinEnd);
    m_spinWeight = new QSpinBox(m_pageDin);
    m_spinWeight->setValue(1);
    layout->addRow(tr("w="), m_spinWeight);
    m_btnAddEdge = new QPushButton(QIcon(":/new/icons/assets/addedge.png"), tr("Add"), m_pageDin);
    connect(m_btnAddEdge, SIGNAL(pressed()), this, SLOT(onBtnAddEdgePressed()));
    layout->addWidget(m_btnAddEdge);
}

/**
 * @brief ModelGraphImpl::createDataOutputPage
 * 创建Data Output页面控件
 */
void ModelGraphImpl::createDataOutputPage()
{
    QVBoxLayout *layout = new QVBoxLayout(m_pageDout);
    m_result = new QLabel(m_pageDout);
    layout->addWidget(m_result);
    m_graph = new GraphWidget(m_pageDout);
    layout->addWidget(m_graph);
    updateInputEnable();
    layout->setStretch(0,0);
    layout->setStretch(1,1);
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
 * @brief onBtnCreatePressed 建图按钮单击信号槽
 */
void ModelGraphImpl::onBtnCreatePressed()
{
    m_graph->clear();
    addNodes(m_spinNumNodes->value());
    updateInputEnable();
}

/**
 * @brief onBtnAddEdgePressed 建边按钮单击信号槽
 */
void ModelGraphImpl::onBtnAddEdgePressed()
{
    double weight = m_spinWeight->value();
    int u = m_spinStart->value(), v = m_spinEnd->value();
    if(u>m_graph->getNumNodes() || v>m_graph->getNumNodes()) {
        QMessageBox::critical(m_pageDin, tr("input"), tr("Invalid node number."), QMessageBox::Ok);
        return;
    }
    addEdge(u,v, weight);
    randomGenInput();
}

void ModelGraphImpl::updateInputEnable()
{
    bool couldAddEdge = m_graph->getNumNodes() > 0;
    m_spinStart->setEnabled(couldAddEdge);
    m_spinEnd->setEnabled(couldAddEdge);
    m_spinWeight->setEnabled(couldAddEdge);
    m_btnAddEdge->setEnabled(couldAddEdge);
    randomGenInput();
}

/**
 * @brief 随机建边 尽量使连通分量减少
 */
void ModelGraphImpl::randomGenInput()
{
    int retry = 0;
    while(retry++ < m_graph->getNumNodes()<<1) {
        int u = (rand()%m_graph->getNumNodes())+1;
        int v = (rand()%m_graph->getNumNodes())+1;
        if(u!=v && !m_graph->connected(u,v)) {
            m_spinStart->setValue(u);
            m_spinEnd->setValue(v);
            break;
        }
    }
    m_spinWeight->setValue(rand()%m_spinWeight->maximum());
}

/**
  * IModelGraph 接口实现
  * 接口定义详见 ../frontend/include/imodule.h
  */

int ModelGraphImpl::matrix(int u, int v) const
{
    return m_matrix[u][v];
}
int ModelGraphImpl::getNumNodes() const
{
    return m_graph->getNumNodes();
}
int ModelGraphImpl::getNumEdges() const
{
    return m_graph->getNumEdges();
}
int ModelGraphImpl::getWeight(int i) const
{
    return m_graph->getEdge(i)->weight;
}
void ModelGraphImpl::getEndpoints(int i, int *u, int *v) const
{
    *u = m_graph->getEdge(i)->u;
    *v = m_graph->getEdge(i)->v;
}

void ModelGraphImpl::addEdge(int u, int v, int val)
{
    UndirectedEdge edge;
    edge.u = u;
    edge.v = v;
    edge.weight = val;
    m_graph->addEdge(edge);
    m_matrix[u][v]=1;
    m_matrix[v][u]=1;
}

void ModelGraphImpl::setEdgeHighlight(int u, int v)
{
    m_graph->getNode(u)->highlight = true;
    m_graph->getNode(v)->highlight = true;
    m_graph->update();
}

void ModelGraphImpl::addNodes(int count)
{
    GraphNode node;
    int n=m_graph->getNumNodes();
    for(int i=n;i<n+count;++i) {
        node.id = i+1;
        node.color = QColor(rand()%255,rand()%255,rand()%255);
        m_graph->addNode(node);
    }
}

void ModelGraphImpl::addNode(int id)
{
    if(m_graph->getNode(id)) {
        return; // 结点已经存在
    }
    GraphNode node;
    node.id = id;
    node.color = QColor(rand()%255,rand()%255,rand()%255);
    m_graph->addNode(node);
}

void ModelGraphImpl::clear()
{
    for(int i=1;i<=m_graph->getNumNodes(); ++i)
        for(int j=1;j<=m_graph->getNumNodes(); ++j) {
            m_matrix[i][j]=0;
        }
    m_graph->clear();
}

void ModelGraphImpl::setResult(const char *msg)
{
    m_result->setText(msg);
    m_result->adjustSize();
}
