/**
 * ifxValidator.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFXVALIDATOR_H
#define INCLUDE_IFXVALIDATOR_H

#include <functional>
#include <string>

namespace ifx
{

template <typename T> class Validator
{
private:
    std::function<bool(T)> func;
public:
    Validator()                : func(nullptr) {}
    Validator(bool (*func)(T)) : func(func)    {}
//    Validator(std::function<bool(T)> f1) : func(f1) {}
    virtual ~Validator() {}
    virtual bool operator() (T& argVal) { return func(argVal); }
};

template <typename T> class DefaultValidator : public Validator<T>
{
public:
    DefaultValidator() {}
    virtual ~DefaultValidator() {}
    virtual bool operator() (T& argVal) { return true; }
};

template <typename T, bool (*func)(T)>
class Custom2Validator : public Validator<T>
{
public:
    Custom2Validator() {}
    virtual ~Custom2Validator() {}
    virtual bool operator() (T& argVal) { return func(argVal); }

//    static Validator<T> get(bool (*funcArg)(T))
//    {
//        Custom2Validator<T, funcArg> obj;
//        return obj;
//    }
};

#define IFX_CUSTOM_VALIDATOR(type, fn)

//template <typename T> class CustomValidator : public Validator<T>
//{
//private:
//
//public:
//    CustomValidator(bool (*func)(T argVal)) {}
//    virtual ~CustomValidator() {}
//    virtual bool operator() (T argVal) { return true; }
//};


} /* namespace ifx */

#endif /* INCLUDE_IFXVALIDATOR_H */
