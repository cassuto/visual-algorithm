#ifndef MODULESQUAREDCOVER_H
#define MODULESQUAREDCOVER_H

#include "module-squaredcover_global.h"
#include "imodule.h"

class MODULESQUAREDCOVERSHARED_EXPORT ModuleSquaredCover : public QObject, public IModule
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.visualalgorithm.modules.squaredcover")
    Q_INTERFACES(IModule)
public:
    ModuleSquaredCover();

protected:
    /**
     * 重载IModule接口
     * 接口定义详见 ../frontend/include/module.h
     */
    const char *getName() const;
    const char *getGroup() const;
    const char *getModelSymbol() const;
    int open();
    void close();
    int run(IModel *model, IControl *control);

private:
    void solve(int a, int b,int xl,int xr,int yl,int yr);

private:
    static const int m_maxChessRows = 15;
    int map[m_maxChessRows][m_maxChessRows];
    int n;
    class IModelChessBox *m_model;
    class IControl *m_control;
};

#endif // MODULESQUAREDCOVER_H
