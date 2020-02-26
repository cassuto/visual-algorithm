#ifndef MODULEQUICKSORT_H
#define MODULEQUICKSORT_H

#include "module-quicksort_global.h"
#include "imodule.h"

class MODULEQUICKSORTSHARED_EXPORT ModuleQuicksort : public QObject, public IModule
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.visualalgorithm.modules.kruskal")
    Q_INTERFACES(IModule)
public:
    ModuleQuicksort();

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

#endif // MODULEQUICKSORT_H