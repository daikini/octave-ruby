#include "or-array.h"
#include "or-variable.h"

OR_Array::~OR_Array() {}

octave_value OR_Array::to_octave()
{
  int row_index;
  VALUE values = rb_funcall(ruby_val, rb_intern("flatten"), 0);
  int number_of_rows = RARRAY(values)->len;
  VALUE cell;
  
  if (should_convert_to_cell_matrix()) {
    Cell matrix = Cell(number_of_rows, 1);
    
    for (row_index = 0; row_index < number_of_rows; row_index++) {
      cell = RARRAY(values)->ptr[row_index];
      matrix(row_index, 0) = OR_Variable(cell).to_octave();
    }
    
    return matrix;
  } else {
    Matrix matrix = Matrix(number_of_rows, 1);
    
    for (row_index = 0; row_index < number_of_rows; row_index++) {
      cell = RARRAY(values)->ptr[row_index];

      if (rb_type(cell) == T_FLOAT) {
        matrix(row_index, 0) = RFLOAT(cell)->value;
      } else if (rb_type(cell) == T_FIXNUM) {
        matrix(row_index, 0) = FIX2LONG(cell);
      } else {
        matrix(row_index, 0) = octave_NaN;
      }
    }
    
    return matrix;
  }
}

bool OR_Array::should_convert_to_cell_matrix()
{
  int row_index;
  VALUE values = rb_funcall(ruby_val, rb_intern("flatten"), 0);
  VALUE value;
  VALUE type;
  int number_of_rows = RARRAY(values)->len;

  for (row_index = 0; row_index < number_of_rows; row_index++) {
    value = RARRAY(values)->ptr[row_index];
    type = rb_type(value);
    if (type != T_FLOAT && type != T_FIXNUM && value != Qnil) {
      return true;
    }
  }

  return false;
}
