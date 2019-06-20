/**
 * internal_ifxOpt.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INTERNAL_IFXOPT_H
#define INTERNAL_IFXOPT_H

#include <vector>
#include <functional>

#include <ifxOpt.h>
#include "ifxCustomValidator.h"

namespace ifx
{

template <typename T>
void Opt::addOptEntry(const std::string  optLong,
                      const char optShort,
                      T &target)
{
    OptEntryBase *opt = new OptEntry<T>(optLong, optShort, target);
    if (opt != nullptr)
    {
        this->entries.push_back(opt);
    }
    // else TODO: some error mechanism
}

template <typename T>
void Opt::addOptEntry(const std::string  optLong,
                      const char optShort,
                      T &target,
                      Validator<T> *validatorFn)
{
    OptEntryBase *opt = new OptEntry<T>(optLong, optShort, target, validatorFn);
    if (opt != nullptr)
    {
        this->entries.push_back(opt);
    }
    // else TODO: some error mechanism
}

template <typename T>
void Opt::addOptEntry(const std::string  optLong,
                      const char optShort,
                      T &target,
                      std::function<bool(T)> validatorFn)
{
    this->addOptEntry<T>(optLong, optShort, target, CustomValidator<T>(validatorFn));
}


#define IFX_OPT_ADD_INSTANTIATE_TYPE(type)                                      \
    template void Opt::addOptEntry<type>(const std::string  optLong,            \
                                         const char optShort,                   \
                                         type &target);                         \
    template void Opt::addOptEntry<type>(const std::string  optLong,            \
                                         const char optShort,                   \
                                         type &target,                          \
                                         Validator<type> *validatorFn);         \
    template void Opt::addOptEntry<type>(const std::string  optLong,            \
                                         const char optShort,                   \
                                         type &target,                          \
                                         std::function<bool(type)> validatorFn)

} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_H */
