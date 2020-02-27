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

/**
 * @brief 运行算法
 * @param model 模型接口（前端依据getModelSymbol()创建）
 * @param control 控制接口
 * @return status code
 */
int ModuleSquaredCover::run(IModel *model, IControl *control)
{
    return 0;
}
