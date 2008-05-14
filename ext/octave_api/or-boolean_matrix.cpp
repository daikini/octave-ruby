#include "or-boolean_matrix.h"

OR_BooleanMatrix::~OR_BooleanMatrix() {}

VALUE OR_BooleanMatrix::to_ruby()
{
  Matrix matrix;
  MArray<double> values;
  double cell;
  int i, number_of_values;
  VALUE argv[2];
  
  matrix = octave_val.matrix_value();
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
          rb_ary_push(row, (int(cell) == 1 ? Qtrue : Qfalse));
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
      rb_ary_push(ruby_val, (int(cell) == 1 ? Qtrue : Qfalse));
    }
  }
  
  return ruby_val;
}
