#include "octave_api.h"
#include "ruby.h"
#include "octave-ruby.h"

// Defining a space for information and references about the module to be stored internally
VALUE OCTAVE_API = Qnil;

// The initialization method for this module
void Init_octave_api() {
  OCTAVE_API = rb_define_module("Octave");
  OCTAVE_API = rb_define_module_under(OCTAVE_API, "Driver");
  OCTAVE_API = rb_define_module_under(OCTAVE_API, "Native");
  OCTAVE_API = rb_define_module_under(OCTAVE_API, "API");
  rb_define_module_function(OCTAVE_API, "feval", feval, 2);
  
  initialize_octave();
}

VALUE feval(VALUE self, VALUE function_name, VALUE arguments)
{
  return or_feval(function_name, arguments);
}
