#ifndef FORMALGORITHMMENU_H
#define FORMALGORITHMMENU_H

#include <QWidget>

class FormAlgorithmMenu : public QWidget
{
    Q_OBJECT
public:
    explicit FormAlgorithmMenu(QWidget *parent = 0);

signals:

public slots:

protected:
    class QToolBox *m_toolBox;
};

#endif // FORMALGORITHMMENU_H
