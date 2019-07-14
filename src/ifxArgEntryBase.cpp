/**
 * ifxArgEntryBase.cpp
 *
 * @date   2019.07
 * @author man
 */

#include <ifxArgEntryBase.h>

#include "internal/ifxDbg.h"

namespace ifx
{

ArgEntryBase::ArgEntryBase(const std::string  valName,
                           const std::string  helpString,
                           OptionSet          options)
                           : mHelpString(helpString),
                             mValName(valName),
                             mMandatory(IFX_OPTION_CHECK(options, IFX_OPT_ENTRY_MANDATORY))
{ }

ArgEntryBase::~ArgEntryBase()
{ }


void ArgEntryBase::getUsageString(std::string &optionUsageString) const
{
    optionUsageString = mValName;
}

const std::string &ArgEntryBase::getHelpString()  const { return this->mHelpString;  }
const std::string &ArgEntryBase::getValName()     const { return this->mValName;     }
const bool        &ArgEntryBase::isMandatory()    const { return this->mMandatory;   }

} /* namespace ifx */
