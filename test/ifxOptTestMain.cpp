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
    ifx::Opt opt("Option Parser ifx::Opt test program");
    int number;
    int retVal;
    std::string text;

    opt.addOptEntry<int>("number", 'n', number, validateNumber);
    //opt.addOptEntry<int>("number", 'n', number);
    //opt.addOptEntry<std::string>("text", 't', text, validateText);
    opt.addOptEntry<std::string>("text", 't', text);

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
