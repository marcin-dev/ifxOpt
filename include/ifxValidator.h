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

} /* namespace ifx */

#endif /* INCLUDE_IFXVALIDATOR_H */
