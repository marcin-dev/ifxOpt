/**
 * ifxOpt.cpp
 *
 * @date   2019.06
 * @author man
 */

#include <algorithm>
#include <memory>

#include <ifxOpt.h>

#include "internal/ifxDbg.h"

namespace ifx
{

#define OPTIONS_HELP_LEN_INDENT_START   ((size_t)2)
#define OPTIONS_HELP_LEN_INDENT_END     ((size_t)26)

Opt::Opt(OptionSet options, const std::string helpHeader, std::string helpEndnote)
: entries(),
  usedEntries(),
  helpHeader (helpHeader),
  helpEndnote(helpEndnote),
  mAssignCharAllowed(IFX_OPTION_CHECK(options, IFX_OPT_ALLOW_ARG_ASSIGN_CHAR)),
  mNoExitOnError    (IFX_OPTION_CHECK(options, IFX_OPT_NO_EXIT_ON_ERROR))
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

int Opt::verifyAfterParsing(const char *argv0) const
{
    int ret = IFX_OPT_RESULT_SUCCESS;

    // Check for missed mandatory entries
    for (const OptEntryBase * const &e : this->entries) // could wrote auto e, but wanted to learn the explicit type
    {
        if (e->isMandatory() == true)
        {
            // Check if the mandatory option argument is consumed
            auto it = std::find(this->usedEntries.begin(), this->usedEntries.end(), e);
            if (it == this->usedEntries.end())
            {
                // Not fund on the consumed list, error
                std::string optionUsageString;
                e->getUsageString(optionUsageString);

                IFX_LOG_ERR(std::string("The following mandatory option is missing: ") + optionUsageString);

                ret = IFX_OPT_NOT_FOUND;
            }
        }
    }

    return ret;
}

std::string *Opt::generateHelp(const char *argv0, std::string headerStr, std::string footerStr) const
{
    std::string *help = new std::string();

    if (help != nullptr)
    {
        if (headerStr.empty() == false)
        {
            help->append(headerStr + "\n\n");
        }

        help->append("Usage: ").append(argv0);

        std::string optionsHelp = "Options:";

        for (const OptEntryBase * const &e : entries)
        {
            std::string optionUsageString;

            e->getUsageString(optionUsageString);

            if (e->isMandatory() == true)
            {
                *help += " <" + optionUsageString + ">";
            }
            else
            {
                *help += " [" + optionUsageString + "]";
            }

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

            optionsHelp.append(1, '\n');
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
        }

        *help += "\n\n" + optionsHelp;

        if (footerStr.empty() == false)
        {
            *help += "\n\n" + footerStr;
        }
    }

    return help;
}

void Opt::printHelpAndExit(const char *argv0, int exitStatus) const
{
    std::unique_ptr<std::string> helpUPtr(this->generateHelp(argv0, this->helpHeader, this->helpEndnote));

    std::cout << *helpUPtr << std::endl;

    IFX_LOG_DBG("Exiting with code: " << exitStatus);
    exit(exitStatus);
}

void Opt::printHelpAndExitConditionally(const char *argv0, int exitStatus) const
{
    std::unique_ptr<std::string> helpUPtr(this->generateHelp(argv0));

    std::cout << *helpUPtr << std::endl;

    if (mNoExitOnError == false)
    {
        IFX_LOG_DBG("Exiting with code: " << exitStatus);
        exit(exitStatus);
    }
}

// ****************************************************************************
// Option type generic templates are defined in internal/internal_ifxOpt.h
// ****************************************************************************

int Opt::parseOpt(int argc, const char* argv[])
{
    int retVal = IFX_OPT_RESULT_SUCCESS;
    int result;
    const char  *argvPtr;
    std::string  argStr;
    std::string  valStr;
    const char  *optArgv;
    char         argChar;

    // TODO:
    // trim each argv

    IFX_LOG_DBG("Opt::parseOpt START, argc = " << argc);

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

            IFX_LOG_DBG("Opt::parseOpt option found, long: " << argStr << ", short: " << argChar);

            //for (auto&& e : entries)
            for (OptEntryBase *&e : entries)
            {
                IFX_LOG_DBG("optEntry START");
                result = e->parseOpt(argStr, argChar);
                IFX_LOG_DBG("optEntry END");

                if (result != IFX_OPT_RESULT_SUCCESS)
                {
                    continue;
                }

                // Additional checks for '=' character and no space before value for short options
                if (this->mAssignCharAllowed == true && *argvPtr == '=')    // condition for both short and long options
                {
                    argvPtr++;  // +1 to skip '=' character
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
                        // Some string present, potential value, get it for parsing
                        i++;
                        argvPtr = argv[i];  // this assignment is done for Parsing the Value check
                        valStr = std::string(argvPtr);
                    }
                    else
                    {
                        // No value string, need to trigger error if opt is not a string
                        IFX_LOG_DBG("Opt::parseOpt no value found");

                        // Special case for flag entries
                        if (e->isFlag() == true)
                        {
                            IFX_LOG_DBG("Opt::parseOpt flag entry, setting value to true");

                            valStr = std::string("true"); // set true for all flags that are present
                        }
                        else
                        {
                            IFX_LOG_DBG("Opt::parseOpt no flag entry, raising error");

                            // Value argument not found, display the error, print help and exit
                            IFX_LOG_ERR(std::string("No value found for option: ") + optArgv);

                            if (retVal == IFX_OPT_RESULT_SUCCESS)
                            {
                                retVal = IFX_OPT_VALUE_NOT_FOUND;
                            }

                            // Need to exit the loop if there is error+exit condition
                            if (mNoExitOnError == false)
                            {
                                break;
                            }
                        }

                        // TODO: trigger error if the value is mandatory
                    }
                }

                IFX_LOG_DBG("Opt::parseOpt potential value string found: " << valStr);

                //
                // Parsing the Value
                //
                result = e->parseValue(valStr); // run the virtual method to parse value

                // Special case for flag option type:
                if (   e->isFlag() == true
                    && result      == IFX_OPT_ERROR_VALUE_CANNOT_EXTRACT    // -> it is ok if the value cannot be extracted and value str is potentially
                    && argv[i]     == argvPtr)                              // -> next option argument (flags may not have value string argument at all)
                                                                            //   EXAMPLE1: --<FLAG>=<WRONG_VALUE> or -F<WRONG_VALUE> will fail this check, but
                                                                            //   EXAMPLE2: --<FLAG> <SOMETHING> will pass and <FLAG> will be set to true;
                                                                            //             (in this case <SOMETHING> is considered as next option)
                {
                    result = IFX_OPT_RESULT_SUCCESS;
                }


                if (result == IFX_OPT_RESULT_SUCCESS)
                {
                    // Found match and extracted the value successfully

                    // Copy the entry pointer to consumed list
                    this->usedEntries.push_back(e);

                    break;
                }
                else
                {
                    IFX_LOG_ERR(std::string("Parsing value error, option: ") + optArgv + ", incorrect value string: " + valStr);
                    if (retVal == IFX_OPT_RESULT_SUCCESS)
                    {
                        retVal = result;
                    }

                    // Need to exit the loop if there is error+exit condition
                    if (mNoExitOnError == false)
                    {
                        break;
                    }
                }
            }

            if (result == IFX_OPT_NOT_MACHING_OPTION)
            {
                // Option not found, display the error, print help and exit
                IFX_LOG_ERR(std::string("Unrecognized option: ") + optArgv);

                if (retVal == IFX_OPT_RESULT_SUCCESS)
                {
                    retVal = result;
                }

                // Need to exit the main loop if there is error+exit condition
                if (mNoExitOnError == false)
                {
                    break;
                }
            }
            else if (result != IFX_OPT_RESULT_SUCCESS)
            {
                // Need to exit the main loop if there is error+exit condition
                if (mNoExitOnError == false)
                {
                    break;
                }
            }
        }
        else
        {
            // Option not found, we have got string to store
            IFX_LOG_DBG("Opt::parseOpt option not found, argv: " << argStr << ", short: " << argChar);
        }
    }

    // Post verification, only if there are no errors or exit is not requested
    if (   retVal == IFX_OPT_RESULT_SUCCESS
        || mNoExitOnError == true)
    {
        result = this->verifyAfterParsing(argv[0]);
        if (retVal == IFX_OPT_RESULT_SUCCESS)
        {
            retVal = result;
        }
    }

    if (retVal != IFX_OPT_RESULT_SUCCESS)
    {
        this->printHelpAndExitConditionally(argv[0], retVal);
    }

    IFX_LOG_DBG("Opt::parseOpt END, return code = " << retVal);

    return retVal;
}

} /* namespace ifx */
