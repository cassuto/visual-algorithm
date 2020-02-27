#ifndef IMODEL
#define IMODEL

#include <QWidget>

class IModel
{
public:
    /**
     * @brief 获取数据输入Widget实例
     * @param parent
     */
    virtual QWidget *getInputWidget(QWidget * parent = 0)=0;
    /**
     * @brief 获取数据输出Widget实例
     * @param parent
     */
    virtual QWidget *getOutputWidget(QWidget * parent = 0)=0;
};

/**
 * @brief The IModelHanoi class
 * 汉诺塔模型 （算法无关）
 */
class IModelHanoi : public IModel
{
public:
    IModelHanoi() {}

    /**
     * @brief 获取圆盘数
     * @return integer, the number of disks
     */
    virtual int getDisksNum() const=0;
    /**
     * @brief 将柱子src上最后一个圆盘移动到dst上
     * @param src 柱子编号 'A' 'B' 'C'
     * @param dst 柱子编号 'A' 'B' 'C'
     */
    virtual void moveTop(char src, char dst)=0;
};

/**
 * @brief The IModelGraph class
 * 图论模型 （算法无关）
 */
class IModelGraph : public IModel
{
public:
    IModelGraph() {}

    /**
     * @brief 添加一条从第u个结点到第v个结点的边
     * @param u 起点编号
     * @param v 终点编号
     * @param val 权值
     * @return
     */
    virtual void addEdge(int u, int v, double val)=0;
    /**
     * @brief 删除从u到v的所有边
     * @param u 起点编号
     * @param v 终点编号
     */
    virtual void removeEdge(int u, int v)=0;
    /**
     * @brief 添加count个结点
     * @param count
     */
    virtual void addNodes(int count)=0;
    /**
     * @brief 删除所有结点与边
     */
    virtual void clear()=0;
};


/**
 * @brief The IModelLinearList class
 * 线性表模型 （算法无关）
 */
class IModelLinearList : public IModel
{
public:
    IModelLinearList() {}

};



#endif // IMODEL
