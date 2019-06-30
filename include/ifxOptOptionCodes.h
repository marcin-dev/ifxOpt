/**
 * ifxOptOptionCodes.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFXOPT_OPTION_CODES_H
#define INCLUDE_IFXOPT_OPTION_CODES_H

#include <cstdint>

namespace ifx
{

typedef uint32_t OptionSet;

#define  IFX_OPTION_SET_CLEAR                   (0u)

#define  IFX_OPTION_VAL(x)                      (1u << (x))

#define  IFX_OPTION_CHECK(optSet, option)       (((optSet) & (option)) != 0u)

#define  IFX_OPT_ALLOW_ARG_ASSIGN_CHAR          IFX_OPTION_VAL(0u)

#define  IFX_OPT_ENTRY_MANDATORY                IFX_OPTION_VAL(0u)
#define  IFX_OPT_ENTRY_MANDATORY_EX_GROUP       IFX_OPTION_VAL(1u) // TODO: implement
#define  IFX_OPT_ENTRY_OPTIONAL_EX_GROUP        IFX_OPTION_VAL(2u) // TODO: implement
#define  IFX_OPT_ENTRY_MANDATORY_AT_LEAST_ONE   IFX_OPTION_VAL(3u) // TODO: implement

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_OPTION_CODES_H */
