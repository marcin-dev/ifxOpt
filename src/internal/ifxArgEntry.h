/**
 * ifxArgEntry.h
 *
 * @date   2019.07
 * @author man
 */

#ifndef INTERNAL_IFXARG_ENTRY_H
#define INTERNAL_IFXARG_ENTRY_H

#include <functional>

#include <ifxArgEntryBase.h>

namespace ifx
{

// Internal class for non-option arguments handling
class ArgEntry : public ArgEntryBase
{
    typedef std::function<int(const std::string &)> OnArgFoundNotifier;

private:
    std::string          &mTarget;
    OnArgFoundNotifier    mNotifier;

public:
    ArgEntry(const std::string    valName,
             const std::string    helpString,
             std::string         &target,
             OptionSet            options  = IFX_OPTION_SET_CLEAR,
             OnArgFoundNotifier &&notifierFn = nullptr);

    virtual ~ArgEntry();

    virtual int parseValue(const std::string &valStr);
};

} /* namespace ifx */

#endif /* INTERNAL_IFXARG_ENTRY_H */
