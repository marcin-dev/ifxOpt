/**
 * ifxDbg.h
 *
 * @date   2019.07
 * @author man
 */

#ifndef INCLUDE_IFXDBG_H
#define INCLUDE_IFXDBG_H

#include <iostream>

#define LOG_TAG     "[IFX_OPT]"

#define IFX_LOG_ERR(stream) \
        std::cerr << LOG_TAG << " " << "ERROR: " << stream << std::endl

#ifdef DEBUG_LOG_ENABLED

#define IFX_LOG_DBG(stream) \
        std::cout << LOG_TAG << " " << stream << std::endl

#else // ! DEBUG_LOG_ENABLED

#define IFX_LOG_DBG(stream)

#endif // DEBUG_LOG_ENABLED

#endif /* INCLUDE_IFXDBG_H */
