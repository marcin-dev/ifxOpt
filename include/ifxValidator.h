/**
 * ifxValidator.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFXVALIDATOR_H
#define INCLUDE_IFXVALIDATOR_H

#include <string>
#include <functional>

namespace ifx
{

template <typename T>
class Validator
{
protected:
    Validator() {}
public:
    virtual ~Validator() {}
    virtual bool operator() (T& argVal) = 0;
};

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

#endif /* INCLUDE_IFXVALIDATOR_H */
