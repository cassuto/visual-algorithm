#ifndef MODELHANOIIMPL_H
#define MODELHANOIIMPL_H

#include <QWidget>
#include "imodel.h"

/**
 * @brief The IHanoiModel class
 * 汉诺塔模型（算法无关）
 */
class ModelHanoiImpl : public QObject, public IModelHanoi
{
    Q_OBJECT
public:
    ModelHanoiImpl();
    ~ModelHanoiImpl() {}

    /**
      * IModel接口实现
      * 接口定义详见 ../frontend/include/imodule.h
      */
    QWidget *createInputWidget(QWidget * parent = 0);
    QWidget *createOutputWidget(QWidget * parent = 0);

    /**
     * IModelHanoi接口实现
     * 接口定义详见 ../frontend/include/imodule.h
     */
    int getDisksNum() const;
    void moveTop(char src, char dst);

private:

};

#endif // MODELHANOIIMPL_H
