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
                           bool               mandatory,
                           bool               valMandatory)
                           : helpString(helpString), valName(valName), optLong(optLong),
                             optShort(optShort), mandatory(mandatory), valMandatory(valMandatory)
{ }

OptEntryBase::~OptEntryBase()
{ }


const std::string &OptEntryBase::getHelpString()  const { return this->helpString;  }
const std::string &OptEntryBase::getValName()     const { return this->valName;     }
const std::string &OptEntryBase::getOptLong()     const { return this->optLong;     }
const char        &OptEntryBase::getOptShort()    const { return this->optShort;    }
const bool        &OptEntryBase::isMandatory()    const { return this->mandatory;   }
const bool        &OptEntryBase::isValMandatory() const { return this->valMandatory;}

int OptEntryBase::parseOpt(const std::string &argStr, const char argShort, const std::string &valStr)
{
    std::cout << "parseOpt(argStr=" << argStr << ", argShort=" << argShort << ", valStr=" << valStr << ")" << std::endl;

    int retVal = IFX_OPT_NOT_MACHING_OPTION; // by default - not matching string

    std::cout << "optLong: " << this->optLong << ", optShort: " << this->optShort << std::endl;

    if (   this->optLong.compare(argStr) == 0
        || this->optShort == argShort )
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
