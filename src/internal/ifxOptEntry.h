/**
 * ifxOptEntry.h
 *
 * @date   2019.07
 * @author man
 */

#ifndef INTERNAL_IFXOPT_ENTRY_H
#define INTERNAL_IFXOPT_ENTRY_H

#include <functional>
#include <vector>

#include <ifxOptEntryBase.h>

namespace ifx
{

// Internal class for unified option handling
template <typename T>
class OptEntry : public OptEntryBase
{
    typedef std::function<bool(T)> Validator;

private:
    T                    &mTarget;
    Validator             mValidatorFn;
    std::vector<T>        mChoices;

    static std::string genValNameFromChoices(std::vector<T> &choices);

public:
    OptEntry(const std::string  optLong,
             const char         optShort,
             const std::string  valName,
             const std::string  helpString,
             T                 &target,
             OptionSet          options     = IFX_OPTION_SET_CLEAR,
             Validator        &&validatorFn = nullptr);

    OptEntry(const std::string  optLong,
             const char         optShort,
             const std::string  valName,
             const std::string  helpString,
             T                 &target,
             std::vector<T>   &&choices,
             OptionSet          options = IFX_OPTION_SET_CLEAR);

    virtual ~OptEntry();

    virtual int parseValue(const std::string &valStr);

    // The following function needs to be defined in each type-specific implementation
    int parseValueTypeImpl(const std::string &valStr, T &value);
};

} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_ENTRY_H */
