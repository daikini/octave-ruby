#include "or-variable.h"
#include "or-string.h"
#include "or-matrix.h"
#include "or-boolean_matrix.h"
#include "or-struct_matrix.h"
#include "or-cell_matrix.h"
#include "or-array.h"
#include "or-hash.h"

OR_Variable::~OR_Variable() {}

VALUE OR_Variable::to_ruby()
{
  if (octave_val.is_string()) {
    return OR_String(octave_val).to_ruby();
  } else if (octave_val.is_bool_matrix()) {
    return OR_BooleanMatrix(octave_val).to_ruby();
  } else if (octave_val.is_bool_type()) {
    return (octave_val.bool_value() ? Qtrue : Qfalse);
  } else if (octave_val.is_cell()) {
    return OR_CellMatrix(octave_val).to_ruby();
  } else if (octave_val.is_real_matrix()) {
    return OR_Matrix(octave_val).to_ruby();
  } else if (octave_val.is_map()) {
    return OR_StructMatrix(octave_val).to_ruby();
  } else if (octave_val.is_numeric_type() && !xisnan(octave_val.double_value())) {
    return rb_float_new(octave_val.double_value());
  } else {
    return Qnil;
  }
}

octave_value OR_Variable::to_octave()
{
  if (ruby_val == Qtrue) {
    return true;
  } else if (ruby_val == Qfalse) {
    return false;
  } else if (ruby_val == Qnil) {
    return octave_NaN;
  } else if (rb_type(ruby_val) == T_FLOAT) {
    return RFLOAT_VALUE(ruby_val);
  } else if (rb_type(ruby_val) == T_FIXNUM) {
    return FIX2LONG(ruby_val);
  } else if (rb_obj_is_kind_of(ruby_val, rb_path2class("Array")) == Qtrue) {
    return OR_Array(ruby_val).to_octave();
  } else if (rb_obj_is_kind_of(ruby_val, rb_path2class("Hash")) == Qtrue) {
    return OR_Hash(ruby_val).to_octave();
  } else if (rb_obj_is_kind_of(ruby_val, rb_path2class("Octave::StructMatrix")) == Qtrue) {
    return OR_StructMatrix(ruby_val).to_octave();
  } else if (rb_obj_is_kind_of(ruby_val, rb_path2class("Octave::CellMatrix")) == Qtrue) {
    return OR_CellMatrix(ruby_val).to_octave();
  } else if (rb_obj_is_kind_of(ruby_val, rb_path2class("Octave::Matrix")) == Qtrue) {
    return OR_Matrix(ruby_val).to_octave();
  } else {
    return OR_String(ruby_val).to_octave();
  }
}
