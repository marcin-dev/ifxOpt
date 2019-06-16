/**
 * ifxOpt.h
 *
 * @date   2019.04
 * @author man
 */

#ifndef INCLUDE_IFXOPT_H
#define INCLUDE_IFXOPT_H

#include <vector>

#include "ifxOptEntry.h"
#include "ifxValidator.h"

namespace ifx
{

class Opt
{
private:
    std::vector<OptEntry *> entries;

    const char *getOption(const char* in, std::string &argStr, char &argChar);

public:
    Opt();
    virtual ~Opt();

    template <typename T> void addOptEntry(const std::string  optLong,
                                           const char optShort,
                                           T &target);

    template <typename T> void addOptEntry(const std::string  optLong,
                                           const char optShort,
                                           T &target,
                                           Validator<T> &validatorFn);

    int parseOpt(int argc, const char* argv[]);
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_H */
