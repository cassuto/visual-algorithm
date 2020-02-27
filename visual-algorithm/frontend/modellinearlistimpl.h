#ifndef MODELLINEARLISTIMPL_H
#define MODELLINEARLISTIMPL_H

#include <QObject>
#include <QObject>
#include "imodel.h"

/**
 * @brief The IModelLinearList class
 * 线性表模型（算法无关）
 */
class ModelLinearListImpl : public QObject, public IModelLinearList
{
    Q_OBJECT
public:
    explicit ModelLinearListImpl(QWidget *parent = 0);

    /**
      * IModel接口实现
      * 接口定义详见 ../frontend/include/imodule.h
      */
    QWidget *getInputWidget(QWidget * parent = 0);
    QWidget *getOutputWidget(QWidget * parent = 0);

    /**
     * IModelLinearList接口实现
     * 接口定义详见 ../frontend/include/imodule.h
     */

signals:

public slots:
};

#endif // MODELLINEARLISTIMPL_H
