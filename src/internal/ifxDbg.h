/**
 * ifxDbg.h
 *
 * @date   2019.07
 * @author man
 */

#ifndef INCLUDE_IFXDBG_H
#define INCLUDE_IFXDBG_H

#define DEBUG_LOG_ENABLED
#ifdef DEBUG_LOG_ENABLED

#define LOG_TAG     "[IFX_OPT]"

#include <iostream>
#define IFX_LOG_DBG(stream) \
        std::cout << LOG_TAG << " " << stream << std::endl
#define IFX_LOG_ERR(stream) \
        std::cerr << LOG_TAG << " " << "ERROR: " << stream << std::endl

#else // ! DEBUG_LOG_ENABLED

#define IFX_LOG_DBG(stream)
#define IFX_LOG_ERR(stream)

#endif // DEBUG_LOG_ENABLED

#endif /* INCLUDE_IFXDBG_H */
