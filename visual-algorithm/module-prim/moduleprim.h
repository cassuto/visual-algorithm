#ifndef MODULEPRIM_H
#define MODULEPRIM_H

#include "module-prim_global.h"
#include "imodule.h"

class MODULEPRIMSHARED_EXPORT ModulePrim : public QObject, public IModule
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.visualalgorithm.modules.kruskal")
    Q_INTERFACES(IModule)
public:
    ModulePrim();

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
};

#endif // MODULEPRIM_H
