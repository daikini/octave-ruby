#include "or-matrix.h"

OR_Matrix::~OR_Matrix() {}

VALUE OR_Matrix::to_ruby()
{
  Matrix matrix;
  MArray<double> values;
  double cell;
  int i, number_of_values;
  VALUE argv[2];
  
  matrix = octave_val.matrix_value();
  int number_of_rows = matrix.rows();
  int number_of_columns = matrix.columns();
  
  if ((number_of_rows == 0) && (number_of_columns == 0)) {
    return rb_ary_new2(0);
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
  for (i = 0; i < number_of_values; i++) {
    cell = values(i);
    if (xisnan(cell) || octave_is_NA(cell)) {
      rb_ary_push(ruby_val, Qnil);
    } else {
      rb_ary_push(ruby_val, rb_float_new(cell));
    }
  }
  
  return ruby_val;
}

octave_value OR_Matrix::to_octave()
{
  int row_index, column_index;
  int number_of_rows = FIX2INT(rb_iv_get(ruby_val, "@m"));
  int number_of_columns = FIX2INT(rb_iv_get(ruby_val, "@n"));
  VALUE cells = rb_iv_get(ruby_val, "@cells");
  VALUE row, cell;
  Matrix matrix = Matrix(number_of_rows, number_of_columns);
  
  for (row_index = 0; row_index < number_of_rows; row_index++) {
    row = RARRAY_PTR(cells)[row_index];
    
    for (column_index = 0; column_index < number_of_columns; column_index++) {
      cell = RARRAY_PTR(row)[column_index];
      
      if (rb_type(cell) == T_FLOAT) {
        matrix(row_index, column_index) = RFLOAT_VALUE(cell);
      } else if (rb_type(cell) == T_FIXNUM) {
        matrix(row_index, column_index) = FIX2LONG(cell);
      } else {
        matrix(row_index, column_index) = octave_NaN;
      }
    }
  }
  
  return matrix;
}
