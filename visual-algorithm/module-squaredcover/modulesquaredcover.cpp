#include "modulesquaredcover.h"


ModuleSquaredCover::ModuleSquaredCover()
{
}

/**
 * 重载IModule接口
 * 接口定义详见 ../frontend/include/module.h
 */

const char *ModuleSquaredCover::getName() const
{
    return "棋盘覆盖";
}

const char *ModuleSquaredCover::getGroup() const
{
    return "回溯法";
}

const char *ModuleSquaredCover::getModelSymbol() const
{
    return "matrix";
}

int ModuleSquaredCover::open()
{
    return 0;
}

void ModuleSquaredCover::close()
{
}
