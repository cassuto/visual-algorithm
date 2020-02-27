#include "modulesquaredcover.h"


ModuleSquaredCover::ModuleSquaredCover()
    : n(1)
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
    return "分治法";
}

const char *ModuleSquaredCover::getModelSymbol() const
{
    return "chessbox";
}

int ModuleSquaredCover::open()
{
    return 0;
}

void ModuleSquaredCover::close()
{
}

/**
 * @brief 求解棋盘覆盖问题
 * @param a 特殊点的坐标x
 * @param b 特殊点的坐标y
 * @param xl x轴的边界
 * @param xr x轴的边界
 * @param yl y轴的边界
 * @param yr y轴的边界
 */
void ModuleSquaredCover::solve(int a, int b,int xl,int xr,int yl,int yr)
{
    if (xl == xr || yl == yr) {
        return;
    }
    int xm = (xl + xr) / 2;
    int ym = (yl + yr) / 2;

    if (a > xm && b <= ym) { // RT
        m_model->setElement(ym, xm, n);
        m_model->setElement(ym + 1, xm, n);
        m_model->setElement(ym + 1, xm + 1, n);
        m_control->waitForNextStep();

        n++;
        // RT
        solve(a, b, xm + 1, xr, yl, ym);
        // RB
        solve(xm + 1, ym + 1, xm + 1, xr, ym+1, yr);
        // LT
        solve(xm, ym, xl, xm, yl, ym);
        // LB
        solve(xm, ym + 1, xl, xm, ym + 1, yr);
    }
    if(a <= xm && b >ym) { // LB
        m_model->setElement(ym, xm, n);
        m_model->setElement(ym, xm + 1, n);
        m_model->setElement(ym + 1, xm + 1, n);
        m_control->waitForNextStep();

        n++;
        solve(a, b, xl, xm, ym+1, yr);
        solve(xm, ym, xl, xm, yl, ym);
        solve(xm+1, ym, xm + 1, xr, yl, ym);
        solve(xm + 1, ym + 1, xm + 1, xr, ym+1, yr);
    }
    if (a > xm && b > ym) { // RB
        m_model->setElement(ym, xm, n);
        m_model->setElement(ym, xm + 1, n);
        m_model->setElement(ym + 1, xm + 1, n);
        m_control->waitForNextStep();

        n++;
        solve(a, b, xm + 1, xr, ym+1, yr);
        solve(xm, ym, xl, xm, yl, ym);
        solve(xm + 1, ym, xm + 1, xr, yl, ym);
        solve(xm, ym + 1, xl, xm, ym + 1, yr);
    }
    if (a <= xm && b <= ym) { // LT
        m_model->setElement(ym + 1, xm + 1, n);
        m_model->setElement(ym, xm + 1, n);
        m_model->setElement(ym + 1, xm, n);
        m_control->waitForNextStep();

        n++;
        solve(a, b, xl, xm, yl, ym);
        solve(xm + 1, ym + 1, xm + 1, xr, ym+1, yr);
        solve(xm + 1, ym, xm + 1, xr, yl, ym);
        solve(xm, ym + 1, xl, xm, ym + 1, yr);
    }
}

/**
 * @brief 运行算法
 * @param model 模型接口（前端依据getModelSymbol()创建）
 * @param control 控制接口
 * @return status code
 */
int ModuleSquaredCover::run(IModel *model, IControl *control)
{
    m_model = static_cast<IModelChessBox *>(model);
    m_control = control;

    solve(m_model->getMagX()-1, m_model->getMagY()-1, 0, m_model->getNumColumns()-1, 0, m_model->getNumRows()-1);

    return 0;
}
