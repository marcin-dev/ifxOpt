/**
 * ifxOpt.cpp
 *
 * @date   2019.04
 * @author man
 */

#include "ifxOpt.h"

// Type specific option parsers:
#include "ifxOptEntryInt.h"

#include <iostream>

namespace ifx
{

Opt::Opt() : entries() // we start from 10 options for now
{
    // TODO Auto-generated constructor stub
}

Opt::~Opt()
{
    // TODO Auto-generated destructor stub
}

const char *Opt::getOption(const char* in, std::string &argStr, char &argChar)
{
    argChar = 0;
    argStr.clear();

    if (*in == '-')
    {
        in++;

        if (*in == '-')
        {
            in++;
            // Long opt
            argStr = std::string(in);
        }
        else
        {
            // Short opt
            argChar = *in++;
        }
    }
    else
    {
        argStr = std::string(in);
    }

    return in;
}

// ****************************************************************************
// Custom Validator Generic Template
// ****************************************************************************

template <typename T>
class InternalCustomValidator : public Validator<T>
{
private:
    std::function<bool(T)> func;
public:
    InternalCustomValidator(std::function<bool(T)> func) : func(func) {}
    virtual ~InternalCustomValidator() {}
    virtual bool operator() (T& argVal) { return func(argVal); }
};

template <typename T>
Validator<T> *CustomValidator(std::function<bool(T)> func)
{
    return new InternalCustomValidator<T>(func);
}

// ****************************************************************************
// Option type generic template
// ****************************************************************************

template <typename T> void Opt::addOptEntry(const std::string  optLong,
                                       const char optShort,
                                       T &target)
{
    // TODO different implementation for basic types
    std::cout << "Opt::addOptEntry3 <>" << std::endl;
}

template <typename T> void Opt::addOptEntry(const std::string  optLong,
                                       const char optShort,
                                       T &target,
                                       Validator<T> *validatorFn)
{
    // TODO different implementation for basic types
    std::cout << "Opt::addOptEntry4 <>" << std::endl;
}

// ****************************************************************************
// Option type: int
// ****************************************************************************

template <> void Opt::addOptEntry<int> (const std::string  optLong,
                                        const char optShort,
                                        int &target)
{
    std::cout << "Opt::addOptEntry3 <int> START" << std::endl;

    OptEntryBase *opt = new OptEntryInt(optLong, optShort, target);
    if (opt != nullptr)
    {
        entries.push_back(opt);
    }
    // else TODO: some error mechanism

    std::cout << "Opt::addOptEntry3 <int> END" << std::endl;
}

template <> void Opt::addOptEntry<int> (const std::string  optLong,
                                        const char optShort,
                                        int &target,
                                        Validator<int> *validatorFn)
{
    std::cout << "Opt::addOptEntry4 <int> START" << std::endl;

    OptEntryBase *opt = new OptEntryInt(optLong, optShort, target, validatorFn);
    if (opt != nullptr)
    {
        entries.push_back(opt);
    }
    // else TODO: some error mechanism

    std::cout << "Opt::addOptEntry4 <int> END" << std::endl;
}

template <> void Opt::addOptEntry<int> (const std::string  optLong,
                                        const char optShort,
                                        int &target,
                                        std::function<bool(int)> validatorFn)
{
    std::cout << "Opt::addOptEntryC4 <int> START" << std::endl;

    this->addOptEntry<int>(optLong, optShort, target, CustomValidator<int>(validatorFn));

    std::cout << "Opt::addOptEntryC4 <int> END" << std::endl;
}

// Add definition to avoid linker errors
template void Opt::addOptEntry<int> (const std::string  optLong,
                                     const char optShort,
                                     int &target);

// Add definition to avoid linker errors
template void Opt::addOptEntry<int> (const std::string  optLong,
                                     const char optShort,
                                     int &target,
                                     Validator<int> *validatorFn);

// Add definition to avoid linker errors
template void Opt::addOptEntry<int> (const std::string  optLong,
                                     const char optShort,
                                     int &target,
                                     std::function<bool(int)> validatorFn);

int Opt::parseOpt(int argc, const char* argv[])
{
    int retVal = 0;
    const char  *argvPtr;
    std::string  argStr;
    std::string  valStr;
    char         argChar;

    // TODO:
    // trim each argv
    // add some bool or whatever to state whether option value is mandatory (is this needed?)
    // default value for each option?

    std::cout << "Opt::parseOpt START, argc = " << argc << std::endl;

    for (int i = 1; i < argc; i++)
    {
        argvPtr = this->getOption(argv[i], argStr, argChar);

        // Test if option found
        if (argvPtr != argv[i])
        {
            // option found, get value
            std::cout << "Opt::parseOpt option found, long: " << argStr << ", short: " << argChar << std::endl;

            // TODO: value optional or mandatory?

            if (argc > i+1)
            {
                // Some string present, maybe value, get it for parsing
                // Move iterator
                i++;
                std::cout << "Opt::parseOpt potential value string found: " << argv[i] << std::endl;
                valStr = std::string(argv[i]);
            }
            else
            {
                // No value string, need to trigger error if value is mandatory
                std::cout << "Opt::parseOpt no value found" << std::endl;
                valStr = std::string("");

                // TODO: trigger error if the value is mandatory
            }

            //for (auto&& e : entries)
            for (OptEntryBase *e : entries)
            {
                std::cout << "optEntry START" << std::endl;
                retVal = e->parseOpt(argStr, argChar, valStr); // TODO: is this ok?
                std::cout << "optEntry END" << std::endl;

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
        else
        {
            // Option not found, we have got string to store
            std::cout << "Opt::parseOpt option not found, argv: " << argStr << ", short: " << argChar << std::endl;
        }
    }

    std::cout << "Opt::parseOpt END, return code = " << retVal << std::endl;

    return retVal;
}

} /* namespace ifx */
