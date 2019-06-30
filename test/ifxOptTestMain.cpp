/**
 * ifxOptTestMain.cpp
 *
 * @date   2019.04
 * @author man
 */

#include <iostream>

#include <ifxOpt.h>

#define LOG_TAG     " >>> [IFX TEST] "

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

int parseOpt(int argc, const char **argv)
{
    ifx::Opt opt(IFX_OPT_ALLOW_ARG_ASSIGN_CHAR, "Option Parser ifx::Opt test program");
    int number;
    int retVal;
    std::string text;

    opt.addOptEntry<int>("number", 'n', "value",
                         "Any integer number between -10 and 10",
                         number, IFX_OPTION_SET_CLEAR, validateNumber);
    //opt.addOptEntry<int>("number", 'n', number);
    //opt.addOptEntry<std::string>("text", 't', text, validateText);
    opt.addOptEntry<std::string>("text", 't', "anything",
                                 "Any text is accepted",
                                 text, IFX_OPTION_SET_CLEAR);

    retVal = opt.parseOpt(argc, argv);

    if (retVal == IFX_OPT_RESULT_SUCCESS)
    {
        std::cout << LOG_TAG "parsed number: " << number << std::endl;
        std::cout << LOG_TAG "parsed text  : " << text << std::endl;
    }

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
