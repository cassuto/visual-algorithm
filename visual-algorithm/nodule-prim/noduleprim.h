#ifndef NODULEPRIM_H
#define NODULEPRIM_H

#include "nodule-prim_global.h"
#include "imodule.h"

class NODULEPRIMSHARED_EXPORT NodulePrim : public QObject, public IModule
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.visualalgorithm.modules.prim")
    Q_INTERFACES(IModule)
public:
    NodulePrim();

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

#endif // NODULEPRIM_H
