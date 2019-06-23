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

namespace ifx
{

class OptEntryBase
{
private:
    const std::string  helpString;
    const std::string  valName;
    const std::string  optLong;
    const char         optShort;
    bool               mandatory;
    bool               valMandatory;

public:
    OptEntryBase(const std::string  optLong,
                 const char         optShort,
                 const std::string  valName,
                 std::string        helpString,
                 bool               mandatory = false,
                 bool               valMandatory = false);

    virtual ~OptEntryBase();

    const std::string &getHelpString()  const;
    const std::string &getValName()     const;
    const std::string &getOptLong()     const;
    const char        &getOptShort()    const;
    const bool        &isMandatory()    const;
    const bool        &isValMandatory() const;

    int parseOpt(const std::string &argStr, const char argShort, const std::string &valStr);

    virtual int parseOpt(const std::string &valStr) = 0;
};

template <typename T>
class OptEntry : public OptEntryBase
{
protected:
    T                 &target;
    Validator<T>      *validator;

public:
    OptEntry(const std::string  optLong,
             const char         optShort,
             const std::string  valName,
             std::string        helpString,
             T                 &target,
             bool               mandatory = false,
             bool               valMandatory = false,
             Validator<T>      *validator = nullptr);

    virtual ~OptEntry();

    virtual int parseOpt(const std::string &valStr);

    // The following function needs to be defined in each type-specific implementation
    int parseValue(const std::string &valStr, T &value);
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_ENTRY_H */
