#include "ruby.h"

#ifdef __cplusplus
extern "C" {
#endif

// Prototype for the initialization method - Ruby calls this, not you
void Init_octave_api();
static VALUE feval(VALUE self, VALUE function_name, VALUE arguments);
static VALUE get_variable(VALUE self, VALUE variable_name);
static VALUE put_variable(VALUE self, VALUE variable_name, VALUE value);
#ifdef __cplusplus
}
#endif
