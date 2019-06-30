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
                             mMandatory(IFX_OPTION_CHECK(options, IFX_OPT_ENTRY_MANDATORY))
{ }

OptEntryBase::~OptEntryBase()
{ }


const std::string &OptEntryBase::getHelpString()  const { return this->mHelpString;  }
const std::string &OptEntryBase::getValName()     const { return this->mValName;     }
const std::string &OptEntryBase::getOptLong()     const { return this->mOptLong;     }
const char        &OptEntryBase::getOptShort()    const { return this->mOptShort;    }
const bool        &OptEntryBase::isMandatory()    const { return this->mMandatory;   }

int OptEntryBase::parseOpt(const std::string &argStr, const char argShort)
{
    std::cout << "parseOpt(argStr=" << argStr << ", argShort=" << argShort << ")" << std::endl;

    int retVal;

    std::cout << "optLong: " << this->mOptLong << ", optShort: " << this->mOptShort << std::endl;

    if (   (this->mOptLong.empty() == false && this->mOptLong.compare(argStr) == 0)
        || (this->mOptShort        != '\0'  && this->mOptShort == argShort) )
    {
        retVal = IFX_OPT_RESULT_SUCCESS;
        std::cout << "parseOpt MATCH" << std::endl;
    }
    else
    {
        retVal = IFX_OPT_NOT_MACHING_OPTION;
        std::cout << "parseOpt NOT MATCH" << std::endl;
    }

    return retVal;
}

bool OptEntryBase::isFlag() const
{
    return false; // this is the default behavior
}

} /* namespace ifx */
