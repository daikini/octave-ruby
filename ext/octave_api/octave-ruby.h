#ifndef EXECUTECALL_H_INCLUDED_
#define EXECUTECALL_H_INCLUDED_

#include "ruby.h"

#ifdef __cplusplus
extern "C"
{
#endif
  
/* Macros for backwards compatibility with 1.8 */
#ifdef RUBY_18
  #define RARRAY_LEN(a) (RARRAY(a)->len)
  #define RARRAY_PTR(a) (RARRAY(a)->ptr)
  #define RFLOAT_VALUE(v) (RFLOAT(v)->value)
  #define RSTRING_PTR(s) (RSTRING(s)->ptr)
#endif

extern VALUE or_feval(VALUE function_name, VALUE arguments);
extern VALUE or_get_variable(VALUE variable_name);
extern VALUE or_put_variable(VALUE variable_name, VALUE value);
extern void initialize_octave();

#ifdef __cplusplus /* extern "C" */
}
#endif

#endif /*EXECUTECALL_H_INCLUDED_ */
