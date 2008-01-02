#ifndef EXECUTECALL_H_INCLUDED_
#define EXECUTECALL_H_INCLUDED_

#include "ruby.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern VALUE or_feval(VALUE function_name, VALUE arguments);
extern void initialize_octave();

#ifdef __cplusplus /* extern "C" */
}
#endif

#endif /*EXECUTECALL_H_INCLUDED_ */
