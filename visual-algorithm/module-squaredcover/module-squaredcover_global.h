#ifndef MODULESQUAREDCOVER_GLOBAL_H
#define MODULESQUAREDCOVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MODULESQUAREDCOVER_LIBRARY)
#  define MODULESQUAREDCOVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MODULESQUAREDCOVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MODULESQUAREDCOVER_GLOBAL_H
