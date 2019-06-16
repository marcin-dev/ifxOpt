/**
 * ifxOptTestMain.cpp
 *
 * @date   2019.04
 * @author man
 */

#include <iostream>

#include <ifxOpt.h>

#define LOG_TAG     " >>> [IFX TEST] "

int parseOpt(int argc, const char **argv)
{
    ifx::Opt opt;
    int number;
    int retVal;

    opt.addOptEntry<int>("number", 'n', number);

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
