/**
 * ifxOpt.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFXOPT_H
#define INCLUDE_IFXOPT_H

#include <vector>
#include <functional>

#include "ifxOptEntryBase.h"
#include "ifxOptResultCodes.h"
#include "ifxOptOptionCodes.h"
#include "utils/ifxSharedPtr.h"

namespace ifx
{

class Opt
{
private:
    const unsigned int mId;                                 // global object id
    std::vector<SharedPtr<OptEntryBase>> mEntries;          // option arguments added by user
    std::vector<SharedPtr<OptEntryBase>> mUsedEntries;      // all recognized option argument entries are added here
    std::vector<SharedPtr<ArgEntryBase>> mArgs;             // non-option argument entries added by user
    std::vector<SharedPtr<ArgEntryBase>> mUsedArgs;         // all recognized non-option argument entries are added here
    const std::string helpHeader;                           // header passed by user or empty string
    const std::string helpEndnote;                          // footer passed by user of empty string
    const bool  mAssignCharAllowed;         // can be configured, tells if there can be a '=' character before option and value arguments
    const bool  mNoExitOnError;             // can be configured, tells if the program should exit on parsing error
    const bool  mEnforceStrictOrder;        // can be configured, tells if options and arguments must be given in strict order

    const char *getOption(const char* in, std::string &argStr, char &argChar);

    int verifyAfterParsing(const char *argv0) const;

    std::string *generateHelp(const char *argv0, std::string headerStr = std::string(), std::string footerStr = std::string()) const;
    void printHelpAndExitConditionally(const char *argv0, int exitStatus);

    // Non-copyable
    Opt(const Opt &);

public:
    Opt(OptionSet options = IFX_OPTION_SET_CLEAR, const std::string helpHeader = std::string(), std::string helpEndnote = std::string());
    virtual ~Opt();

    template <typename T>
    int addOptEntry(const std::string  optLong,
                    const char         optShort,
                    const std::string  valName,
                    const std::string  helpString,
                    T                 &target,
                    OptionSet          options = IFX_OPTION_SET_CLEAR,
                    std::function<bool(T)> validatorFn = nullptr);

    template <typename T>
    int addOptEntry(const std::string  optLong,
                    const char         optShort,
                    const std::string  helpString,
                    T                 &target,
                    std::vector<T>     choices,
                    OptionSet          options = IFX_OPTION_SET_CLEAR);

    template <typename T>
    int addOptEntry(const std::string  optLong,
                    const char         optShort,
                    const std::string  valName,
                    const std::string  helpString,
                    T                 &target,
                    const T           *choices,
                    size_t             choicesSize,
                    OptionSet          options = IFX_OPTION_SET_CLEAR);

    int addArgEntry(const std::string  valName,
                    const std::string  helpString,
                    std::string       &target,
                    OptionSet          options = IFX_OPTION_SET_CLEAR,
                    std::function<int(const std::string &)> notifierFn = nullptr);

    int parseOpt(int argc, const char* argv[]);

    void printHelpAndExit(const char *argv0, int exitStatus);
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_H */
