#include "octave-ruby.h"
#include "octave-includes.h"
#include "or-variable.h"

void initialize_octave()
{
  char *argv[2];
  argv[0] = "octave-ruby";
  argv[1] = "-q";
  octave_main(2,argv,1);
  bind_internal_variable("crash_dumps_octave_core", false);
}

extern void recover_from_exception(void)
{
  unwind_protect::run_all();
  can_interrupt = true;
  octave_interrupt_immediately = 0;
  octave_interrupt_state = 0;
  octave_allocation_error = 0;
}

VALUE or_feval(VALUE function_name, VALUE arguments)
{
  VALUE ruby_val = Qnil;
  int i, n;
  octave_value_list argList;
  
  n = RARRAY(arguments)->len;
  
  for (i = 0; i < n; i++) {
    argList(i) = OR_Variable(RARRAY(arguments)->ptr[i]).to_octave();
  }
  
  if (octave_set_current_context) {
    unwind_protect::run_all();
    raw_mode(0);
  }

  can_interrupt = true;
  octave_initialized = true;

  try {
    curr_sym_tab = top_level_sym_tab;
    reset_error_handler();
    
    octave_value_list val = feval(std::string(RSTRING(function_name)->ptr), argList, 1);
    if(val.length() > 0 && val(0).is_defined()) {
      ruby_val = OR_Variable(val(0)).to_ruby();
    }
  } catch (octave_interrupt_exception) {
    recover_from_exception();
    error_state = -2; 
  } catch (std::bad_alloc) {
    recover_from_exception();
    error_state = -3;
  }

  octave_initialized = false;

  return(ruby_val);
}
