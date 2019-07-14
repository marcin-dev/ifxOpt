/**
 * ifxInternalUtils.cpp
 *
 * @date   2019.07
 * @author man
 */

#include "ifxInternalUtils.h"

// Anonymous namespace, internal
namespace
{
    unsigned int globalId = 0u;
} // Anonymous namespace

namespace ifx
{

unsigned int assignGlobalId()
{
    return globalId++;
}

unsigned int getGlobalObjectsCount()
{
    return globalId;
}

} /* namespace ifx */
