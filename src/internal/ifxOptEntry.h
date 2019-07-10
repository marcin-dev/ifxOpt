/**
 * ifxOptEntry.h
 *
 * @date   2019.07
 * @author man
 */

#ifndef INTERNAL_IFXOPT_ENTRY_H
#define INTERNAL_IFXOPT_ENTRY_H

#include <functional>

#include <ifxOptEntryBase.h>

namespace ifx
{

// Alias for the function type
template <typename T>
using ValidatorFn = std::function<bool(T)>;

// Internal class for unified option handling
template <typename T>
class OptEntry : public OptEntryBase
{
    typedef std::function<bool(T)> Validator;

protected:
    T                 &mTarget;
    Validator          mValidatorFn;
    //Validator<T>      *mValidator;

public:
    OptEntry(const std::string  optLong,
             const char         optShort,
             const std::string  valName,
             const std::string  helpString,
             T                 &target,
             OptionSet          options     = IFX_OPTION_SET_CLEAR,
             Validator        &&validatorFn = nullptr);

    virtual ~OptEntry();

    virtual int parseValue(const std::string &valStr);

    // The following function needs to be defined in each type-specific implementation
    int parseValueTypeImpl(const std::string &valStr, T &value);
};

} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_ENTRY_H */
