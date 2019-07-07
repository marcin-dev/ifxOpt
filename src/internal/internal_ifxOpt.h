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
int Opt::addOptEntry(const std::string  optLong,
                     const char         optShort,
                     const std::string  valName,
                     std::string        helpString,
                     T                 &target,
                     OptionSet          options,
                     Validator<T>      *validatorFn)
{
    int ret = IFX_OPT_RESULT_SUCCESS;

    if (   optShort == '\0'
        && optLong.empty() == true)
    {
        IFX_LOG_ERR("Cannot add empty option");
        ret = IFX_OPT_ERROR_INVALID_ARGUMENTS;
    }
    else
    {
        OptEntryBase *opt = new OptEntry<T>(optLong, optShort, valName, helpString, target, options, validatorFn);
        if (opt != nullptr)
        {
            this->mEntries.push_back(std::shared_ptr<OptEntryBase>(opt));
        }
        else
        {
            ret = IFX_OPT_ERROR_OUT_OF_MEMORY;
        }
    }

    return ret;
}

template <typename T>
int Opt::addOptEntry(const std::string  optLong,
                     const char         optShort,
                     const std::string  valName,
                     std::string        helpString,
                     T                 &target,
                     OptionSet          options,
                     std::function<bool(T)> validatorFn)
{
    return this->addOptEntry<T>(optLong, optShort, valName, helpString, target, options, CustomValidator<T>(validatorFn));
}


#define IFX_OPT_INSTANTIATE_TYPE_ADD_ENTRY(type)                                    \
    template int Opt::addOptEntry<type>(const std::string  optLong,                 \
                                         const char         optShort,               \
                                         const std::string  valName,                \
                                         std::string        helpString,             \
                                         type              &target,                 \
                                         OptionSet          options     = IFX_OPTION_SET_CLEAR, \
                                         Validator<type>   *validatorFn = nullptr); \
    template int Opt::addOptEntry<type>(const std::string  optLong,                 \
                                         const char         optShort,               \
                                         const std::string  valName,                \
                                         std::string        helpString,             \
                                         type              &target,                 \
                                         OptionSet          options,                \
                                         std::function<bool(type)> validatorFn)

} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_H */
