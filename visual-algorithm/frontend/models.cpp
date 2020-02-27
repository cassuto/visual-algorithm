#include <cstring>
#include "modelhanoiimpl.h"
#include "modelgraphimpl.h"
#include "modellinearlistimpl.h"
#include "modelmatriximpl.h"
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
    } else if (std::strcmp(symbol, "linearlist")==0) {
        return new ModelLinearListImpl();
    } else if (std::strcmp(symbol, "matrix")==0) {
        return new ModelMatrixImpl();
    } else {
        return 0l;
    }
}

