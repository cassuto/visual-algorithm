#ifndef FORMDATAINPUT_H
#define FORMDATAINPUT_H

#include <QWidget>
#include "module.h"

/**
 * @brief The formdatainput class
 * 算法视图（数据I/O）窗口
 */
class FormAlgorithmView : public QWidget
{
    Q_OBJECT
public:
    explicit FormAlgorithmView(IModule *module, QWidget *parent = 0);

signals:

public slots:

protected:
    IModule *m_module;
};

#endif // FORMDATAINPUT_H
