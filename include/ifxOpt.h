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

#include "ifxOptResultCodes.h"
#include "ifxOptEntry.h"
#include "ifxValidator.h"

namespace ifx
{

class Opt
{
private:
    std::vector<OptEntryBase *> entries;
    std::string helpHeader;

    const char *getOption(const char* in, std::string &argStr, char &argChar);

    void printHelpAndExit(const char *argv0, int exitStatus) const;
    void printHelpAndExit(const char *argv0, int exitStatus, std::string headerStr) const;

    // Non-copyable
    Opt(const Opt &);

public:
    Opt(const std::string helpHeader = "");
    virtual ~Opt();

    template <typename T>
    void addOptEntry(const std::string  optLong,
                     const char         optShort,
                     const std::string  valName,
                     std::string        helpString,
                     T                 &target,
                     bool               mandatory = false,
                     bool               valMandatory = false,
                     Validator<T>      *validatorFn = nullptr);

    template <typename T>
    void addOptEntry(const std::string  optLong,
                     const char         optShort,
                     const std::string  valName,
                     std::string        helpString,
                     T                 &target,
                     bool               mandatory,
                     bool               valMandatory,
                     std::function<bool(T)> validatorFn);

    int parseOpt(int argc, const char* argv[]);
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_H */
