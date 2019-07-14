/**
 * ifxArgEntry.cpp
 *
 * @date   2019.07
 * @author man
 */

#include "ifxArgEntry.h"

namespace ifx
{

ArgEntry::ArgEntry(const std::string  valName,
                   const std::string  helpString,
                   std::string       &target,
                   OptionSet          options,
                   OnArgFoundNotifier &&notifierFn)
                   : ArgEntryBase(valName, helpString, options),
                     mTarget(target),
                     mNotifier(notifierFn)
{ }

ArgEntry::~ArgEntry()
{ }

int ArgEntry::parseValue(const std::string &valStr)
{
    int ret = IFX_OPT_RESULT_SUCCESS;

    if (true == static_cast<bool>(mNotifier))
    {
        ret = mNotifier(valStr);
    }

    if (ret == IFX_OPT_RESULT_SUCCESS)
    {
        this->mTarget = valStr;
    }

    return ret;
}

};
