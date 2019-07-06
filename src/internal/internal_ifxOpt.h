/**
 * internal_ifxOpt.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INTERNAL_IFXOPT_H
#define INTERNAL_IFXOPT_H

#include <ifxOpt.h>
#include "ifxCustomValidator.h"
#include "ifxDbg.h"

namespace ifx
{

template <typename T>
void Opt::addOptEntry(const std::string  optLong,
                      const char         optShort,
                      const std::string  valName,
                      std::string        helpString,
                      T                 &target,
                      OptionSet          options,
                      Validator<T>      *validatorFn)
{
    if (   optShort == '\0'
        && optLong.empty() == true)
    {
        // TODO: cannot add empty option, some error mechanism
        exit(IFX_OPT_ERROR_INVALID_ARGUMENTS);
    }
    else
    {
        OptEntryBase *opt = new OptEntry<T>(optLong, optShort, valName, helpString, target, options, validatorFn);
        if (opt != nullptr)
        {
            this->entries.push_back(opt);
        }
        // else TODO: some error mechanism
    }
}

template <typename T>
void Opt::addOptEntry(const std::string  optLong,
                      const char         optShort,
                      const std::string  valName,
                      std::string        helpString,
                      T                 &target,
                      OptionSet          options,
                      std::function<bool(T)> validatorFn)
{
    this->addOptEntry<T>(optLong, optShort, valName, helpString, target, options, CustomValidator<T>(validatorFn));
}


#define IFX_OPT_ADD_INSTANTIATE_TYPE(type)                                          \
    template void Opt::addOptEntry<type>(const std::string  optLong,                \
                                         const char         optShort,               \
                                         const std::string  valName,                \
                                         std::string        helpString,             \
                                         type              &target,                 \
                                         OptionSet          options     = IFX_OPTION_SET_CLEAR, \
                                         Validator<type>   *validatorFn = nullptr); \
    template void Opt::addOptEntry<type>(const std::string  optLong,                \
                                         const char         optShort,               \
                                         const std::string  valName,                \
                                         std::string        helpString,             \
                                         type              &target,                 \
                                         OptionSet          options,                \
                                         std::function<bool(type)> validatorFn)

} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_H */
