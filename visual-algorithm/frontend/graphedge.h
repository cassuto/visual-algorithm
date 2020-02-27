#ifndef GRAPHEDGE
#define GRAPHEDGE

#include "graphnode.h"

class GraphNode;

class GraphEdge{
public:
    int u, v;
    int weight;
    virtual void setEdge(int, int, double=0)=0;
};
class UndirectedEdge : public GraphEdge{
public:
    UndirectedEdge(){}
    UndirectedEdge(int u, int v, double weight=0){
        setEdge(u, v, weight);
    }
    void setEdge(int u, int v, double weight=0){
        if(u>v){
            int t;
            t=u,u=v,v=t;
        }
        this->u=u, this->v=v, this->weight=weight;
    }
public:
    GraphNode *nodeU;
    GraphNode *nodeV;
};
class DirectedEdge : public GraphEdge{
public:
    DirectedEdge(){}
    DirectedEdge(int u, int v, double weight=0){
        setEdge(u, v,weight);
    }
    void setEdge(int u, int v, double weight=0){
        this->u=u, this->v=v;
        this->weight=weight;
    }
public:
    GraphNode *nodeU;
    GraphNode *nodeV;
public:

};

#endif // GRAPHEDGE

