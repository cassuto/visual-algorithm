#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QVector>
#include <QTimer>
#include <ogdf/basic/Graph.h>
#include "graphedge.h"
#include "graphnode.h"

class GraphWidget : public QWidget {
    Q_OBJECT
public:
    GraphWidget(QWidget *parent = 0l);
    /**
     * @brief 通过ID获取结点
     * @param id
     * @retval pointer to the instance of node
     * @retval NULL if none
     */
    GraphNode *getNode(int id);

    void clear();
    void addNode(const GraphNode &node);
    void addEdge(const UndirectedEdge &edge);
    inline int getNumNodes() const {
        return m_nodes.count();
    }
    bool connected(int u, int v);

protected:
    /**
     * @brief 维护边与顶点的信息
     */
    void rearrange();

    /**
     * @brief 运行布局算法
     */
    void layout();

protected:
    QVector<GraphNode> m_nodes;
    QVector<UndirectedEdge> m_edges;
    bool m_undirectGraph;

    QTimer *m_aniTimer;
    bool m_aniActive;
    int m_currentAniPhase;
    static const int MAX_ANI_PHASE = 48;

    int m_fontSize;
    double m_edgeWidth;
    double m_nodeRadius;
    int m_minDegree;
    QColor m_edgeDefaultColor;
    QColor m_edgeFilteredColor;
    QColor m_edgeHighlightedColor;

    // 视图位置偏移量
    double m_viewX, m_viewY;
    double m_viewScale;

private slots:
    void slotAniTimer();

protected:
    void paintEvent(QPaintEvent *event);
};


#endif // GRAPH_H
