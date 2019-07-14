/**
 * ifxArgEntryBase.h
 *
 * @date   2019.07
 * @author man
 */

#ifndef INCLUDE_IFXARG_ENTRY_BASE_H
#define INCLUDE_IFXARG_ENTRY_BASE_H

#include <string>

#include "ifxOptResultCodes.h"
#include "ifxOptOptionCodes.h"

namespace ifx
{

class ArgEntryBase
{
private:
    const std::string  mHelpString;
    const std::string  mValName;
    const bool         mMandatory;

public:
    ArgEntryBase(const std::string  valName,
                 const std::string  helpString,
                 OptionSet          options);

    virtual ~ArgEntryBase();

    virtual void getUsageString(std::string &optionUsageString) const;
    const std::string &getHelpString()  const;
    const std::string &getValName()     const;
    const bool        &isMandatory()    const;

    virtual int parseValue(const std::string &valStr) = 0;
};

} /* namespace ifx */

#endif /* INCLUDE_IFXARG_ENTRY_BASE_H */
