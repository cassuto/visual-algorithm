#include <QPainter>
#include <QDebug>
#include <ogdf/basic/GridLayout.h>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <cmath>
#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent),
      m_undirectGraph(false),
      m_aniTimer (new QTimer(this)),
      m_edgeDefaultColor(QColor(50,50,50,200)),
      m_edgeFilteredColor(QColor(200,200,200,100)),
      m_edgeHighlightedColor(QColor(200,100,0,200))
{
    // 初始化动画定时器
    m_aniTimer->setInterval(10);
    connect(m_aniTimer, SIGNAL(timeout()),this, SLOT(slotAniTimer()));

    // 默认参数
    m_viewY=0;
    m_viewX=0;
    m_viewScale=1.0;
    m_nodeRadius=5;
    m_minDegree=0;
    m_edgeWidth=1;
    m_fontSize=11; // pts

    this->setMinimumSize(QSize(GraphNode::OGDF_width, GraphNode::OGDF_height));

    clear();
}

void GraphWidget::clear()
{
    m_nodes.clear();
    m_edges.clear();
    m_aniActive=false;
    m_undirectGraph=false;
    rearrange();
    layout();
}

void GraphWidget::addNode(const GraphNode &node)
{
    m_nodes.append(node);
    m_undirectGraph=true;
    rearrange();
    layout();
}

void GraphWidget::addEdge(const UndirectedEdge &edge)
{
    m_edges.append(edge);
    m_undirectGraph=true;
    rearrange();
    layout();
}

bool GraphWidget::connected(int u, int v)
{
    GraphNode *n_u = getNode(u);
    GraphNode *n_v = getNode(v);
    for(const UndirectedEdge &e: m_edges){
        if( ((e.u==n_u->id) &&(e.v==n_v->id)) ||
            ((e.u==n_v->id) &&(e.v==n_u->id)) )
            return true;
    }
    return false;
}

/**
 * @brief 运行布局算法
 */
void GraphWidget::layout()
{
    ogdf::Graph G;
    for(int i=0;i<m_nodes.size();++i) {
        m_nodes[i].ogdfID = G.newNode(i);
    }
    for(int i=0;i<m_edges.size();++i) {
        G.newEdge(m_edges[i].nodeU->ogdfID,m_edges[i].nodeV->ogdfID);
    }

    // FMMM布局算法
    ogdf::GraphAttributes GA_FMMM(G);
    ogdf::FMMMLayout layout;
    layout.unitEdgeLength(15.0);
    layout.newInitialPlacement(true);
    layout.useHighLevelOptions(true);
    layout.qualityVersusSpeed(ogdf::FMMMLayout::qvsGorgeousAndEfficient);
    layout.call(GA_FMMM);

    ogdf::DRect rect=GA_FMMM.boundingBox();

    // 归一化坐标
    double xk=GraphNode::OGDF_width/rect.width();
    double yk=GraphNode::OGDF_height/rect.height();
    double x0=rect.p1().m_x;
    double y0=rect.p1().m_y;
    for(int i=0;i<m_nodes.size();++i) {
        m_nodes[i].aniX = (GA_FMMM.x(m_nodes[i].ogdfID)-x0)*xk+GraphNode::OGDF_left;
        m_nodes[i].aniY = (GA_FMMM.y(m_nodes[i].ogdfID)-y0)*yk+GraphNode::OGDF_top;
    }
    m_currentAniPhase=0;
    m_aniTimer->start();
    return;
}

/**
 * @brief 通过ID获取结点实例
 * @param id
 * @retval pointer to the instance of node
 * @retval NULL if none
 */
GraphNode* GraphWidget::getNode(int id)
{
    for(int i=0;i<m_nodes.size();++i) {
        if(m_nodes[i].id == id)
            return &m_nodes[i];
    }
    return 0l;
}

/**
 * @brief 维护边与顶点的信息
 */
void GraphWidget::rearrange()
{
    for(int i=0;i<m_edges.size(); ++i) {
        m_edges[i].nodeU=getNode(m_edges[i].u);
        m_edges[i].nodeV=getNode(m_edges[i].v);
    }
}

/**
 * @brief 绘制图
 */
void GraphWidget::paintEvent(QPaintEvent *) {

#define transformX(x) (((x)+m_viewX)*m_viewScale)
#define transformY(y) (((y)+m_viewY)*m_viewScale)
#define transformR(r) ((int)((r)*m_viewScale))

    if(m_undirectGraph) {

        QPainter p(this);

        // 反锯齿渲染
        p.setRenderHint(QPainter::Antialiasing, true);

        // 初始化工具
        QPen pen = p.pen();
        pen.setWidth(1);
        QPalette palette(this->palette());
        p.setBrush(palette.windowText());
        p.setPen(pen);
        QFont font;
        int fontSize = transformR(m_fontSize);
        if(fontSize<1) fontSize=1;
        font.setPointSize(fontSize);
        p.setFont(font);

        // 绘制边
        pen.setWidth(transformR(m_edgeWidth));
        pen.setColor(m_edgeDefaultColor);
        p.setPen(pen);
        foreach(const UndirectedEdge &i, m_edges) {
            QPen last = pen;
            /*bool filtered=(i.nodeA->degree<m_minDegree
                || i.nodeB->degree<m_minDegree);
            if(filtered){pen.setColor(m_edgeFilteredColor);p.setPen(pen);}*/

            if(i.nodeU->highlight && i.nodeV->highlight)
                pen.setColor(m_edgeHighlightedColor);p.setPen(pen);

            QString ws=QString::number(i.weight,'f',3).mid(1);
            double k= (transformY(i.nodeU->y)-transformY(i.nodeV->y))/
                      (transformX(i.nodeU->x)-transformX(i.nodeV->x)+0.0);
            double textX=(transformX(i.nodeU->x)+transformX(i.nodeV->x))/2.0;
            double textY=(transformY(i.nodeU->y)+transformY(i.nodeV->y))/2.0;

            double theta=std::atan(k);

            QPointF textPoint(textX, textY);
            QTransform transform;
            transform.rotateRadians(theta);
            p.setTransform(transform);

            QPointF drawTextPoint=transform.inverted().map(textPoint);
            drawTextPoint.setY(drawTextPoint.y()-transformR(m_edgeWidth));
            drawTextPoint.setX(drawTextPoint.x()-p.fontMetrics().width(ws)/2.0);

            p.drawText(drawTextPoint, ws);
            transform.rotateRadians(-theta);
            p.setTransform(transform);

            p.drawLine(
                transformX(i.nodeU->x),
                transformY(i.nodeU->y),
                transformX(i.nodeV->x),
                transformY(i.nodeV->y)
                );
            pen=last;
            p.setPen(last);
        }

        font.setPointSize(fontSize);
        p.setFont(font);

        // 绘制结点
        pen.setWidth(1);
        pen.setColor(Qt::PenStyle::DotLine);
        p.setPen(pen);
        foreach(const GraphNode &i, m_nodes) {
            int x,y;double r=transformR(2);
            x=transformX(i.x), y=transformY(i.y);

            // 绘制结点编号
            QPen oldpen=p.pen();
            p.setPen(QPalette(this->palette()).windowText().color());
            p.drawText(x+r+2, y, QString::number(i.id));
            p.setPen(oldpen);

            p.setBrush(i.color);
            r *= m_nodeRadius;
            p.drawEllipse(QPoint(x, y), (int)r, (int)r);
        }
    }
}

/**
 * @brief GraphWidget::slotAniTimer
 * 动画定时器信号槽
 */
void GraphWidget::slotAniTimer()
{
    m_currentAniPhase++;
    if(m_currentAniPhase>=MAX_ANI_PHASE){
        m_aniTimer->stop();
        return;
    }

    if(m_undirectGraph) {
        for(int i=0;i<m_nodes.size();++i) {
            m_nodes[i].x += (m_nodes[i].aniX-m_nodes[i].x)/(MAX_ANI_PHASE-m_currentAniPhase);
            m_nodes[i].y += (m_nodes[i].aniY-m_nodes[i].y)/(MAX_ANI_PHASE-m_currentAniPhase);
        }
    }
    this->update();
}
