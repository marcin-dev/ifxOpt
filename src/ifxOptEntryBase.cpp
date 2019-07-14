/**
 * ifxOptEntryBase.cpp
 *
 * @date   2019.06
 * @author man
 */

#include <ifxOptEntryBase.h>

#include "internal/ifxDbg.h"

namespace ifx
{

OptEntryBase::OptEntryBase(const std::string  optLong,
                           const char         optShort,
                           const std::string  valName,
                           const std::string  helpString,
                           OptionSet          options)
                           : ArgEntryBase(valName, helpString, options),
                             mOptLong(optLong),
                             mOptShort(optShort)
{ }

OptEntryBase::~OptEntryBase()
{ }


const std::string &OptEntryBase::getUsageString()
{
    if (mUsageString.empty() == true)
    {
        bool addPipeChar = false;

        if (mOptShort != '\0')
        {
            mUsageString += "-";
            mUsageString += mOptShort;
            addPipeChar = true;
        }

        if (mOptLong.empty() == false)
        {
            if (addPipeChar == true)
            {
                mUsageString += '|';
            }
            mUsageString += "--";
            mUsageString += mOptLong;
        }


        if (this->isFlag() == true)
        {
            // Value argument is optional only for FLAG entries (boolean)
            mUsageString.append(" [" + getValName() + "]");
        }
        else
        {
            // Value is mandatory for all entries by default
            mUsageString.append(" <" + getValName() + ">");
        }
    }

    return mUsageString;
}

const std::string &OptEntryBase::getOptLong()     const { return this->mOptLong;     }
const char        &OptEntryBase::getOptShort()    const { return this->mOptShort;    }

int OptEntryBase::parseOpt(const std::string &argStr, const char argShort)
{
    int retVal;

    IFX_LOG_DBG("parseOpt(argStr=" << argStr << ", argShort=" << argShort << ")");
    IFX_LOG_DBG("optLong: " << this->mOptLong << ", optShort: " << this->mOptShort);

    if (   (this->mOptLong.empty() == false && this->mOptLong.compare(argStr) == 0)
        || (this->mOptShort        != '\0'  && this->mOptShort == argShort) )
    {
        retVal = IFX_OPT_RESULT_SUCCESS;
        IFX_LOG_DBG("parseOpt MATCH");
    }
    else
    {
        retVal = IFX_OPT_NOT_MACHING_OPTION;
        IFX_LOG_DBG("parseOpt NOT MATCH");
    }

    return retVal;
}

bool OptEntryBase::isFlag() const
{
    return false; // this is the default behavior
}

} /* namespace ifx */
