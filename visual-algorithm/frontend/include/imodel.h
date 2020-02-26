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
 * @brief The IHanoiModel class
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

#endif // IMODEL
