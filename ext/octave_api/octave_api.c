// Include the Ruby headers and goodies
#include "ruby.h"
#include "ExecuteCall.h"
#include "octave_api.h"

// Defining a space for information and references about the module to be stored internally
VALUE OCTAVE_API = Qnil;

// The initialization method for this module
void Init_octave_api() {
  OCTAVE_API = rb_define_module("Octave");
  OCTAVE_API = rb_define_module_under(OCTAVE_API, "Driver");
  OCTAVE_API = rb_define_module_under(OCTAVE_API, "Native");
  OCTAVE_API = rb_define_module_under(OCTAVE_API, "API");
  rb_define_module_function(OCTAVE_API, "Call", Call, 2);
  
  InitializeOctave();
}

VALUE Call(VALUE self, VALUE function_name, VALUE arguments)
{
  return ExecuteCall(function_name, arguments);
}
