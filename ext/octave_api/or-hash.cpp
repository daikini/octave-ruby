#include "or-hash.h"
#include "or-variable.h"

OR_Hash::~OR_Hash() {}

octave_value OR_Hash::to_octave()
{
  int i;
  VALUE names = rb_funcall(ruby_val, rb_intern("keys"), 0);
  int number_of_keys = RARRAY(names)->len;

  string_vector keys = string_vector();
  for (i = 0; i < number_of_keys; i++) {
    keys.append(std::string(RSTRING(RARRAY(names)->ptr[i])->ptr));
  }

  Octave_map struct_matrix = Octave_map(dim_vector(0, 1), Cell(keys));
  for (i = 0; i < number_of_keys; i++) {
    struct_matrix.contents(std::string(RSTRING(RARRAY(names)->ptr[i])->ptr)) = OR_Variable(rb_hash_aref(ruby_val, rb_str_new2(RSTRING(RARRAY(names)->ptr[i])->ptr))).to_octave();
  }

  return struct_matrix;
}
