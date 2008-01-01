#include "octave/config.h"
#include "octave.h"
#include "symtab.h"
#include "parse.h"
#include "unwind-prot.h"
#include "toplev.h"
#include "error.h" 
#include "variables.h"
#include "sighandlers.h"
#include "sysdep.h"
#include "ov-struct.h"

#include "ExecuteCall.h"

void InitializeOctave()
{
  char *argv[2];
  argv[0] = "octave-ruby";
  argv[1] = "-q";
  octave_main(2,argv,1);
  bind_internal_variable("crash_dumps_octave_core", false);
}

void TerminateOctave()
{
  do_octave_atexit();
}

extern void recover_from_exception(void)
{
  unwind_protect::run_all();
  can_interrupt = true;
  octave_interrupt_immediately = 0;
  octave_interrupt_state = 0;
  octave_allocation_error = 0;
}

VALUE toRubyValue(octave_value val)
{
   VALUE ruby_val = Qnil;

   // std::cerr << "Type name: " << val.type_name() << std::endl;

   if (val.is_string()) {
     ruby_val = rb_str_new2(val.string_value().c_str());
   } else if (val.is_bool_type()) {
     ruby_val = (val.bool_value() ? Qtrue : Qfalse);
   } else if (val.is_real_matrix()) {
     Matrix matrix;
     MArray<double> values;
     double cell;
     int i, number_of_values;
     VALUE argv[2];
     
     matrix = val.matrix_value();
     int number_of_rows = matrix.rows();
     int number_of_columns = matrix.columns();
     
     if (number_of_rows == 1) {
       values = matrix.row(0);
     } else if (number_of_columns == 1) {
       values = matrix.column(0);
     } else {
       argv[0] = INT2FIX(number_of_rows);
       argv[1] = INT2FIX(number_of_columns);
       ruby_val = rb_class_new_instance(2, argv, rb_path2class("Octave::Matrix"));
       
       int row_index, column_index = 0;
       VALUE cells, row;
       cells = rb_ary_new2(number_of_rows);
       for (row_index = 0; row_index < number_of_rows; row_index++) {
         row = rb_ary_new2(number_of_columns);
         values = matrix.row(row_index);
         
         for (column_index = 0; column_index < number_of_columns; column_index++) {
           cell = values(column_index);
           if (xisnan(cell) || octave_is_NA(cell)) {
             rb_ary_push(row, Qnil);
           } else {
             rb_ary_push(row, rb_float_new(cell));
           }
         }
         
         rb_ary_push(cells, row);
       }
       
       rb_iv_set(ruby_val, "@cells", cells);
       return ruby_val;
     }
     
     number_of_values = values.length();
     ruby_val = rb_ary_new2(number_of_values);
     for(i = 0; i < number_of_values; i++) {
       cell = values(i);
       if (xisnan(cell) || octave_is_NA(cell)) {
         rb_ary_push(ruby_val, Qnil);
       } else {
         rb_ary_push(ruby_val, rb_float_new(cell));
       }
     }
     
   } else if (val.is_map()) {
     Octave_map struct_matrix = Octave_map(val.map_value());
     string_vector keys = struct_matrix.keys();
     int number_of_keys = keys.length();
     int number_of_rows = struct_matrix.rows();
     int number_of_columns = struct_matrix.columns();
     int i;
     VALUE cells, row, cell;

     if (number_of_rows == 1 && number_of_columns == 1) {
       ruby_val = rb_hash_new();
       for (i = 0; i < number_of_keys; i++) {
         rb_hash_aset(ruby_val, rb_str_new2(keys[i].c_str()), toRubyValue(struct_matrix.contents(keys[i])(0)));
       }
     } else {
       int number_of_arguments_to_struct_matrix = number_of_keys + 2;
       VALUE argv[number_of_arguments_to_struct_matrix];
       argv[0] = INT2FIX(number_of_rows);
       argv[1] = INT2FIX(number_of_columns);
     
       for (i = 0; i < number_of_keys; i++) {
         argv[2 + i] = rb_str_new2(keys[i].c_str());
       }
       ruby_val = rb_class_new_instance(number_of_arguments_to_struct_matrix, argv, rb_path2class("Octave::StructMatrix"));
       cells = rb_ary_new2(number_of_rows);
     
       int row_index, column_index;
       for(row_index = 0; row_index < number_of_rows; row_index++) {
         row = rb_ary_new2(number_of_columns);
       
         for(column_index = 0; column_index < number_of_columns; column_index++) {
           cell = rb_hash_new();
           for (i = 0; i < number_of_keys; i++) {
             rb_hash_aset(cell, rb_str_new2(keys[i].c_str()), toRubyValue(struct_matrix.contents(keys[i])(column_index, row_index)));
           }
           rb_ary_push(row, cell);
         }
       
         rb_ary_push(cells, row);
       }
     
       rb_iv_set(ruby_val, "@cells", cells);
     }
   } else if (val.is_numeric_type()) {
     ruby_val = rb_float_new(val.double_value());
   } else {
     ruby_val = Qnil;
   }
 
   return(ruby_val);
}

octave_value toOctaveValue(VALUE val)
{
  octave_value octave_val;
  
  if (val == Qfalse) {
    octave_val = false;
  } else if (val == Qtrue) {
    octave_val = true;
  } else if (val == Qnil) {
    octave_val = octave_NaN;
  } else if (rb_type(val) == T_FLOAT) {
    octave_val = RFLOAT(val)->value;
  } else if (rb_type(val) == T_FIXNUM) {
    octave_val = FIX2LONG(val);
  } else if (rb_obj_is_kind_of(val, rb_path2class("Octave::Matrix")) == Qtrue) {
    int row_index, column_index;
    int number_of_rows = FIX2INT(rb_iv_get(val, "@m"));
    int number_of_columns = FIX2INT(rb_iv_get(val, "@n"));
    VALUE cells = rb_iv_get(val, "@cells");
    VALUE row, cell;
    Matrix matrix = Matrix(number_of_rows, number_of_columns);
    
    for (row_index = 0; row_index < number_of_rows; row_index++) {
      row = RARRAY(cells)->ptr[row_index];
      
      for (column_index = 0; column_index < number_of_columns; column_index++) {
        cell = RARRAY(row)->ptr[column_index];
        if (rb_obj_is_kind_of(cell, rb_path2class("Numeric")) == Qtrue) {
          matrix(row_index, column_index) = RFLOAT(cell)->value;
        } else {
          matrix(row_index, column_index) = octave_NaN;
        }
      }
    }
    
    octave_val = matrix;
  } else {
    octave_val = std::string(RSTRING(val)->ptr);
  }
  
  return octave_val;
}

VALUE ExecuteCall(VALUE function_name, VALUE arguments)
{
  VALUE ruby_val = Qnil;
  int i, n;
  octave_value_list argList;
  
  n = RARRAY(arguments)->len;
  
  for(i = 0; i < n; i++) {
    argList(i) = toOctaveValue(RARRAY(arguments)->ptr[i]);
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
      ruby_val = toRubyValue(val(0));
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
