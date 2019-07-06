/**
 * ifxOpt.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFXOPT_H
#define INCLUDE_IFXOPT_H

#include <list>
#include <functional>

#include "ifxOptResultCodes.h"
#include "ifxOptOptionCodes.h"
#include "ifxOptEntry.h"
#include "ifxValidator.h"

namespace ifx
{

class Opt
{
private:
    std::list<OptEntryBase *> entries;
    std::list<OptEntryBase *> usedEntries;
    std::string helpHeader;
    const bool  mAssignCharAllowed;             // tells if there can be a '=' character before option and value arguments

    const char *getOption(const char* in, std::string &argStr, char &argChar);

    void verifyAfterParsing(const char *argv0) const;

    void printHelpAndExit(const char *argv0, int exitStatus) const;
    void printHelpAndExit(const char *argv0, int exitStatus, std::string headerStr) const;

    // Non-copyable
    Opt(const Opt &);

public:
    Opt(OptionSet options = IFX_OPTION_SET_CLEAR, const std::string helpHeader = "");
    virtual ~Opt();

    template <typename T>
    void addOptEntry(const std::string  optLong,
                     const char         optShort,
                     const std::string  valName,
                     std::string        helpString,
                     T                 &target,
                     OptionSet          options,
                     Validator<T>      *validatorFn = nullptr);

    template <typename T>
    void addOptEntry(const std::string  optLong,
                     const char         optShort,
                     const std::string  valName,
                     std::string        helpString,
                     T                 &target,
                     OptionSet          options,
                     std::function<bool(T)> validatorFn);

    int parseOpt(int argc, const char* argv[]);
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_H */
