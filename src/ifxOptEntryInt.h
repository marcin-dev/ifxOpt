/**
 * ifxOptEntryInt.h
 *
 * @date   2019.05
 * @author man
 */

#ifndef INCLUDE_IFXOPT_ENTRY_INT_H
#define INCLUDE_IFXOPT_ENTRY_INT_H

#include "ifxOptEntry.h"
#include "ifxValidator.h"

namespace ifx
{

class OptEntryInt : public OptEntry
{
private:
    int               &target;
    Validator<int>    &validator;
    static DefaultValidator<int>  defaultValidator;  // static, it may be shared between all objects

public:
    OptEntryInt(const std::string  optLong,
                const char optShort,
                int &target,
                Validator<int> &validator = defaultValidator);
    virtual ~OptEntryInt();

    virtual int parseOpt(const std::string &valStr);
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_ENTRY_INT_H */
