#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <cstring>
#include "modelhanoiimpl.h"

ModelHanoiImpl::ModelHanoiImpl()
    : m_maxDiskNum(11),
      m_step(0),
      m_pageDin(new QWidget()),
      m_pageDout(new QWidget()),
      m_diskFillColor(new QColor[m_maxDiskNum]),
      m_pillarColor(QColor(128,128,128))
{
    createDataInputPage();
    createDataOutputPage();
}

ModelHanoiImpl::~ModelHanoiImpl()
{
    delete m_diskFillColor;
}

/**
 * @brief ModelHanoiImpl::createDataInputPage
 * 创建Data Input页面控件
 */
void ModelHanoiImpl::createDataInputPage()
{
    QFormLayout *layout = new QFormLayout(m_pageDin);
    QLabel *label = new QLabel(tr("Number of Disks:"), m_pageDin);
    layout->addWidget(label);
    m_spinDiskNum = new QSpinBox(m_pageDin);
    m_spinDiskNum->setMaximum(m_maxDiskNum);
    m_spinDiskNum->setMinimum(1);
    layout->addWidget(m_spinDiskNum);

    // 绑定信号槽
    connect(m_spinDiskNum, SIGNAL(valueChanged(int)), this, SLOT(numDiskValueChanged(int)));
}

/**
 * @brief ModelHanoiImpl::createDataOutputPage
 * 创建Data Output页面控件
 */
void ModelHanoiImpl::createDataOutputPage()
{
    QVBoxLayout *layout = new QVBoxLayout(m_pageDout);
    m_lbStep = new QLabel(tr("Ready..."), m_pageDout);
    layout->addWidget(m_lbStep);
    m_scene = new QGraphicsScene(m_pageDout);
    m_view = new QGraphicsView(m_pageDout);
    layout->addWidget(m_view);

    m_view->setScene(m_scene);
    m_view->viewport()->setFixedSize(1600, 1200);
    // 显示滚动条
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn );
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn );
    // 减少刷新次数
    m_view->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate );
    m_view->setCacheMode(QGraphicsView::CacheBackground );
    // 反锯齿渲染
    m_view->setRenderHint(QPainter::HighQualityAntialiasing);

    // 绘制汉诺塔
    QPen pen;
    pen.setColor(m_pillarColor);
    pen.setWidth(4);
    m_scene->addLine(20,400,160,400, pen);
    m_scene->addLine(90,200,90,400, pen);
    m_scene->addLine(220,400,360,400, pen);
    m_scene->addLine(290,200,290,400, pen);
    m_scene->addLine(420,400,560,400, pen);
    m_scene->addLine(490,200,490,400, pen);
    m_spinDiskNum->setValue(m_maxDiskNum);
}

/**
  * IModel接口实现
  * 接口定义详见 ../frontend/include/imodule.h
  */

QWidget *ModelHanoiImpl::getInputWidget(QWidget * parent)
{
    m_pageDin->setParent(parent);
    return m_pageDin;
}

QWidget *ModelHanoiImpl::getOutputWidget(QWidget * parent)
{
    m_pageDout->setParent(parent);
    return m_pageDout;
}

/**
 * IModelHanoi接口实现
 * 接口定义详见 ../frontend/include/imodule.h
 */

int ModelHanoiImpl::getDisksNum() const
{
    return m_numDisks;
}

static int toPillarIndex(char ch)
{
    switch(ch) {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    default: return 0;
    }
}

void ModelHanoiImpl::moveTop(char src, char dst)
{
    int a=toPillarIndex(src), b=toPillarIndex(dst);
    --m_pillar[a];
    ++m_pillar[b];
    updateStep();
}

void ModelHanoiImpl::updateStep()
{
    m_lbStep->setText(QString(tr("step %1")).arg(m_step));
    updateDisk(false);
}

void ModelHanoiImpl::updateDisk(bool reset)
{
    if(reset) {
        // 随机生成圆盘填充色
        for(int i=0;i<m_numDisks;++i) {
            m_diskFillColor[i].setRed(double(rand())/RAND_MAX*255);
            m_diskFillColor[i].setGreen(double(rand())/RAND_MAX*255);
            m_diskFillColor[i].setBlue(double(rand())/RAND_MAX*255);
        }
    }

    foreach(QGraphicsItem *item, m_graphItems) {
        m_scene->removeItem(item);
    }
    m_graphItems.clear();

    const int diskHeight = 14;

    // 按照圆盘数绘制塔柱
    for(int p=1;p<=3;++p) {
        for(int n=1;n<=m_pillar[p-1];++n) {
            int x0 = (p-1)*200+(m_numDisks-n)*(diskHeight/2)+diskHeight;
            int x1 = (p-1)*200+166-(m_numDisks-n)*(diskHeight/2);
            int y0 = 390-(m_numDisks-n+1)*diskHeight;
            int w = x1-x0+1;
            QGraphicsRectItem *rect = new QGraphicsRectItem(x0, y0, w, diskHeight);
            rect->setBrush(QBrush(QColor(rand()%255,rand()%255,rand()%255)));
            m_scene->addItem(rect);
            m_graphItems.append(rect);
        }
    }
}

void ModelHanoiImpl::numDiskValueChanged(int i)
{
    m_numDisks = m_spinDiskNum->value();
    m_pillar[0] = m_numDisks;
    m_pillar[1] = 0;
    m_pillar[2] = 0;
    updateDisk(true);
}
