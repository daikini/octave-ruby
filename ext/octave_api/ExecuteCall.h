#ifndef EXECUTECALL_H_INCLUDED_
#define EXECUTECALL_H_INCLUDED_

#include "ruby.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Entry point */
extern VALUE ExecuteCall(VALUE function_name, VALUE arguments);

extern void InitializeOctave();
extern void TerminateOctave();

#ifdef __cplusplus /* extern "C" */
}
#endif

#endif /*EXECUTECALL_H_INCLUDED_ */
