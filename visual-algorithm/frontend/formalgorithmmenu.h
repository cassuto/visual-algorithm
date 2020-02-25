#ifndef FORMALGORITHMMENU_H
#define FORMALGORITHMMENU_H

#include <QWidget>

/**
 * @brief The FormAlgorithmMenu class
 * 选择算法窗口
 */
class FormAlgorithmMenu : public QWidget
{
    Q_OBJECT
public:
    explicit FormAlgorithmMenu(QWidget *parent = 0);

signals:

public slots:
    void menuDbClicked(class QListWidgetItem *item);
    void viewClosed(class IModule *module);

protected:
    class QToolBox *m_toolBox;
};

#endif // FORMALGORITHMMENU_H
