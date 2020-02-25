#ifndef IMODULE_H
#define IMODULE_H

#include "errorcodes.h"

#include <QtPlugin>

// IModule 接口类
class IModule
{
public:
    IModule() {}

    /**
     * @brief 获取算法模块名称
     * @return pointer to string constant value
     */
    virtual const char *getName() const=0;
    /**
     * @brief 获取算法分组名称
     * @return pointer to string constant value
     */
    virtual const char *getGroup() const=0;
    /**
     * @brief 获取模型标识符
     * @return pointer to string constant value
     */
    virtual const char *getModelSymbol() const=0;

    /**
     * @brief 初始化算法
     * @return status code
     */
    virtual int open() =0;
    /**
     * @brief 反初始化算法
     */
    virtual void close() =0;
};

// 声明接口类
Q_DECLARE_INTERFACE(IModule,"algorithm_module/1.0")

#endif // IMODULE_H
