#ifndef MODULEKRUSKAL_H
#define MODULEKRUSKAL_H

#include "module-kruskal_global.h"
#include "imodule.h"

class MODULEKRUSKALSHARED_EXPORT ModuleKruskal : public QObject, public IModule
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.visualalgorithm.modules.kruskal")
    Q_INTERFACES(IModule)
public:
    ModuleKruskal();

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

};

#endif // MODULEKRUSKAL_H
