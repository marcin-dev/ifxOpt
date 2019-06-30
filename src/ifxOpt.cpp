/**
 * ifxOpt.cpp
 *
 * @date   2019.06
 * @author man
 */

#include <iostream>

#include "ifxOpt.h"

namespace ifx
{

#define OPTIONS_HELP_LEN_INDENT_START   ((size_t)2)
#define OPTIONS_HELP_LEN_INDENT_END     ((size_t)26)

Opt::Opt(OptionSet options, const std::string helpHeader)
: entries(),
  usedEntries(),
  helpHeader(helpHeader),
  mAssignCharAllowed(IFX_OPTION_CHECK(options, IFX_OPT_ALLOW_ARG_ASSIGN_CHAR))
{
    // TODO Auto-generated constructor stub
}

Opt::~Opt()
{
    // Cleanup all allocated entries
    for (OptEntryBase *e : entries)
    {
        delete e;
    }
    for (OptEntryBase *e : usedEntries)
    {
        delete e;
    }
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

            // If '=' is allowed, need to search for it and clear remaining characters
            if (this->mAssignCharAllowed == true)
            {
                size_t pos = argStr.find_first_of('=');
                if (pos != std::string::npos)
                {
                    argStr.erase(pos);
                }
            }

            in += argStr.length();
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

void Opt::printHelpAndExit(const char *argv0, int exitStatus) const
{
    this->printHelpAndExit(argv0, exitStatus, this->helpHeader);
}

void Opt::printHelpAndExit(const char *argv0, int exitStatus, std::string headerStr) const
{
    if (headerStr.empty() == false)
    {
        std::cout << headerStr << "\n\n";
    }

    std::string usageString = std::string("Usage: ").append(argv0);
    std::string optionsHelp = "Options:\n";

    for (const OptEntryBase * const &e : entries)
    {
        bool addPipeChar = false;
        std::string optionUsageString = "<";

        // TODO: Move these constructions to some new OptEntryBase class method
        if (e->getOptShort() != '\0')
        {
            optionUsageString += "-";
            optionUsageString += e->getOptShort();
            addPipeChar = true;
        }

        if (e->getOptLong().empty() == false)
        {
            if (addPipeChar == true)
            {
                optionUsageString += '|';
            }
            optionUsageString += "--";
            optionUsageString += e->getOptLong();
        }


        if (e->isFlag() == true)
        {
            // Value argument is optional only for FLAG entries (boolean)
            optionUsageString.append(" [" + e->getValName() + "]");
        }
        else
        {
            // Value is mandatory for all entries by default
            optionUsageString.append(" <" + e->getValName() + ">");
        }

        if (e->isMandatory() == true)
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

        //usageString.append(1, ' ');
        //usageString.append(optionUsageString);
        usageString += " " + optionUsageString;

        if (optionUsageString.length() < (OPTIONS_HELP_LEN_INDENT_END - OPTIONS_HELP_LEN_INDENT_START))
        {
            // Fill with spaces up to (OPTIONS_HELP_LEN_INDENT_END - OPTIONS_HELP_LEN_INDENT_START)
            optionUsageString.append(OPTIONS_HELP_LEN_INDENT_END - OPTIONS_HELP_LEN_INDENT_START - optionUsageString.length(), ' ');
        }
        else
        {
            optionUsageString.push_back('\n');
            optionUsageString.append(OPTIONS_HELP_LEN_INDENT_END, ' ');
        }

        optionsHelp.append(OPTIONS_HELP_LEN_INDENT_START, ' ');
        optionsHelp += optionUsageString;

        // Need to shift each newline to the OPTIONS_HELP_LEN_INDENT_END
        // to keep nice alignment
        for (auto it = e->getHelpString().cbegin() ; it != e->getHelpString().cend() ; it++ )
        {
            optionsHelp.append(1, *it);
            if (*it == '\n')
            {
                optionsHelp.append(OPTIONS_HELP_LEN_INDENT_END, ' ');
            }
        }

        optionsHelp.append(1, '\n');
    }

    std::cout << usageString << "\n";
    std::cout << optionsHelp << "\n";
    std::cout << std::endl;

    exit(exitStatus);
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
    const char  *optArgv;
    char         argChar;

    // TODO:
    // trim each argv

    std::cout << "Opt::parseOpt START, argc = " << argc << std::endl;

    for (int i = 1; i < argc; i++)
    {
        argvPtr = this->getOption(argv[i], argStr, argChar);

        // Test if option found
        if (argvPtr != argv[i])
        {
            // option found
            optArgv = argv[i];

            // check if it is help
            if (   argStr.compare("help") == 0
                || argChar == 'h')
            {
                // display help and exit program
                this->printHelpAndExit(argv[0], IFX_OPT_RESULT_SUCCESS);
            }

            std::cout << "Opt::parseOpt option found, long: " << argStr << ", short: " << argChar << std::endl;

            //for (auto&& e : entries)
            for (OptEntryBase *&e : entries)
            {
                std::cout << "optEntry START" << std::endl;
                retVal = e->parseOpt(argStr, argChar);
                std::cout << "optEntry END" << std::endl;

                if (retVal != IFX_OPT_RESULT_SUCCESS)
                {
                    continue;
                }

                // Additional checks for '=' character and no space before value for short options
                if (this->mAssignCharAllowed == true && *argvPtr == '=')    // condition for both short and long options
                {
                    argvPtr++;
                    valStr = std::string(argvPtr);
                }
                else if (argChar != 0 && *argvPtr != '\0')                  // condition for short option only

                {
                    valStr = std::string(argvPtr);
                }
                else
                {
                    if (argc > i+1)
                    {
                        // Some string present, maybe value, get it for parsing
                        i++;
                        valStr = std::string(argv[i]);
                    }
                    else
                    {
                        // No value string, need to trigger error if value is mandatory
                        std::cout << "Opt::parseOpt no value found" << std::endl;

                        // Special case for flag entries
                        if (e->isFlag() == true)
                        {
                            std::cout << "Opt::parseOpt flag entry, setting value to true" << std::endl;

                            valStr = std::string("true"); // set true for all flags that are present
                        }
                        else
                        {
                            std::cout << "Opt::parseOpt no flag entry, raising error" << std::endl;

                            // Value argument not found, display the error, print help and exit
                            this->printHelpAndExit(argv[0], IFX_OPT_VALUE_NOT_FOUND, std::string("No value found for option: ") + optArgv);
                        }

                        // TODO: trigger error if the value is mandatory
                    }
                }

                std::cout << "Opt::parseOpt potential value string found: " << valStr << std::endl;

                retVal = e->parseValue(valStr); // run the virtual method to parse value
                if (retVal == IFX_OPT_RESULT_SUCCESS)
                {
                    // Found match and extracted the value successfully
                    // Or parsing error
                    break;
                }
                else
                {
                    this->printHelpAndExit(argv[0], retVal, std::string("Parsing value error, option: ") + optArgv + ", incorrect value string: " + valStr);
                }
            }

            if (retVal == IFX_OPT_NOT_MACHING_OPTION)
            {
                // Option not found, display the error, print help and exit
                this->printHelpAndExit(argv[0], IFX_OPT_NOT_MACHING_OPTION, std::string("Unrecognized option: ") + optArgv);
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
