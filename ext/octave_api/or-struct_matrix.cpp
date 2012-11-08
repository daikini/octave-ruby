#include "or-struct_matrix.h"
#include "or-variable.h"

OR_StructMatrix::~OR_StructMatrix() {}

VALUE OR_StructMatrix::to_ruby()
{
  Octave_map struct_matrix = Octave_map(octave_val.map_value());
  string_vector keys = struct_matrix.keys();
  int number_of_keys = keys.length();
  int number_of_rows = struct_matrix.rows();
  int number_of_columns = struct_matrix.columns();
  int i;
  VALUE cells, row, cell;

  if (number_of_rows == 0 && number_of_columns == 1) {
    ruby_val = rb_hash_new();
    for (i = 0; i < number_of_keys; i++) {
      rb_hash_aset(ruby_val, rb_str_new2(keys[i].c_str()), OR_Variable(struct_matrix.contents(keys[i])).to_ruby());
    }
  } else if (number_of_rows == 1 && number_of_columns == 1) {
    ruby_val = rb_hash_new();
    for (i = 0; i < number_of_keys; i++) {
      rb_hash_aset(ruby_val, rb_str_new2(keys[i].c_str()), OR_Variable(struct_matrix.contents(keys[i])(0)).to_ruby());
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
    for (row_index = 0; row_index < number_of_rows; row_index++) {
      row = rb_ary_new2(number_of_columns);
    
      for (column_index = 0; column_index < number_of_columns; column_index++) {
        cell = rb_hash_new();
        for (i = 0; i < number_of_keys; i++) {
          rb_hash_aset(cell, rb_str_new2(keys[i].c_str()), OR_Variable(struct_matrix.contents(keys[i])(row_index, column_index)).to_ruby());
        }
        rb_ary_push(row, cell);
      }
    
      rb_ary_push(cells, row);
    }
  
    rb_iv_set(ruby_val, "@cells", cells);
  }
  
  return ruby_val;
}

octave_value OR_StructMatrix::to_octave()
{
  int i, row_index, column_index;
  VALUE row, cell;
  VALUE cells = rb_iv_get(ruby_val, "@cells");
  VALUE names = rb_iv_get(ruby_val, "@names");
  int number_of_keys = RARRAY_LEN(names);
  int number_of_rows = FIX2INT(rb_iv_get(ruby_val, "@m"));
  int number_of_columns = FIX2INT(rb_iv_get(ruby_val, "@n"));

  string_vector keys = string_vector();
  for (i = 0; i < number_of_keys; i++) {
    keys.append(std::string(RSTRING_PTR(RARRAY_PTR(names)[i])));
  }
  
  Octave_map struct_matrix = Octave_map(dim_vector(number_of_rows, number_of_columns), Cell(keys));
  for (row_index = 0; row_index < number_of_rows; row_index++) {
    row = RARRAY_PTR(cells)[row_index];
  
    for (column_index = 0; column_index < number_of_columns; column_index++) {
      cell = RARRAY_PTR(row)[column_index];
      
      for (i = 0; i < number_of_keys; i++) {
        struct_matrix.contents(std::string(RSTRING_PTR(RARRAY_PTR(names)[i])))(row_index, column_index) = OR_Variable(rb_hash_aref(cell, rb_str_new2(RSTRING_PTR(RARRAY_PTR(names)[i])))).to_octave();
      }
    }
  }
  
  return struct_matrix;
}
