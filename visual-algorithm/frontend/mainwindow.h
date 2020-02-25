#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Singleton Mode
    static MainWindow &instance() {
        if(!m_instance) {
            m_instance = new MainWindow;
        }
        return *m_instance;
    }

    void createAlgorithmForm(class IModule *module);

protected:
    class QMdiArea *m_mdiArea;
    class FormAlgorithmMenu *m_formAlgorithmMenu;

private:
    static MainWindow *m_instance;
};

#endif // MAINWINDOW_H
