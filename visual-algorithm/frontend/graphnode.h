#ifndef GRAPHNODE
#define GRAPHNODE

#include <QColor>
#include <ogdf/basic/Graph.h>
#include "graphedge.h"

class GraphNode{
public:
    GraphNode()
    {
        highlight = false;
        x = OGDF_left + (OGDF_width>>1);
        y = OGDF_top + (OGDF_height>>1);
    }

public:
    int id;
    ogdf::node ogdfID;
    double x, y;
    QColor color;
    bool highlight;

protected:
    double aniX, aniY;
friend class GraphWidget;

public:
    static const int OGDF_width = 500;
    static const int OGDF_height = 500;
    static const int OGDF_left = 30;
    static const int OGDF_top = 60;
};

#endif // GRAPHNODE
