#ifndef MODULEKRUSKAL_GLOBAL_H
#define MODULEKRUSKAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MODULEKRUSKAL_LIBRARY)
#  define MODULEKRUSKALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MODULEKRUSKALSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MODULEKRUSKAL_GLOBAL_H
