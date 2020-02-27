#ifndef MODELHANOIIMPL_H
#define MODELHANOIIMPL_H

#include <QWidget>
#include <QColor>
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
    ~ModelHanoiImpl();

    /**
      * IModel接口实现
      * 接口定义详见 ../frontend/include/imodule.h
      */
    QWidget *getInputWidget(QWidget * parent = 0);
    QWidget *getOutputWidget(QWidget * parent = 0);

    /**
     * IModelHanoi接口实现
     * 接口定义详见 ../frontend/include/imodule.h
     */
    int getDisksNum() const;
    void moveTop(char src, char dst);
    void resetPillar();

private slots:
    void numDiskValueChanged(int i);

protected:
    void createDataInputPage();
    void createDataOutputPage();
    void updateStep();
    void updateDisk(bool reset);

private:
    int m_maxDiskNum;
    class QLabel *m_lbStep;
    class QSpinBox *m_spinDiskNum;
    int m_step;
    class QGraphicsScene *m_scene;
    class QGraphicsView *m_view;
    QWidget *m_pageDin;
    QWidget *m_pageDout;
    int m_pillar[3];
    int m_numDisks;
    QColor *m_diskFillColor;
    QColor m_pillarColor;
    QList<class QGraphicsItem *> m_graphItems;
};

#endif // MODELHANOIIMPL_H
