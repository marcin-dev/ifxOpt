/**
 * ifxOptEntry.h
 *
 * @date   2019.07
 * @author man
 */

#ifndef INTERNAL_IFXOPT_ENTRY_H
#define INTERNAL_IFXOPT_ENTRY_H

#include <ifxOptEntryBase.h>
#include "ifxValidator.h"

namespace ifx
{

template <typename T>
class OptEntry : public OptEntryBase
{
protected:
    T                 &mTarget;
    Validator<T>      *mValidator;

public:
    OptEntry(const std::string  optLong,
             const char         optShort,
             const std::string  valName,
             std::string        helpString,
             T                 &target,
             OptionSet          options,
             Validator<T>      *validator = nullptr);

    virtual ~OptEntry();

    virtual int parseValue(const std::string &valStr);

    // The following function needs to be defined in each type-specific implementation
    int parseValueTypeImpl(const std::string &valStr, T &value);
};

} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_ENTRY_H */
