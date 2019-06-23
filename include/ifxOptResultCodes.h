/**
 * ifxOptResultCodes.h
 *
 * @date   2019.06
 * @author man
 */

#ifndef INCLUDE_IFXOPT_RESULT_CODES_H
#define INCLUDE_IFXOPT_RESULT_CODES_H

#include <vector>
#include <functional>

#include "ifxOptEntry.h"
#include "ifxValidator.h"

namespace ifx
{

#define  IFX_OPT_RESULT_SUCCESS                 (0)
#define  IFX_OPT_NOT_MACHING_OPTION             (1)
#define  IFX_OPT_NOT_FOUND                      (2)
#define  IFX_OPT_VALUE_NOT_FOUND                (3)

#define  IFX_OPT_ERROR_INVALID_ARGUMENTS        (-1)
#define  IFX_OPT_ERROR_VALUE_CANNOT_EXTRACT     (-2)
#define  IFX_OPT_ERROR_VALUE_OUT_OF_RANGE       (-3)
#define  IFX_OPT_ERROR_CUSTOM_VALIDATION_FAILED (-4)

} /* namespace ifx */

#endif /* INCLUDE_IFXOPT_RESULT_CODES_H */
