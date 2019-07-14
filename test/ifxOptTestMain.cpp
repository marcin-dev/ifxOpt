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

bool validateNonOptArgText(const std::string &val)
{
    std::cout << LOG_TAG "validateNonOptArgText " << val << std::endl;

    return IFX_OPT_RESULT_SUCCESS;
}

static const char *helpEndnote =
"Copyright: InFoX\n\
2019";

int parseOpt(int argc, const char **argv)
{
    ifx::OptionSet optionSet = IFX_OPT_ALLOW_ARG_ASSIGN_CHAR | IFX_OPT_NO_EXIT_ON_ERROR | IFX_OPT_STRICT_ORDER;
    //ifx::OptionSet optionSet = IFX_OPT_ALLOW_ARG_ASSIGN_CHAR | IFX_OPT_STRICT_ORDER;
    //ifx::OptionSet optionSet = IFX_OPT_ALLOW_ARG_ASSIGN_CHAR;
    ifx::Opt opt(optionSet, "Option Parser ifx::Opt test program", helpEndnote);
    int number1 = -50;
    int number2 = -60;
    int number3 = -70;
    int retVal;
    std::string text  = "not changed";
    std::string text2 = "not changed2";

    std::string nonopttext1 = "not changed a1";
    std::string nonopttext2 = "not changed a2";


    int  a[] = {1,2,3};

    std::vector<int> test3 = { 7,8,9 };

    opt.addOptEntry<int>("number", 'n', "value",
                         "Any integer number between -10 and 10",
                         number1, IFX_OPT_ENTRY_MANDATORY, validateNumber);
    opt.addOptEntry<std::string>("text", 't', "anything",
                                 "Any text is accepted",
                                 text, IFX_OPTION_SET_CLEAR);

    opt.addOptEntry<int>("enum", 'e',
                         "Number in range 1-3",
                         number2, {1,2,3,-1}, IFX_OPTION_SET_CLEAR);

    opt.addOptEntry<int>("", 'c',
                         "Number in range 1-3",
                         number3, test3, IFX_OPTION_SET_CLEAR);

    opt.addOptEntry<std::string>("stringenum", 's',
                         "Number in range 1-3",
                         text2, {"aa", "bb", "cc"}, IFX_OPTION_SET_CLEAR);
    opt.addOptEntry<std::string>("text", 't', "anything",
                                 "Any text is accepted",
                                 text, IFX_OPTION_SET_CLEAR, validateText);

    opt.addArgEntry("noptarg1",
                    "Any text is accepted",
                    nonopttext1, IFX_OPT_ENTRY_MANDATORY, validateNonOptArgText);

    opt.addArgEntry("noptarg2",
                    "Any text is accepted",
                    nonopttext2, IFX_OPTION_SET_CLEAR, validateNonOptArgText);

    retVal = opt.parseOpt(argc, argv);

    //if (retVal == IFX_OPT_RESULT_SUCCESS)
    //{
        std::cout << LOG_TAG "parsed number1: " << number1 << std::endl;
        std::cout << LOG_TAG "parsed number2: " << number2 << std::endl;
        std::cout << LOG_TAG "parsed number3: " << number3 << std::endl;
        std::cout << LOG_TAG "parsed text  : " << text  << std::endl;
        std::cout << LOG_TAG "parsed text  : " << text2 << std::endl;
        std::cout << LOG_TAG "noptarg1 text  : " << nonopttext1  << std::endl;
        std::cout << LOG_TAG "noptarg2 text  : " << nonopttext2 << std::endl;
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
