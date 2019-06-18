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

int parseOpt(int argc, const char **argv)
{
    ifx::Opt opt;
    int number;
    int retVal;

    //ifx::Custom2Validator<int, validateNumber> cv;

    //opt.addOptEntry<int>("number", 'n', number, ifx::Custom2Validator<int, validateNumber>::get(&validateNumber));
    //opt.addOptEntry<int>("number", 'n', number, ifx::Custom2Validator<int, validateNumber>());

    opt.addOptEntry<int>("number", 'n', number, validateNumber);
    //opt.addOptEntry<int>("number", 'n', number); // will use default validator

    retVal = opt.parseOpt(argc, argv);

    if (retVal == 0)
    {
        std::cout << LOG_TAG "parsed number: " << number << std::endl;
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
