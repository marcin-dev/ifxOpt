/**
 * internal_ifxOpt.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INTERNAL_IFXOPT_IMPL_H
#define INTERNAL_IFXOPT_IMPL_H

#include <utility>

#include <ifxOpt.h>
#include "ifxDbg.h"

namespace ifx
{

template <typename T>
int Opt::addOptEntry(const std::string  optLong,
                     const char         optShort,
                     const std::string  valName,
                     const std::string  helpString,
                     T                 &target,
                     OptionSet          options,
                     std::function<bool(T)> validatorFn)
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
        OptEntryBase *opt = new OptEntry<T>(optLong, optShort, valName, helpString, target, options, std::move(validatorFn));
        if (opt != nullptr)
        {
            this->mEntries.push_back(opt);
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
					 const std::string  helpString,
					 T                 &target,
					 std::vector<T>     choices,
					 OptionSet          options)
{
    int ret = IFX_OPT_RESULT_SUCCESS;

    if (   optShort == '\0'
        && optLong.empty() == true)
    {
        IFX_LOG_ERR("Cannot add empty option");
        ret = IFX_OPT_ERROR_INVALID_ARGUMENTS;
    }
    else if (choices.empty() == true)
    {
        IFX_LOG_ERR("Cannot use empty set of choices");
        ret = IFX_OPT_ERROR_INVALID_ARGUMENTS;
    }
    else
    {
        OptEntryBase *opt = new OptEntry<T>(optLong, optShort, valName, helpString, target, std::move(choices), options);
        if (opt != nullptr)
        {
            this->mEntries.push_back(opt);
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
                	 const std::string  helpString,
                	 T                 &target,
                	 const T           *choices,
                	 size_t             choicesSize,
                	 OptionSet          options)
{
	int ret;

	if (choices == nullptr || choicesSize == 0u)
	{
		ret = IFX_OPT_ERROR_INVALID_ARGUMENTS;
	}
	else
	{
		ret = addOptEntry(optLong, optShort, valName, helpString, target, std::vector<T>(choices, choices+choicesSize), options);
	}

	return ret;
}

#define IFX_OPT_INSTANTIATE_TYPE_ADD_ENTRY(type)                                    \
    template int Opt::addOptEntry<type>(const std::string   optLong,                \
                                         const char         optShort,               \
                                         const std::string  valName,                \
                                         const std::string  helpString,             \
                                         type              &target,                 \
                                         OptionSet          options = IFX_OPTION_SET_CLEAR, \
                                         std::function<bool(type)> validatorFn = nullptr);  \
	template int Opt::addOptEntry<type>(const std::string   optLong,                \
									  	const char          optShort,               \
									  	const std::string   valName,                \
									  	const std::string   helpString,             \
									  	type               &target,                 \
										std::vector<type>   choices,				\
										OptionSet           options = IFX_OPTION_SET_CLEAR)
} /* namespace ifx */

#endif /* INTERNAL_IFXOPT_IMPL_H */
