/**
 * ifxValidator.cpp
 *
 * @date   2019.06
 * @author man
 */

#include "ifxValidator.h"

#include <iostream>

namespace ifx
{

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
Validator<T> *CustomValidator(bool (*func)(T))
{
    return new InternalCustomValidator<T>(func);
}

// ****************************************************************************
// Option type: int
// ****************************************************************************

template <>
Validator<int> *CustomValidator<int>(bool (*func)(int))
{
    return new InternalCustomValidator<int>(func);
}

// Add definition to avoid linker errors
template <>
Validator<int> *CustomValidator<int>(bool (*func)(int));

} /* namespace ifx */
