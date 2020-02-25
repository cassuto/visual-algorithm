#ifndef MODULEHANOI_GLOBAL_H
#define MODULEHANOI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MODULEHANOI_LIBRARY)
#  define MODULEHANOISHARED_EXPORT Q_DECL_EXPORT
#else
#  define MODULEHANOISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MODULEHANOI_GLOBAL_H