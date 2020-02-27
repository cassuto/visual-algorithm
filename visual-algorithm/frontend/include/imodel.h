#ifndef IMODEL
#define IMODEL

class IModel
{
public:
    /**
     * @brief 获取数据输入Widget实例
     * @param parent
     */
    virtual class QWidget *getInputWidget(class QWidget * parent = 0)=0;
    /**
     * @brief 获取数据输出Widget实例
     * @param parent
     */
    virtual class QWidget *getOutputWidget(class QWidget * parent = 0)=0;
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

    virtual void resetPillar()=0;
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
     * @brief matrix 获取邻接矩阵
     * @param u
     * @param v
     * @return
     */
    virtual int matrix(int u, int v) const=0;
    /**
     * @brief 获取结点个数
     * @return
     */
    virtual int getNumNodes() const=0;
    /**
     * @brief 获取边个数
     * @return
     */
    virtual int getNumEdges() const=0;
    /**
     * @brief 获取第i条边的权值
     * @param i [1, numEdges]
     * @return
     */
    virtual int getWeight(int i) const=0;
    /**
     * @brief 获取第i条边的两个端点
     * @param i [1, numEdges]
     * @param u
     * @param v
     */
    virtual void getEndpoints(int i, int *u, int *v) const=0;

    /**
     * @brief 添加一条从第u个结点到第v个结点的边
     * @param u 起点编号
     * @param v 终点编号
     * @param val 权值
     * @return
     */
    virtual void addEdge(int u, int v, int val)=0;
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

    /**
     * @brief 获取线性表长度
     * @return size
     */
    virtual int getSize() const=0;
    /**
     * @brief 获取位序为idx的元素
     * @param idx [1,size]
     * @return 元素值
     */
    virtual int getElement(int idx) const=0;
    /**
     * @brief 更新位序为idx的元素的值
     * @param idx [1,size]
     * @param value
     */
    virtual void setElement(int idx, int value)=0;
};


/**
 * @brief The IModelMatrix class
 * 矩阵模型 （算法无关）
 */
class IModelMatrix : public IModel
{
public:
    IModelMatrix() {}

    virtual int getNumRows() const=0;
    virtual int getNumColumns() const=0;
    virtual int getElement(int row, int col) const=0;
    virtual void setElement(int row, int col, int value)=0;
};


#endif // IMODEL
