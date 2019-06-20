/**
 * ifxOpt.cpp
 *
 * @date   2019.06
 * @author man
 */

#include <iostream>

#include "ifxOpt.h"
#include "internal/ifxCustomValidator.h"

namespace ifx
{

Opt::Opt() : entries()
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
// Option type generic templates are defined in internal/internal_ifxOpt.h
// ****************************************************************************

int Opt::parseOpt(int argc, const char* argv[])
{
    int retVal = IFX_OPT_RESULT_SUCCESS;
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

                if (retVal == IFX_OPT_NOT_MACHING_OPTION)
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

            if (retVal < IFX_OPT_RESULT_SUCCESS) // TODO: != unknown option
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
