/**
 * ifxArgEntryBase.cpp
 *
 * @date   2019.07
 * @author man
 */

#include <ifxArgEntryBase.h>

#include "internal/ifxInternalUtils.h"
#include "internal/ifxDbg.h"

namespace ifx
{

ArgEntryBase::ArgEntryBase(const std::string  valName,
                           const std::string  helpString,
                           OptionSet          options)
                           : mId(assignGlobalId()),
                             mHelpString(helpString),
                             mValName(valName),
                             mMandatory(IFX_OPTION_CHECK(options, IFX_OPT_ENTRY_MANDATORY))
{ }

ArgEntryBase::~ArgEntryBase()
{ }


const std::string &ArgEntryBase::getUsageString()
{
    return mValName;
}

const unsigned int  &ArgEntryBase::getId()          const { return this->mId;  }
const std::string   &ArgEntryBase::getHelpString()  const { return this->mHelpString;  }
const std::string   &ArgEntryBase::getValName()     const { return this->mValName;     }
const bool          &ArgEntryBase::isMandatory()    const { return this->mMandatory;   }

} /* namespace ifx */
