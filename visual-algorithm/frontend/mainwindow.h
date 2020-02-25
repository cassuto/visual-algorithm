#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    class QMdiArea *m_mdiArea;
    class FormAlgorithmMenu *m_formAlgorithmMenu;
};

#endif // MAINWINDOW_H
