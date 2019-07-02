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


void OptEntryBase::getUsageString(std::string &optionUsageString) const
{
    bool addPipeChar = false;
    optionUsageString = "<";

    // TODO: Move these constructions to some new OptEntryBase class method
    if (mOptShort != '\0')
    {
        optionUsageString += "-";
        optionUsageString += mOptShort;
        addPipeChar = true;
    }

    if (mOptLong.empty() == false)
    {
        if (addPipeChar == true)
        {
            optionUsageString += '|';
        }
        optionUsageString += "--";
        optionUsageString += mOptLong;
    }


    if (this->isFlag() == true)
    {
        // Value argument is optional only for FLAG entries (boolean)
        optionUsageString.append(" [" + mValName + "]");
    }
    else
    {
        // Value is mandatory for all entries by default
        optionUsageString.append(" <" + mValName + ">");
    }

    if (mMandatory == true)
    {
        // Brackets for mandatory entries: < >
        optionUsageString.append(">");
    }
    else
    {
        // Brackets for optional entries: [ ]
        optionUsageString.at(0) = '[';
        optionUsageString.append("]");
    }
}

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
