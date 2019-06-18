/**
 * ifxDbg.h
 *
 * @date   2019.05
 * @author man
 */

#ifndef INCLUDE_IFXDBG_H
#define INCLUDE_IFXDBG_H

#include "ifxOptEntry.h"
#include "ifxValidator.h"

#define DEBUG_LOG_ENABLED
#ifdef DEBUG_LOG_ENABLED

#include <iostream>
#define IFX_LOG_DBG(...)

#endif // DEBUG_LOG_ENABLED

#endif /* INCLUDE_IFXDBG_H */
