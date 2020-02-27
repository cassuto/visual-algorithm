#ifndef MODELLINEARLISTIMPL_H
#define MODELLINEARLISTIMPL_H

#include <QObject>
#include <QWidget>
#include "imodel.h"

/**
 * @brief The IModelLinearList class
 * 线性表模型（算法无关）
 */
class ModelLinearListImpl : public QObject, public IModelLinearList
{
    Q_OBJECT
public:
    explicit ModelLinearListImpl(QObject *parent = 0l);
    ~ModelLinearListImpl();

    /**
      * IModel接口实现
      * 接口定义详见 ../frontend/include/imodule.h
      */
    QWidget *getInputWidget(QWidget * parent = 0);
    QWidget *getOutputWidget(QWidget * parent = 0);
    int getTimeInval() const {
        return 200;
    }

    /**
     * IModelLinearList接口实现
     * 接口定义详见 ../frontend/include/imodule.h
     */
    int getSize() const;
    int getElement(int idx) const;
    void setElement(int idx, int value);

signals:

public slots:
    void slotBtnAppendPressed();
    void slotBtnClearPressed();
    void slotRandomGenInput();

protected:
    void createDataInputPage();
    void createDataOutputPage();
    void clear();
    void updateView();

private:
    QWidget *m_pageDin;
    QWidget *m_pageDout;
    class QSpinBox *m_spinNum;
    class QSpinBox *m_spinValue;
    class LinearWidget *m_view;
    static const int m_maxListSize = 1000000;
    int m_list[m_maxListSize];
    int m_listLen;
    int m_listMax;

friend class LinearWidget;
};

class LinearWidget : public QWidget
{
    Q_OBJECT
public:
    LinearWidget(ModelLinearListImpl *model) : model(model)
    {}
    void paintEvent(QPaintEvent *event);
private:
    ModelLinearListImpl *model;
};

#endif // MODELLINEARLISTIMPL_H
