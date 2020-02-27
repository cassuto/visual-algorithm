#include <cstring>
#include "modelhanoiimpl.h"
#include "modelgraphimpl.h"
#include "models.h"

/////////////////////////////////////////////////////////////////////////
/// \brief ModelfactoryImpl::ModelfactoryImpl
/// 模型工厂类 Impl
///
ModelFactory *ModelFactory::m_instance = 0l;

ModelFactory::ModelFactory()
{
}

/**
 * @brief 根据标识符创建模型类
 * @param symbol 标识符
 * @return pointer to IModel interface class.
 */
IModel *ModelFactory::createModel(const char *symbol)
{
    if (std::strcmp(symbol, "hanoi")==0) {
        return new ModelHanoiImpl();
    } else if (std::strcmp(symbol, "graph")==0) {
        return new ModelGraphImpl();
    } else {
        return 0l;
    }
}

