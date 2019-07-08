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
#include "ifxValidator.h"
#include "utils/ifxSharedPtr.h"

namespace ifx
{

class Opt
{
private:
    std::vector<SharedPtr<OptEntryBase>> mEntries;
    std::vector<SharedPtr<OptEntryBase>> mUsedEntries;
    const std::string helpHeader;
    const std::string helpEndnote;
    const bool  mAssignCharAllowed;         // can be configured, tells if there can be a '=' character before option and value arguments
    const bool  mNoExitOnError;             // can be configured, tells if the program should exit on parsing error

    const char *getOption(const char* in, std::string &argStr, char &argChar);

    int verifyAfterParsing(const char *argv0) const;

    std::string *generateHelp(const char *argv0, std::string headerStr = std::string(), std::string footerStr = std::string()) const;
    void printHelpAndExitConditionally(const char *argv0, int exitStatus) const;

    // Non-copyable
    Opt(const Opt &);

public:
    Opt(OptionSet options = IFX_OPTION_SET_CLEAR, const std::string helpHeader = std::string(), std::string helpEndnote = std::string());
    virtual ~Opt();

    template <typename T>
    int addOptEntry(const std::string  optLong,
                    const char         optShort,
                    const std::string  valName,
                    std::string        helpString,
                    T                 &target,
                    OptionSet          options,
                    Validator<T>      *validatorFn = nullptr);

    template <typename T>
    int addOptEntry(const std::string  optLong,
                    const char         optShort,
                    const std::string  valName,
                    std::string        helpString,
                    T                 &target,
                    OptionSet          options,
                    std::function<bool(T)> validatorFn);

    int parseOpt(int argc, const char* argv[]);

    void printHelpAndExit(const char *argv0, int exitStatus) const;
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_H */
