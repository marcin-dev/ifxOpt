/**
 * ifxOptTestMain.cpp
 *
 * @date   2019.04
 * @author man
 */

#include <iostream>

#include <ifxOpt.h>

#define LOG_TAG     " >>> [IFX_TEST] "

bool validateNumber(int val)
{
    std::cout << LOG_TAG "validateNumber" << std::endl;

    if (val >= -10 && val <=10)
        return true;

    return false;
}

bool validateText(std::string val)
{
    std::cout << LOG_TAG "validateText" << std::endl;

    return true;
}

static const char *helpEndnote =
"Copyright: InFoX\n\
2019";

int parseOpt(int argc, const char **argv)
{
    //ifx::OptionSet optionSet = IFX_OPT_ALLOW_ARG_ASSIGN_CHAR | IFX_OPT_NO_EXIT_ON_ERROR;
    ifx::OptionSet optionSet = IFX_OPT_ALLOW_ARG_ASSIGN_CHAR;
    ifx::Opt opt(optionSet, "Option Parser ifx::Opt test program", helpEndnote);
    int number = -50;
    int retVal;
    std::string text = "not changed";

    opt.addOptEntry<int>("number", 'n', "value",
                         "Any integer number between -10 and 10",
                         number, IFX_OPT_ENTRY_MANDATORY, validateNumber);
    opt.addOptEntry<std::string>("text", 't', "anything",
                                 "Any text is accepted",
                                 text, IFX_OPTION_SET_CLEAR);
//    opt.addOptEntry<std::string>("text", 't', "anything",
//                                 "Any text is accepted",
//                                 text, IFX_OPTION_SET_CLEAR, validateText);

    retVal = opt.parseOpt(argc, argv);

    //if (retVal == IFX_OPT_RESULT_SUCCESS)
    //{
        std::cout << LOG_TAG "parsed number: " << number << std::endl;
        std::cout << LOG_TAG "parsed text  : " << text << std::endl;
    //}

    return retVal;
}


int main(int argc, const char **argv)
{
    int retVal;

    std::cout << LOG_TAG "START" << std::endl;

    retVal = parseOpt(argc, argv);

    std::cout << LOG_TAG "END, return code = " << retVal << std::endl;

    return retVal;
}
