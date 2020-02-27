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
};

#endif // MODULESQUAREDCOVER_H
