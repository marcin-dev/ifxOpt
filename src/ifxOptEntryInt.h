/**
 * ifxOptEntryInt.h
 *
 * @date   2019.05
 * @author man
 */

#ifndef INCLUDE_IFXOPT_ENTRY_INT_H
#define INCLUDE_IFXOPT_ENTRY_INT_H

#include "ifxOptEntry.h"

namespace ifx
{

class OptEntryInt : public OptEntry<int>
{
public:
    OptEntryInt(const std::string  optLong,
                const char optShort,
                int &target,
                Validator<int> *validator = nullptr);
    virtual ~OptEntryInt();

    virtual int parseValue(const std::string &valStr, int &value);
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_ENTRY_INT_H */
