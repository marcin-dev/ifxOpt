/**
 * ifxOpt.cpp
 *
 * @date   2019.04
 * @author man
 */

#include "ifxOpt.h"

// Type specific option parsers:
#include "ifxOptEntryInt.h"

namespace ifx
{

Opt::Opt() : entries(10) // we start from 10 options for now
{
    // TODO Auto-generated constructor stub
}

Opt::~Opt()
{
    // TODO Auto-generated destructor stub
}

template <typename T> void Opt::addOptEntry(const std::string  optLong,
                                       const char optShort,
                                       T &target)
{
    // TODO different implementation for basic types
}

template <typename T> void Opt::addOptEntry(const std::string  optLong,
                                       const char optShort,
                                       T &target,
                                       Validator<T> &validatorFn)
{
    // TODO different implementation for basic types
}

// Option type: int
template <> void Opt::addOptEntry <int> (const std::string  optLong,
                                         const char optShort,
                                         int &target)
{
    OptEntryInt *opt = new OptEntryInt(optLong, optShort, target);
    if (opt != nullptr)
    {
        //entries.push_back(opt);
        entries.push_back(dynamic_cast<OptEntry *>(opt));
        //entries.push_back((OptEntry *)(opt));
    }
    // else TODO: some error mechanism
}

template <> void Opt::addOptEntry <int> (const std::string  optLong,
                                         const char optShort,
                                         int &target,
                                         Validator<int> &validatorFn)
{
    OptEntryInt *opt = new OptEntryInt(optLong, optShort, target, validatorFn);
    if (opt != nullptr)
    {
        //entries.push_back(opt);
        entries.push_back(dynamic_cast<OptEntry *>(opt));
        //entries.push_back((OptEntry *)(opt));
    }
    // else TODO: some error mechanism
}

int Opt::parseOpt(int argc, char* argv[])
{
    int retVal = 0;
    std::string argstr;
    std::string valstr;

    // TODO:
    // trim each argv
    // add some bool or whatever to state whether option value is mandatory (is this needed?)
    // default value for each option?

    for (int i = 0; i < argc; i++)
    {
        //for (auto&& e : entries)
        for (OptEntry *&e : entries)
        {
            retVal = e->parseOpt(argstr, valstr); // TODO: is this ok?

            if (retVal > 0)
            {
                // Not matching string, go to the next element
                continue;
            }
            else
            {
                // Found match and extracted the value successfully
                // Or parsing error
                break;
            }
        }

        if (retVal < 0)
        {
            // Parsing error, need to exit
            break;
        }
    }

    return retVal;
}

} /* namespace ifx */
