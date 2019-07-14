/**
 * ifxOptEntryBase.h
 *
 * @date   2019.07
 * @author man
 */

#ifndef INCLUDE_IFXOPT_ENTRY_BASE_H
#define INCLUDE_IFXOPT_ENTRY_BASE_H

#include <string>

#include "ifxArgEntryBase.h"
#include "ifxOptResultCodes.h"
#include "ifxOptOptionCodes.h"

namespace ifx
{

class OptEntryBase : public ArgEntryBase
{
private:
    std::string        mUsageString;
    const std::string  mOptLong;
    const char         mOptShort;

public:
    OptEntryBase(const std::string  optLong,
                 const char         optShort,
                 const std::string  valName,
                 const std::string  helpString,
                 OptionSet          options);

    virtual ~OptEntryBase();

    virtual const std::string &getUsageString();
    const std::string &getOptLong()     const;
    const char        &getOptShort()    const;

    int parseOpt(const std::string &argStr, const char argShort);

    virtual int parseValue(const std::string &valStr) = 0;

    // The following function may be defined in each type-specific implementation
    bool isFlag() const;
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_ENTRY_BASE_H */
