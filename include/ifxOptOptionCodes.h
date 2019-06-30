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
#define  IFX_OPT_ENTRY_HAS_VAL_ARG              IFX_OPTION_VAL(1u)
#define  IFX_OPT_ENTRY_VAL_ARG_MANDATORY        IFX_OPTION_VAL(2u)
#define  IFX_OPT_ENTRY_ONE_FROM_GROUP_1         IFX_OPTION_VAL(3u)
#define  IFX_OPT_ENTRY_ONE_FROM_GROUP_2         IFX_OPTION_VAL(4u)
#define  IFX_OPT_ENTRY_ONE_FROM_GROUP_3         IFX_OPTION_VAL(5u)
#define  IFX_OPT_ENTRY_ONE_FROM_GROUP_4         IFX_OPTION_VAL(6u)
#define  IFX_OPT_ENTRY_ONE_FROM_GROUP_5         IFX_OPTION_VAL(7u)

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_OPTION_CODES_H */
