/**
 * ifxOptEntry.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFXOPT_ENTRY_H
#define INCLUDE_IFXOPT_ENTRY_H

#include <string>

#include "ifxValidator.h"

namespace ifx
{

class OptEntryBase
{
private:
    const std::string  optLong;
    const char         optShort;

public:
    OptEntryBase(const std::string  optLong,
                 const char optShort);
    virtual ~OptEntryBase();

    int parseOpt(const std::string &argStr, const char argShort, const std::string &valStr);

    virtual int parseOpt(const std::string &valStr) = 0;
};

template <typename T>
class OptEntry : public OptEntryBase
{
protected:
    T                 &target;
    Validator<T>      *validator;

public:
    OptEntry(const std::string  optLong,
             const char optShort,
             T &target,
             Validator<T> *validator = nullptr);

    virtual ~OptEntry();

    virtual int parseOpt(const std::string &valStr);

    // The following function needs to be defined in each type-specific implementation
    int parseValue(const std::string &valStr, T &value);
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_ENTRY_H */
