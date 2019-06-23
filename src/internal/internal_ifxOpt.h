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
                      const char         optShort,
                      const std::string  valName,
                      std::string        helpString,
                      T                 &target,
                      bool               mandatory,
                      bool               valMandatory,
                      Validator<T>      *validatorFn)
{
    OptEntryBase *opt = new OptEntry<T>(optLong, optShort, valName, helpString, target, mandatory, valMandatory, validatorFn);
    if (opt != nullptr)
    {
        this->entries.push_back(opt);
    }
    // else TODO: some error mechanism
}

template <typename T>
void Opt::addOptEntry(const std::string  optLong,
                      const char         optShort,
                      const std::string  valName,
                      std::string        helpString,
                      T                 &target,
                      bool               mandatory,
                      bool               valMandatory,
                      std::function<bool(T)> validatorFn)
{
    this->addOptEntry<T>(optLong, optShort, valName, helpString, target, mandatory, valMandatory, CustomValidator<T>(validatorFn));
}


#define IFX_OPT_ADD_INSTANTIATE_TYPE(type)                                          \
    template void Opt::addOptEntry<type>(const std::string  optLong,                \
                                         const char         optShort,               \
                                         const std::string  valName,                \
                                         std::string        helpString,             \
                                         type              &target,                 \
                                         bool               mandatory = false,      \
                                         bool               valMandatory = false,   \
                                         Validator<type>   *validatorFn = nullptr); \
    template void Opt::addOptEntry<type>(const std::string  optLong,                \
                                         const char         optShort,               \
                                         const std::string  valName,                \
                                         std::string        helpString,             \
                                         type              &target,                 \
                                         bool               mandatory,              \
                                         bool               valMandatory,           \
                                         std::function<bool(type)> validatorFn)

} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_H */
