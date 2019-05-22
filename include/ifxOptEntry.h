/**
 * ifxOptEntry.h
 *
 * @date   2019.04
 * @author man
 */

#ifndef INCLUDE_IFXOPT_ENTRY_H
#define INCLUDE_IFXOPT_ENTRY_H

#include <string>

namespace ifx
{

class OptEntry
{
private:
    const std::string  optLong;
    const char         optShort;

public:
    OptEntry(const std::string  optLong,
             const char optShort);
    virtual ~OptEntry();
};

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_ENTRY_H */
