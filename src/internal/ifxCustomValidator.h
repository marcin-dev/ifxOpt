/**
 * ifxCustomValidator.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFX_CUSTOM_VALIDATOR_H
#define INCLUDE_IFX_CUSTOM_VALIDATOR_H

#include <string>
#include <functional>

#include <ifxValidator.h>

namespace ifx
{

// ****************************************************************************
// Custom Validator Generic Template
// ****************************************************************************

template <typename T>
class InternalCustomValidator : public Validator<T>
{
private:
    std::function<bool(T)> func;
public:
    InternalCustomValidator(std::function<bool(T)> func) : func(func) {}
    virtual ~InternalCustomValidator() {}
    virtual bool operator() (T& argVal) { return func(argVal); }
};

template <typename T>
Validator<T> *CustomValidator(std::function<bool(T)> func)
{
    return new InternalCustomValidator<T>(func);
}

} /* namespace ifx */

#endif /* INCLUDE_IFX_CUSTOM_VALIDATOR_H */
