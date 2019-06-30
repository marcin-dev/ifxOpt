/**
 * ifxOptEntry.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFXOPT_ENTRY_H
#define INCLUDE_IFXOPT_ENTRY_H

#include <string>

#include "ifxValidator.h"
#include "ifxOptOptionCodes.h"

namespace ifx
{

class OptEntryBase
{
private:
    const std::string  mHelpString;
    const std::string  mValName;
    const std::string  mOptLong;
    const char         mOptShort;
    bool               mMandatory;
    bool               mHasValArg;
    bool               mValMandatory;

public:
    OptEntryBase(const std::string  optLong,
                 const char         optShort,
                 const std::string  valName,
                 std::string        helpString,
                 OptionSet          options);

    virtual ~OptEntryBase();

    const std::string &getHelpString()  const;
    const std::string &getValName()     const;
    const std::string &getOptLong()     const;
    const char        &getOptShort()    const;
    const bool        &isMandatory()    const;
    const bool        &hasValArg()      const;
    const bool        &isValMandatory() const;

    int parseOpt(const std::string &argStr, const char argShort, const std::string &valStr);

    virtual int parseOpt(const std::string &valStr) = 0;
};

template <typename T>
class OptEntry : public OptEntryBase
{
protected:
    T                 &mTarget;
    Validator<T>      *mValidator;

public:
    OptEntry(const std::string  optLong,
             const char         optShort,
             const std::string  valName,
             std::string        helpString,
             T                 &target,
             OptionSet          options,
             Validator<T>      *validator = nullptr);

    virtual ~OptEntry();

    virtual int parseOpt(const std::string &valStr);

    // The following function needs to be defined in each type-specific implementation
    int parseValue(const std::string &valStr, T &value);
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_ENTRY_H */
