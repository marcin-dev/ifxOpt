/**
 * ifxOptEntry.h
 *
 * @date   2019.04
 * @author man
 */

#ifndef INCLUDE_IFXOPT_ENTRY_H
#define INCLUDE_IFXOPT_ENTRY_H

#include <string>

namespace ifx
{

template <typename T> class Validator
{
    Validator() {}
    virtual ~Validator() {}
    virtual bool operator() (T argVal) = 0;
};

class OptEntry
{
private:
    const std::string  optLong;
    const char         optShort;

public:
    OptEntry(const std::string  optLong,
             const char optShort);
    virtual ~OptEntry();

    int parseOpt(const std::string &valarg, const std::string &valstr)
    {
        int retVal = 1; // by default - not matching string

        if (   valarg == optShort
            || valarg == optLong)
        {
            retVal = this->parseOpt(valstr); // run the second virtual method to parse value
        }

        return retVal;
    }

    virtual int parseOpt(const std::string &valstr) = 0;
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_ENTRY_H */
