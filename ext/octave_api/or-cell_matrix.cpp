#include "or-cell_matrix.h"
#include "or-variable.h"

OR_CellMatrix::~OR_CellMatrix() {}

VALUE OR_CellMatrix::to_ruby()
{
  int i, number_of_values;
  int number_of_rows = octave_val.rows();
  int number_of_columns = octave_val.columns();
  Cell cell = octave_val.cell_value();
  
  if (number_of_rows == 1 && number_of_columns == 1) {
    return OR_Variable(cell(0)).to_ruby();
  } else if (number_of_rows == 1) {
    number_of_values = number_of_columns;
  } else if (number_of_columns == 1) {
    number_of_values = number_of_rows;
  } else {
    VALUE argv[2];
    argv[0] = INT2FIX(number_of_rows);
    argv[1] = INT2FIX(number_of_columns);
    ruby_val = rb_class_new_instance(2, argv, rb_path2class("Octave::CellMatrix"));
    
    int row_index, column_index = 0;
    VALUE cells, row;
    cells = rb_ary_new2(number_of_rows);
    for (row_index = 0; row_index < number_of_rows; row_index++) {
      row = rb_ary_new2(number_of_columns);

      for (column_index = 0; column_index < number_of_columns; column_index++) {
        rb_ary_push(row, OR_Variable(cell(row_index, column_index)).to_ruby());
      }
      
      rb_ary_push(cells, row);
    }
    
    rb_iv_set(ruby_val, "@cells", cells);
    return ruby_val;
  }
  
  ruby_val = rb_ary_new2(number_of_values);
  for (i = 0; i < number_of_values; i++) {
    rb_ary_push(ruby_val, OR_Variable(cell(i)).to_ruby());
  }
  return ruby_val;
}

octave_value OR_CellMatrix::to_octave()
{
  int i, row_index, column_index;
  int number_of_rows = FIX2INT(rb_iv_get(ruby_val, "@m"));
  int number_of_columns = FIX2INT(rb_iv_get(ruby_val, "@n"));
  VALUE cells = rb_iv_get(ruby_val, "@cells");
  VALUE row, cell;
  Cell matrix = Cell(number_of_rows, number_of_columns);
  
  for (row_index = 0; row_index < number_of_rows; row_index++) {
    row = RARRAY(cells)->ptr[row_index];
    
    for (column_index = 0; column_index < number_of_columns; column_index++) {
      cell = RARRAY(row)->ptr[column_index];
      matrix(row_index, column_index) = OR_Variable(cell).to_octave();
    }
  }
  
  return matrix;
}
