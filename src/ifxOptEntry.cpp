/**
 * ifxOptEntry.cpp
 *
 * @date   2019.06
 * @author man
 */

#include <ifxOptResultCodes.h>
#include "ifxOptEntry.h"

#include <iostream>

namespace ifx
{

OptEntryBase::OptEntryBase(const std::string  optLong,
                           const char         optShort,
                           const std::string  valName,
                           std::string        helpString,
                           OptionSet          options)
                           : mHelpString(helpString),
                             mValName(valName),
                             mOptLong(optLong),
                             mOptShort(optShort),
                             mMandatory(IFX_OPTION_CHECK(options, IFX_OPT_ENTRY_MANDATORY)),
                             mHasValArg(IFX_OPTION_CHECK(options, IFX_OPT_ENTRY_HAS_VAL_ARG)),
                             mValMandatory(IFX_OPTION_CHECK(options, IFX_OPT_ENTRY_VAL_ARG_MANDATORY))
{ }

OptEntryBase::~OptEntryBase()
{ }


const std::string &OptEntryBase::getHelpString()  const { return this->mHelpString;  }
const std::string &OptEntryBase::getValName()     const { return this->mValName;     }
const std::string &OptEntryBase::getOptLong()     const { return this->mOptLong;     }
const char        &OptEntryBase::getOptShort()    const { return this->mOptShort;    }
const bool        &OptEntryBase::isMandatory()    const { return this->mMandatory;   }
const bool        &OptEntryBase::hasValArg()      const { return this->mHasValArg;   }
const bool        &OptEntryBase::isValMandatory() const { return this->mValMandatory;}

int OptEntryBase::parseOpt(const std::string &argStr, const char argShort, const std::string &valStr)
{
    std::cout << "parseOpt(argStr=" << argStr << ", argShort=" << argShort << ", valStr=" << valStr << ")" << std::endl;

    int retVal = IFX_OPT_NOT_MACHING_OPTION; // by default - not matching string

    std::cout << "optLong: " << this->mOptLong << ", optShort: " << this->mOptShort << std::endl;

    if (   (this->mOptLong.empty() == false && this->mOptLong.compare(argStr) == 0)
        || (this->mOptShort        != '\0'  && this->mOptShort == argShort) )
    {
        std::cout << "parseOpt MATCH" << std::endl;
        retVal = this->parseOpt(valStr); // run the second virtual method to parse value
    }
    else
    {
        std::cout << "parseOpt NOT MATCH" << std::endl;
    }

    return retVal;
}

} /* namespace ifx */
