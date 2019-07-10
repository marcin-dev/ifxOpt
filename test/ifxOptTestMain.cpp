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
    int number1 = -50;
    int number2 = -60;
    int number3 = -70;
    int retVal;
    std::string text = "not changed";


    int  a[] = {1,2,3};
    //int *b   = {4,5,6};

    //std::vector<int> test1 = a;
    //std::vector<int> test2 = b;
    std::vector<int> test3 = { 7,8,9 };
//    std::cout << "test3 size:" << test3.size() << std::endl;
//
//    std::cout << "The contents of test3 are:";
//    for (std::vector<int>::iterator it = test3.begin(); it != test3.end(); ++it)
//      std::cout << ' ' << *it;
//    std::cout << '\n';

    opt.addOptEntry<int>("number", 'n', "value",
                         "Any integer number between -10 and 10",
                         number1, IFX_OPT_ENTRY_MANDATORY, validateNumber);
    opt.addOptEntry<std::string>("text", 't', "anything",
                                 "Any text is accepted",
                                 text, IFX_OPTION_SET_CLEAR);

    opt.addOptEntry<int>("enum", 'e', "choice",
                         "Number in range 1-3",
                         number2, {1,2,3,-1}, IFX_OPTION_SET_CLEAR);

    opt.addOptEntry<int>("charenum", 'c', "choice",
                         "Number in range 1-3",
                         number3, test3, IFX_OPTION_SET_CLEAR);
//    opt.addOptEntry<std::string>("text", 't', "anything",
//                                 "Any text is accepted",
//                                 text, IFX_OPTION_SET_CLEAR, validateText);

    retVal = opt.parseOpt(argc, argv);

    //if (retVal == IFX_OPT_RESULT_SUCCESS)
    //{
        std::cout << LOG_TAG "parsed number1: " << number1 << std::endl;
        std::cout << LOG_TAG "parsed number2: " << number2 << std::endl;
        std::cout << LOG_TAG "parsed number3: " << number3 << std::endl;
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
