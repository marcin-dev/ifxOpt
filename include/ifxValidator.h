/**
 * ifxValidator.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFXVALIDATOR_H
#define INCLUDE_IFXVALIDATOR_H

#include <string>

namespace ifx
{

template <typename T> class Validator
{
public:
    Validator() {}
    virtual ~Validator() {}
    virtual bool operator() (T argVal) = 0;
};

template <typename T> class DefaultValidator : public Validator<T>
{
public:
    DefaultValidator() {}
    virtual ~DefaultValidator() {}
    virtual bool operator() (T argVal) { return true; }
};

} /* namespace ifx */

#endif /* INCLUDE_IFXVALIDATOR_H */
